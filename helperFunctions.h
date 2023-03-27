#pragma once

#ifndef _HEADER_
#define _HEADER_

using namespace std;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void keyCallback(GLFWwindow*, int, int, int, int);
GLFWwindow* initializeGL();
unsigned int initializeSphereShaders();
unsigned int initializeTBNShaders();
std::vector<float> getNormalsEndpoints(std::vector<glm::vec3>, std::vector<glm::vec3>, float);
std::vector<float> getTangentsEndpoints(std::vector<glm::vec3>, float);
std::vector<float> getBitangentsEndpoints(std::vector<glm::vec3>, std::vector<float>, std::vector<float>, float);
void renderSphere(float, unsigned int, unsigned int);
unsigned int loadTexture(char const*);

#endif