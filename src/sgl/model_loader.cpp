#include <sgl/loaders/model_loader.h>
#include <sgl/logger.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>

std::vector<ModelInfo> modelInfos; // Store model metadata
std::vector<Model *> models;       // Store loaded models

void loadModelHeaders()
{
    namespace fs = std::filesystem;
    std::string shadersDir = "engine/models";
    getLogger()->log("ModelLoader", "Loading model headers from directory: " + shadersDir);

    for (const auto &entry : fs::directory_iterator(shadersDir))
    {
        if (!entry.is_regular_file())
            continue;

        std::ifstream file(entry.path());
        if (!file.is_open())
            continue;

        std::string firstLine;
        std::getline(file, firstLine);

        // Parse line like: <<sgl.model.loader=1.0;name=triangle>>
        size_t start = firstLine.find("<<");
        size_t end = firstLine.find(">>");
        if (start == std::string::npos || end == std::string::npos || end <= start + 2)
            continue;

        std::string meta = firstLine.substr(start + 2, end - (start + 2));
        ModelInfo info;
        std::istringstream ss(meta);
        std::string token;

        while (std::getline(ss, token, ';'))
        {
            size_t eq = token.find('=');
            if (eq == std::string::npos)
                continue;
            std::string key = token.substr(0, eq);
            std::string value = token.substr(eq + 1);
            if (key == "sgl.model.loader")
                info.loader_version = value;
            else if (key == "name")
                info.name = value;
        }

        if (info.loader_version != SGL_MODEL_LOADER_VERSION)
        {
            getLogger()->warn("ModelLoader", "Incompatible loader version for model: " + info.name +
                                                 ". Expected " + SGL_MODEL_LOADER_VERSION + ", got " + info.loader_version + ". Skipping.");
            continue;
        }

        info.path = entry.path().string();
        if (info.path.empty() || info.name.empty())
        {
            getLogger()->warn("ModelLoader", "Incomplete model metadata in file: " + entry.path().string() + ". Skipping.");
            continue;
        }

        getLogger()->debug("ModelLoader", "Loaded model metadata: " + info.name + " (" + info.path + ")");
        modelInfos.push_back(info);
    }

    getLogger()->log("ModelLoader", "Total models loaded: " + std::to_string(modelInfos.size()));
    for (const auto &si : modelInfos)
    {
        getLogger()->debug("ModelLoader", "Model ready: " + si.name + " (" + si.path + ")" +
                                              " loader version: " + si.loader_version);
    }
}

