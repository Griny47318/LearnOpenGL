#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLint glWidth = 640;
GLint glHeight = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    glWidth = width;
    glHeight = height;
    glViewport(0, 0, glWidth, glHeight);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Can't glfwInit!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(glWidth, glHeight, "Hello World", NULL, NULL);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

	if(!gladLoadGL())
	{
		std::cout << "Can't load GLAD!!!" << std::endl;
		return -1;
	}
	
	std::cout << "OpenGL " << GLVersion.major << ", " << GLVersion.minor << std::endl;
	
	glClearColor(0, 1, 0, 1);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}