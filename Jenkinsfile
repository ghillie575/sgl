pipeline {
    agent any

    stages {
        stage('Install Dependencies') {
            steps {
                script {
                    // Install additional libraries (example for Ubuntu)
                    // You can modify this command based on your OS and required libraries
                    sh '''
                     apt-get update
                     apt-get install -y g++ cmake git libglfw3 libglfw3-dev
                    '''
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    // Configure and build the project
                    sh 'cmake .'
                    sh 'cmake --build . --config Release'
                }
            }
        }

        stage('Package') {
            steps {
                script {
                    // Create a release package (e.g., a zip file)
                    sh 'cp ./XandO out/XandO'
                    sh 'cp -r ./engine out/engine'
                    sh 'cp -r ./scenes out/scenes'
                    sh 'cd out && zip -r build.zip * && mv build.zip ../ && cd ..'
                }
            }
        }

        stage('Collect Artifacts') {
            steps {
                // Archive the build.zip file as an artifact
                archiveArtifacts artifacts: 'build.zip', fingerprint: true
            }
        }

        stage('Cleanup') {
            steps {
                script {
                    // Remove all build resources
                    sh '''
                        echo 'cleaning up'
                        rm -rf build
                        rm -rf out/engine
                        rm -rf out/scenes
                        rm -rf out/XandO
                        rm -f build.zip
                    '''
                }
            }
        }
    }
}