int loadModel(const std::string &name)
{
    getLogger()->log("ModelLoader", "Loading: " + name);

    for (const auto &mi : modelInfos)
    {
        if (mi.name != name)
            continue;

        std::ifstream file(mi.path);
        if (!file.is_open())
        {
            getLogger()->error("ModelLoader", "Cannot open model file: " + mi.path);
            return -1;
        }

        std::vector<float> verts;
        std::vector<unsigned int> inds;
        std::vector<float> texcoords;
        std::string line;

        bool readingVertices = false;
        bool readingIndices = false;
        bool readingTexcoords = false;

        while (std::getline(file, line))
        {
            if (line.find("<block=vert>") != std::string::npos)
            {
                readingVertices = true;
                readingIndices = false;
                readingTexcoords = false;
                continue;
            }
            if (line.find("<block=ind>") != std::string::npos)
            {
                readingIndices = true;
                readingVertices = false;
                readingTexcoords = false;
                continue;
            }
            if (line.find("<block=tex>") != std::string::npos)
            {
                readingTexcoords = true;
                readingVertices = false;
                readingIndices = false;
                continue;
            }

            std::istringstream ss(line);
            if (readingVertices)
            {
                std::string sx, sy, sz;
                if (ss >> sx >> sy >> sz)
                {
                    auto removef = [](std::string &s)
                    {
                        if (!s.empty() && (s.back() == 'f' || s.back() == 'F'))
                            s.pop_back();
                    };
                    removef(sx);
                    removef(sy);
                    removef(sz);

                    try
                    {
                        float x = std::stof(sx);
                        float y = std::stof(sy);
                        float z = std::stof(sz);
                        verts.push_back(x);
                        verts.push_back(y);
                        verts.push_back(z);
                    }
                    catch (const std::exception &)
                    {
                        getLogger()->error("ModelLoader", "Failed to parse vertex: " + line);
                    }
                }
            }
            else if (readingIndices)
            {
                unsigned int a, b, c;
                if (ss >> a >> b >> c)
                {
                    inds.push_back(a);
                    inds.push_back(b);
                    inds.push_back(c);
                }
            }
            else if (readingTexcoords)
            {
                std::string su, sv;
                if (ss >> su >> sv)
                {
                    auto removef = [](std::string &s)
                    {
                        if (!s.empty() && (s.back() == 'f' || s.back() == 'F'))
                            s.pop_back();
                    };
                    removef(su);
                    removef(sv);

                    try
                    {
                        float u = std::stof(su);
                        float v = std::stof(sv);
                        texcoords.push_back(u);
                        texcoords.push_back(v);
                    }
                    catch (const std::exception &)
                    {
                        getLogger()->error("ModelLoader", "Failed to parse texcoord: " + line);
                    }
                }
            }
        }

        // Combine vertices + texture coordinates in interleaved order
        std::vector<float> interleaved;
        if (!texcoords.empty() && verts.size() / 3 == texcoords.size() / 2)
        {
            for (size_t i = 0; i < verts.size() / 3; ++i)
            {
                interleaved.push_back(verts[i * 3 + 0]);
                interleaved.push_back(verts[i * 3 + 1]);
                interleaved.push_back(verts[i * 3 + 2]);
                interleaved.push_back(texcoords[i * 2 + 0]);
                interleaved.push_back(texcoords[i * 2 + 1]);
            }

            getLogger()->debug("ModelLoader", "Interleaved vertices with texcoords (" +
                                                  std::to_string(interleaved.size() / 5) + " vertices).");
        }
        else
        {
            interleaved = verts;
        }

        // Build Model
        Model *model = new Model();
        model->name = name;
        model->vertexCount = interleaved.size();
        model->indexCount = inds.size();
        model->texcoordCount = texcoords.size();

        model->vertices = new float[interleaved.size()];
        std::copy(interleaved.begin(), interleaved.end(), model->vertices);

        model->indices = new unsigned int[inds.size()];
        std::copy(inds.begin(), inds.end(), model->indices);

        model->texcoords = new float[texcoords.size()];
        std::copy(texcoords.begin(), texcoords.end(), model->texcoords);

        if (model->vertexCount == 0 || model->indexCount == 0)
        {
            getLogger()->error("ModelLoader", "Model file is empty or malformed: " + mi.path);
            delete model;
            return -1;
        }

        models.push_back(model);

        getLogger()->debug("ModelLoader", "Model loaded: " + name +
                                              " with " + std::to_string(verts.size() / 3) +
                                              " vertices and " + std::to_string(inds.size() / 3) + " triangles.");
        std::string vertOut = "Vertices with UVs:\n";
        for (size_t i = 0; i < interleaved.size() / 5; i++)
        {
            float x = interleaved[i * 5 + 0];
            float y = interleaved[i * 5 + 1];
            float z = interleaved[i * 5 + 2];
            float u = interleaved[i * 5 + 3];
            float v = interleaved[i * 5 + 4];

            vertOut += "Vertex " + std::to_string(i) + ": ";
            vertOut += "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
            vertOut += " UV: (" + std::to_string(u) + ", " + std::to_string(v) + ")\n";
        }
        getLogger()->debug("ModelLoader", vertOut);

        return 0;
    }

    getLogger()->error("ModelLoader", "Model not found: " + name);
    return -1;
}

Model *getModelByName(const std::string &name)
{
    for (auto *m : models)
    {
        if (m->name == name)
            return m;
    }
    getLogger()->error("ModelLoader", "Model not found: " + name);
    return nullptr;
}
