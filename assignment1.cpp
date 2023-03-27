//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "helperFunctions.h"
//#include <iostream>
//
//#pragma region // notes to self
//// opengl as a state machine
//// objects in opengl store state: they keep track of state and modify state
//// 
//// what's an attribute?
//// each vertex contains a lot of data: position, color, texture, normals, etc.
//// each of those properties is called an attribute
//// a position is an attribute; a color is an attribute; a texture is an attribute; etc.
//// 
//// what's a buffer?
//// a buffer is a linear array of data that the GPU stores 
//// 
//// what's a draw call?
//// a draw call is a draw command: read what's in the buffer and draw it to the screen
//// 
//// what's binding?
//// binding a buffer is simply selecting a buffer to be the current one to be worked on
//// 
//// what is glVertexAttribPointer for?
//// when we call glBufferData, opengl needs to know what the format of the data is
//// all we said was "here's the type and the size and the data and the usage, now go draw it"
//// but it doesn't know if the data is 2d vectors or 3d vectors, or if it's floats or ints, etc.
//// essentially, we are specifying the layout of our vertex buffer object that holds the attribute data
////
//#pragma endregion
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// shader sources
//#pragma region // produces green rectangle
////const char* vertexShaderSource = "#version 330 core\n"
////"layout (location = 0) in vec3 aPos;\n"
////"void main()\n"
////"{\n"
////"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
////"}\0";
////
////const char* fragmentShaderSource = "#version 330 core\n"
////"out vec4 FragColor;\n"
////"void main()\n"
////"{\n"
////"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
////"}\n\0";
//#pragma endregion
//// produces color-interpolated rectangle
//const char* vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec2 position;\n"
//    "layout (location = 1) in vec3 color;\n"
//    "out vec3 Color;\n"
//    "void main()\n"
//    "{\n"
//    "   Color = color;\n" 
//    "gl_Position = vec4(position, 0.0, 1.0);\n"
//    "}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//    "in vec3 Color;\n"
//    "out vec4 FragColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(Color, 1.0f);\n"
//    "}\n\0";
//
//// callback function: when the user resizes the window, the viewport resizes too
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // specifies the window rectangle for rendering
//    glViewport(0, 0, width, height);
//}
//
//// processes input
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    // set draw mode interactively
//    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
//}
//
//int main()
//{
//    // initialize glfw, use opengl 3.3 plus core-profile
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // create a window object and do a null check
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    // set the opengl context for the window to be the current context
//    glfwMakeContextCurrent(window);
//
//    // set the callback function for resizing the viewport when window is resized
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // initialize GLEW
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//
//    // vertex shader
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    // check for vertex shader compiler errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    // fragment shader
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    // check for fragment shader compiler errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    // linking the vertex and fragment shaders into a shader program
//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // check for linking errors
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success)
//    {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//
//    // delete shaders after linking, they are no longer needed
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // vertices for a rectangle
//    #pragma region // produces green rectangle
//    //float vertices[] = {
//    //     0.5f,  0.5f, 0.0f,  // top right
//    //     0.5f, -0.5f, 0.0f,  // bottom right
//    //    -0.5f, -0.5f, 0.0f,  // bottom left
//    //    -0.5f,  0.5f, 0.0f   // top left 
//    //};  
//    #pragma endregion
//    // produces color-interpolated rectangle 
//    float vertices[] = {
//        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
//         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
//         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
//        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // bottom-left
//    };
//
//    // indexing the vertices to avoid overlap
//    // we must start from 0
//    #pragma region // produces green rectangle
//    //unsigned int indices[] = {
//    //    0, 1, 3,    // first triangle
//    //    1, 2, 3     // second triangle
//    //};  
//    #pragma endregion
//    // produces color-interpolated rectangle
//    unsigned int indices[] = {
//        0, 1, 2,
//        2, 3, 0
//    };
//
//    // create the objects and generate their buffer object names
//    // these are integer ids that represent our buffers
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    // bind vertex array object
//    glBindVertexArray(VAO);
//
//    // bind array buffer to vertex buffer object, VBO
//    // in other words, we tell opengl: the current array buffer is VBO
//    // GL_ARRAY_BUFFER is called the target 
//    // we then create VBO'S data store and copy the data into it
//    // target = GL_ARRAY_BUFFER
//    // size = sizeof(vertices) because that's the size of the new data store we want to create
//    // data = vertices, the actual data we want to copy in
//    // and usage = GL_STATIC_DRAW: 
//    // static means the data will be modified once and used many times
//    // we choose static because we create the buffer once and won't modify it every
//    // frame but will draw it every frame (remember, we are just drawing a triangle),
//    // hence "used many times"
//    // draw means we are using this data as the source for GL drawing
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // bind element array buffer to element buffer object, EBO
//    // in other words, we tell opengl: the current element array buffer is EBO
//    // GL_ELEMENT_ARRAY_BUFFER is called the target 
//    // we then create EBO'S data store and copy the data into it
//    // target = GL_ELEMENT_ARRAY_BUFFER
//    // size = sizeof(indices) because that's the size of the new data store we want to create
//    // data = indices, the actual data we want to copy in
//    // and usage = GL_STATIC_DRAW:
//    // static means the data will be modified once and used many times
//    // we choose static because we create the buffer once and won't modify it every
//    // frame but will draw it every frame (remember, we are just drawing a triangle),
//    // hence "used many times"
//    // draw means we are using this data as the source for GL drawing
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // specify the location and data format of the array of generic 
//    // vertex attributes at index index to use when rendering
//    #pragma region // produces green rectangle
//    // index = 0 because that's the location of "in vec3 aPos"
//    // size = 3 because there are three components per vertex position
//    // type = GL_FLOAT because the vertex components are floats
//    // normalized = GL_FALSE because we are not normalizing
//    // stride = 3 * sizeof(float) because there are 3 float-bytes between each vertex
//    // pointer = (void*)0 because there is only a single attribute, position, so 
//    // the pointer doesn't have to skip over any attributes - each new position will
//    // be at "location" 0 of its vertex
//    // the buffer is contiguously made up of vertex positions and nothing else
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(0);
//    #pragma endregion
//
//    // here we first enable the vertex attribute array for the position attribute
//    // and then specify the attribute pointers but with the new (x, y, r, g, b) format
//    // produces color-interpolated rectangle
//    // posAttrib is the index, or location, of the position attribute, which is location = 0
//    // size = 2 because there are 2 components per vertex position
//    // stride = 5*sizeof(float) because each vertex has 5 float attribute values
//    // pointer/offset = 0 because for each new vertex, the pointer doesn't have to
//    // skip over any attributes to get to position - it's the first attribute in the
//    // (x, y, r, g, b) format, hence no offset for the position attribute
//    unsigned int posAttrib = glGetAttribLocation(shaderProgram, "position");
//    glEnableVertexAttribArray(posAttrib);
//    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//
//    // here we first enable the vertex attribute array for the color attribute
//    // and then specify the attribute pointers but with the new (x, y, r, g, b) format
//    // colAttrib is the index, or location, of the color attribute, which is location = 1
//    // size = 3 because there are 3 components per vertex color
//    // stride = 5*sizeof(float) because each vertex has 5 float attribute values
//    // pointer/offset = (void*)(2 * sizeof(float)) because for each new vertex,
//    // the pointer does have to skip over the position attribute to get to color,
//    // so the offset of color inside each vertex is 2
//    unsigned int colAttrib = glGetAttribLocation(shaderProgram, "color");
//    glEnableVertexAttribArray(colAttrib);
//    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 
//                          (void*)(2 * sizeof(float)));
//
//    // set fill mode as default draw mode
//     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//    // render loop
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        processInput(window);
//
//        // rendering
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // use shader program, bind VAO, and draw 2 triangles
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//
//        // we use glDrawArrays when we have no index buffer
//        // we use glDrawElements when we do have an index buffer
//        // mode = GL_TRIANGLES because that's the primitive we want to use
//        // count = 6 because there are 6 elements to be rendered
//        // type = GL_UNSIGNED_INT because that's the type of the index values
//        // indices = 0 because that's the offset
//        // how does openGL know where we'll draw the elements in "vertices"?
//        // because of the currently bound buffers and vertex array
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        //glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        // check + call input/output events and swap the buffers
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//
//    return 0;
//}