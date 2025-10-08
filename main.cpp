#include <stdio.h>
#include <sgl/window.h>




int main(int argc, char **argv)
{
	// Create a GLFW window without an OpenGL context.
	SGLWindow window("SGL", 800, 600, true);
    window.init();
    window.start();
	return 0;
}