#ifndef BLOCKMANAGER_HPP
#define BLOCKMANAGER_HPP

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "glm/ext.hpp"

void addCubeToVertexBuffer(GLfloat* vertices_data, GLfloat* texture_data, const GLfloat* g_vertex_buffer_data, const GLfloat* g_uv_buffer_data, glm::vec3 cubePositions[], int nbOfBlocks);

#endif