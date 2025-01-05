#version 330 core
layout (location = 0) in vec3 aPos; // координатные переменные в атрибуте идут первыми среди всех остальных данных, поэтому указываем для них location = 0
  
out vec4 vertexColor; // определяем выходную переменную, задающую цвет, которую затем отправим во фрагментный шейдер
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0); // обратите внимание, что в конструктор переменной типа vec4 мы напрямую передаем переменную типа vec3
    vertexColor = vec4(0.4824, 1.0, 0.0, 1.0); // задаем темно-красное значение цвета для выходной переменной
}