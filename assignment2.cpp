//using namespace std;
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "helperFunctions.h"
//#include <iostream>
//#include <vector>
//#include <glm/glm.hpp>
//
//#pragma region // constants
//const unsigned int SCR_WIDTH = 600;
//const unsigned int SCR_HEIGHT = 600;
//
//const unsigned int numX = 50;
//const unsigned int numY = 50;
//const float PI = 3.14159265359f;
//#pragma endregion
//
//#pragma region // global variables
//float sizeScalar = 0.2f;
//#pragma endregion
//
//#pragma region // shaders - sphere
//const char* vertexShaderSphere = 
//    "#version 330 core\n"
//    "layout (location = 0) in vec3 position;\n"
//    "layout (location = 1) in vec3 normal;\n"
//    "out vec3 fragNormal;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(position, 1.0);\n"
//    "   fragNormal = normalize(normal);\n"
//    "}\0";
//
//const char* fragmentShaderSphere = 
//    "#version 330 core\n"
//    "in vec3 fragNormal;\n"
//    "out vec4 fragColor;\n"
//    "void main()\n"
//    "{\n"
//    "   fragColor = vec4((fragNormal + 1)/2, 1.0f);\n"
//    "}\n\0";
//#pragma endregion
//
//#pragma region // shaders - TBN
//const char* vertexShaderTBN = 
//    "#version 330 core\n"
//    "layout (location = 0) in vec3 position;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(position, 1.0);\n"
//    "}\0";
//
//const char* fragmentShaderTBN = 
//    "#version 330 core\n"
//    "uniform vec3 color;\n"
//    "out vec4 lineColor;"
//    "void main()\n"
//    "{\n"
//    "   lineColor = vec4(color, 1.0);\n"
//    "}\n\0";
//#pragma endregion
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
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
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
//        sizeScalar += 0.05f;
//    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
//        sizeScalar -= 0.05f;
//}
//
///// returns the created window
//GLFWwindow* initializeGL()
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
//        cout << "Failed to create GLFW window" << endl;
//        glfwTerminate();
//        return NULL;
//    }
//
//    // set the opengl context for the window to be the current context
//    glfwMakeContextCurrent(window);
//
//    // set the callback function for resizing the viewport when window is resized
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    glfwSetKeyCallback(window, keyCallback);
//
//    // initialize GLEW
//    if (glewInit() != GLEW_OK)
//    {
//        cout << "Failed to initialize GLEW" << endl;
//        return NULL;
//    }
//
//    return window;
//}
//
//unsigned int initializeSphereShaders()
//{
//    // vertex shader
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSphere, NULL);
//    glCompileShader(vertexShader);
//
//    // check for vertex shader compiler errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
//    }
//
//    // fragment shader
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSphere, NULL);
//    glCompileShader(fragmentShader);
//
//    // check for fragment shader compiler errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
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
//        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
//    }
//
//    // delete shaders after linking, they are no longer needed
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    return shaderProgram;
//}
//
//unsigned int initializeTBNShaders()
//{
//    // vertex shader
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderTBN, NULL);
//    glCompileShader(vertexShader);
//
//    // check for vertex shader compiler errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
//    }
//
//    // fragment shader
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderTBN, NULL);
//    glCompileShader(fragmentShader);
//
//    // check for fragment shader compiler errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
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
//        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
//    }
//
//    // delete shaders after linking, they are no longer needed
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    return shaderProgram;
//}
//
///// returns a vector with normals' endpoints for drawing
//vector<float> getNormalsEndpoints(vector<glm::vec3> positions, vector<glm::vec3> normals, float scalar)
//{
//    vector<float> endpoints;
//    for (int i = 0; i < positions.size(); i++)
//    {
//        glm::vec3 P = positions[i];
//        endpoints.push_back(P.x);
//        endpoints.push_back(P.y);
//        endpoints.push_back(P.z);
//
//        glm::vec3 Q = P + scalar * glm::normalize(normals[i]);
//        endpoints.push_back(Q.x);
//        endpoints.push_back(Q.y);
//        endpoints.push_back(Q.z);
//    }
//
//    return endpoints;
//}
//
//vector<float> getTangentsEndpoints(vector<glm::vec3> positions, vector<glm::vec3> normals, float scalar)
//{
//    vector<float> endpoints;
//    for (int i = 0; i < positions.size(); i++)
//    {
//        glm::vec3 P = positions[i];
//        endpoints.push_back(P.x);
//        endpoints.push_back(P.y);
//        endpoints.push_back(P.z);
//
//        glm::vec3 next;
//        if (i == positions.size() - 1)
//            next = positions[0];
//        else
//            next = positions[i + 1];  // TODO: this could be an issue
//
//        glm::vec3 Q = P + scalar * glm::normalize(glm::cross(glm::vec3(0, 1, 0), P));
//        endpoints.push_back(Q.x);
//        endpoints.push_back(Q.y);
//        endpoints.push_back(Q.z);
//    }
//
//    return endpoints;
//}
//
//vector<float> getBitangentsEndpoints(vector<glm::vec3> positions, vector<float> normalsEndpoints, 
//                                     vector<float> tangentsEndpoints, float scalar)
//{
//    vector<float> endpoints;
//    for (int i = 0; i < positions.size(); i++)
//    {
//        glm::vec3 P = positions[i];
//        endpoints.push_back(P.x);
//        endpoints.push_back(P.y);
//        endpoints.push_back(P.z);
//
//        // TODO: this could be an issue
//        glm::vec3 normal = glm::vec3(normalsEndpoints[3*i], normalsEndpoints[3*i + 1], normalsEndpoints[3*i + 2]);
//        glm::vec3 tangent = glm::vec3(tangentsEndpoints[3 * i], tangentsEndpoints[3 * i + 1], tangentsEndpoints[3 * i + 2]);
//
//        glm::vec3 Q = P + scalar * glm::normalize(glm::cross(normal, tangent));
//        endpoints.push_back(Q.x);
//        endpoints.push_back(Q.y);
//        endpoints.push_back(Q.z);
//    }
//
//    return endpoints;
//}
//
//void renderSphere(float r, unsigned int shaderProgramSphere, unsigned int shaderProgramTBN)
//{
//    // clamp radius to [0, 1]
//    r = (r <= 0.0f) ? 0.0f : (r >= 1.0f) ? 1.0f : r;
//
//    #pragma region // vector declarations
//    // sphere rendering
//    vector<glm::vec3> positions;
//    vector<glm::vec3> normals;
//    vector<unsigned int> indices;
//
//    // TBN rendering
//    vector<float> normalsEndpoints;
//    vector<float> tangentsEndpoints;
//    vector<float> bitangentsEndpoints;
//    #pragma endregion
//
//    #pragma region // create vertex positions and normals
//    for (unsigned int x = 0; x <= numX; ++x)
//        for (unsigned int y = 0; y <= numY; ++y)
//        {
//            // find each segment along both axes
//            float xI = (float)x / (float)numX;
//            float yI = (float)y / (float)numY;
//
//            // calculate the angles
//            float theta = xI * 2.0f * PI;
//            float phi = yI * PI;
//
//            // spherical to cartesian
//            float xPos = r * std::cos(theta) * std::sin(phi);
//            float yPos = r * std::cos(phi);
//            float zPos = r * std::sin(theta) * std::sin(phi);
//
//            glm::vec3 position = glm::vec3(xPos, yPos, zPos);
//            glm::vec3 normal = glm::vec3(xPos, yPos, zPos) / r;
//
//            positions.push_back(position);
//            normals.push_back(normal);
//        }
//    #pragma endregion
//
//    #pragma region // create vertex indices
//    bool even = true;
//    for (unsigned int y = 0; y < numY; ++y)
//    {
//        // calculate index based on whether it's an even or odd row
//        if (even)
//            for (unsigned int x = 0; x <= numX; ++x)
//            {
//                indices.push_back(y * (numX + 1) + x);
//                indices.push_back((y + 1) * (numX + 1) + x);
//            }
//        else
//            for (int x = numX; x >= 0; --x)
//            {
//                indices.push_back((y + 1) * (numX + 1) + x);
//                indices.push_back(y * (numX + 1) + x);
//            }
//    
//        even = !even;
//    }
//    #pragma endregion
//
//    #pragma region // input the positions and normals into a single vector
//    vector<float> data;
//    for (unsigned int i = 0; i < positions.size(); ++i)
//    {
//        data.push_back(positions[i].x);
//        data.push_back(positions[i].y);
//        data.push_back(positions[i].z);
//
//        data.push_back(normals[i].x);
//        data.push_back(normals[i].y);
//        data.push_back(normals[i].z);
//    }
//    #pragma endregion
//
//    #pragma region // set the TBN endpoints
//    normalsEndpoints = getNormalsEndpoints(positions, normals, sizeScalar);
//    tangentsEndpoints = getTangentsEndpoints(positions, normals, sizeScalar);
//    bitangentsEndpoints = getBitangentsEndpoints(positions, normalsEndpoints, tangentsEndpoints, sizeScalar);
//    #pragma endregion
//
//    #pragma region // array + buffer declarations
//    unsigned int sphereVAO, sphereVBO, EBO;
//    unsigned int normalsVAO, normalsVBO;
//    unsigned int tangentsVAO, tangentsVBO;
//    unsigned int bitangentsVAO, bitangentsVBO;
//    #pragma endregion
//
//    #pragma region // sphere array + buffers
//    glGenVertexArrays(1, &sphereVAO);
//    glGenBuffers(1, &sphereVBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(sphereVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
//    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
//    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//
//    // positions
//    unsigned int positionAttributeSphere = glGetAttribLocation(shaderProgramSphere, "position");
//    glEnableVertexAttribArray(positionAttributeSphere);
//    glVertexAttribPointer(positionAttributeSphere, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//
//    // normals
//    unsigned int normalAttributeSphere = glGetAttribLocation(shaderProgramSphere, "normal");
//    glEnableVertexAttribArray(normalAttributeSphere);
//    glVertexAttribPointer(normalAttributeSphere, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    #pragma endregion
//
//    #pragma region // normals array + buffers
//    glGenVertexArrays(1, &normalsVAO);
//    glGenBuffers(1, &normalsVBO);
//
//    glBindVertexArray(normalsVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
//    glBufferData(GL_ARRAY_BUFFER, normalsEndpoints.size() * sizeof(float), &normalsEndpoints[0], GL_STATIC_DRAW);
//
//    unsigned int positionAttributeTBN = glGetAttribLocation(shaderProgramTBN, "position");
//    glEnableVertexAttribArray(positionAttributeTBN);
//    glVertexAttribPointer(positionAttributeTBN, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    #pragma endregion
//
//    #pragma region // tangents array + buffers
//    glGenVertexArrays(1, &tangentsVAO);
//    glGenBuffers(1, &tangentsVBO);
//
//    glBindVertexArray(tangentsVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, tangentsVBO);
//    glBufferData(GL_ARRAY_BUFFER, tangentsEndpoints.size() * sizeof(float), &tangentsEndpoints[0], GL_STATIC_DRAW);
//
//    positionAttributeTBN = glGetAttribLocation(shaderProgramTBN, "position");
//    glEnableVertexAttribArray(positionAttributeTBN);
//    glVertexAttribPointer(positionAttributeTBN, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    #pragma endregion
//
//    #pragma region // bitangents array + buffers
//    glGenVertexArrays(1, &bitangentsVAO);
//    glGenBuffers(1, &bitangentsVBO);
//
//    glBindVertexArray(bitangentsVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, bitangentsVBO);
//    glBufferData(GL_ARRAY_BUFFER, bitangentsEndpoints.size() * sizeof(float), &bitangentsEndpoints[0], GL_STATIC_DRAW);
//
//    positionAttributeTBN = glGetAttribLocation(shaderProgramTBN, "position");
//    glEnableVertexAttribArray(positionAttributeTBN);
//    glVertexAttribPointer(positionAttributeTBN, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    #pragma endregion
//
//    #pragma region // draw sphere
//    glUseProgram(shaderProgramSphere);
//    glBindVertexArray(sphereVAO);
//    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)(indices.size()), GL_UNSIGNED_INT, 0);
//    #pragma endregion
//
//    #pragma region // draw normals
//    glUseProgram(shaderProgramTBN);
//    glBindVertexArray(normalsVAO);
//    unsigned int colorLoc = glGetUniformLocation(shaderProgramTBN, "color");
//    glUniform3f(colorLoc, 0, 0, 1);
//    glDrawArrays(GL_LINES, 0, normalsEndpoints.size() / 3);
//    #pragma endregion
//
//    #pragma region // draw tangents
//    glUseProgram(shaderProgramTBN);
//    glBindVertexArray(tangentsVAO);
//    //unsigned int colorLoc = glGetUniformLocation(shaderProgramTBN, "color");
//    //colorLoc = glGetUniformLocation(shaderProgramTBN, "color");
//    glUniform3f(colorLoc, 1, 0, 0);
//    glDrawArrays(GL_LINES, 0, tangentsEndpoints.size() / 3);
//    #pragma endregion
//
//    #pragma region // draw bitangents
//    glUseProgram(shaderProgramTBN);
//    glBindVertexArray(bitangentsVAO);
//    //unsigned int colorLoc = glGetUniformLocation(shaderProgramTBN, "color");
//    //colorLoc = glGetUniformLocation(shaderProgramTBN, "color");
//    glUniform3f(colorLoc, 0, 1, 0);
//    glDrawArrays(GL_LINES, 0, bitangentsEndpoints.size() / 3);
//    #pragma endregion
//}
//
//int main()
//{
//    // initialize glfw + glew + opengl
//    GLFWwindow* window = initializeGL();
//    if (!window)
//        return 0;
//
//    // initialize shaders
//    unsigned int shaderProgramSphere = initializeSphereShaders();
//    if (shaderProgramSphere == 0)
//        return 0;
//
//    unsigned int shaderProgramTBN = initializeTBNShaders();
//    if (shaderProgramTBN == 0)
//        return 0;
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
//        //glUseProgram(shaderProgramSphere);
//        renderSphere(0.75, shaderProgramSphere, shaderProgramTBN);
//
//        // check + call input/output events and swap the buffers
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // end glfw
//    glfwTerminate();
//
//    return 0;
//}