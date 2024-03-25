#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
    if(!glfwInit()) {std::cout << "Error init glfw !" << std::endl; return -1;};

    // Tell GLFW what version of OpenGl we're using
    // In this case we're using OpenGl 4.6 (version when download glad)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Tell GLFW we're using the Core profile (when download glad)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1200, 800, "Learn OpenGl", NULL, NULL);
    if(window == nullptr)
    {
        std::cout << "Error init window !" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    gladLoadGL();
    glViewport(0, 0, 1200, 800);
    
    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

    // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each (the first argument is sizeof array)
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// Introduce the vertices into the VBO

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // First argument is "layout (location = 0) in vec3 aPos;\n"
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created (delete data)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


    glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window))
    {
        
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the background
		glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color to it
		
		glUseProgram(shaderProgram); // Tell OpenGL which Shader Program we want to use
		glBindVertexArray(VAO); // Bind the VAO so OpenGL knows to use it
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle using the GL_TRIANGLES primitive
		
		glfwSwapBuffers(window); // Swap the back buffer with the front buffer
        
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}