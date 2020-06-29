#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLint glWidth = 800;
GLint glHeight = 600;

GLfloat vertices[] = {
          // position         // color
        -0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // right
        -0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // left
        -0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top

};
float secondTriangle[] = {
    0.0f, -0.5f, 0.0f,  // left
    0.9f, -0.5f, 0.0f,  // right
    0.45f, 0.5f, 0.0f   // top 
};

GLuint indices[] = {  
    0, 1, 3,   
    1, 2, 3    
};

//Vertex shader
const char* vertexShaderSorce =
"#version 460 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"void main(){\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"vertexColor = color;\n"
"}\n";

const char* fragmentShaderSorce =
"#version 460 core\n"
"in vec3 vertexColor;\n"
"out vec4 color;\n"
"void main(){\n"
"color  = vec4(vertexColor, 1.0f);\n"
"}\n";

const char* fragmentShaderSorce2 =
"#version 460 core\n"
"out vec4 color;\n"
"uniform vec4 ourColor2;\n"
"void main(){\n"
"color  = ourColor2;\n"
"}\n";


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

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Can't load GLAD!!!" << std::endl;
		return -1;
	}
	
    glViewport(0, 0, glWidth, glHeight);

	std::cout << "Renderer:  " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

   

    //Create, set and compailer Vertex Shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSorce, NULL);
    glCompileShader(vertexShader);

    //check vertex shader
    GLint success;
    GLchar infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
   }
	
    //Create, set and compailer Fragment Shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSorce, NULL);
    glCompileShader(fragmentShader);

    //check fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }


    GLuint fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSorce2, NULL);
    glCompileShader(fragmentShader2);

    //check fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER2::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }


    //create shader programe
    GLint shaderProgram1;
    shaderProgram1 = glCreateProgram();
    //set shaders in programe and Link
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader);
    glLinkProgram(shaderProgram1);

    //check shader programe
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
    }


    GLint shaderProgram2;
    shaderProgram2 = glCreateProgram();
    //set shaders in programe and Link
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    //check shader programe
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);


    // vertex buffer objects memory GPU
    GLuint VBO1;
    glGenBuffers(1, &VBO1);
    // set type VBO GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    //copy data in Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex array objects memory GPU
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    
   /* GLuint EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
       */
    GLuint VBO2;
    glGenBuffers(1, &VBO2);
    // set type VBO GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    //copy data in Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    // vertex array objects memory GPU
    GLuint VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        //glClearColor(rand() % 256, rand() % 256, rand() % 256, 1);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);

        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        GLint vertexColorLocation2 = glGetUniformLocation(shaderProgram2, "ourColor2");
        
        glUniform4f(vertexColorLocation2, greenValue, 0.0f, 0.0f, 1.0f);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}