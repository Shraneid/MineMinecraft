#include "blockManager.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/ext.hpp"
#include <iostream>

template <typename T, size_t N>
size_t countof(T(&array)[N])
{
	return N;
}


void addCubeToVertexBuffer(GLfloat* vertices_data, GLfloat* texture_data, const GLfloat* g_vertex_buffer_data, const GLfloat* g_uv_buffer_data, glm::vec3 cubePositions[], int nbOfBlocks) {
	

	for (int cubeNb = 0; cubeNb < nbOfBlocks; cubeNb++) {
		glm::vec3 cubePos = cubePositions[cubeNb];

		//std::cout << cubePos.x << " " << cubePos.y << " " << cubePos.z <<  std::endl;

		int j = 0 + cubeNb * 72;
		for (int i = 0 + cubeNb*108; i < 108 + cubeNb*108; i += 3) {
			vertices_data[i] = g_vertex_buffer_data[(i) % 108] + cubePos.x * 2;
			vertices_data[i + 1] = g_vertex_buffer_data[(i + 1) % 108] + cubePos.y * 2;
			vertices_data[i + 2] = g_vertex_buffer_data[(i + 2) % 108] + cubePos.z * 2;

			texture_data[j] = g_uv_buffer_data[(j) % 72];
			texture_data[j + 1] = g_uv_buffer_data[(j + 1) % 72];
			
			j += 2;
		}
	}
}