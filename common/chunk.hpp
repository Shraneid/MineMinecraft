#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "block.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "perlinNoise.hpp"

enum class biomeType { desert, plain, forest };

class chunk {
public:
	//chunk parameters
	glm::vec3 coordinates;
	biomeType biome;
	bool visible;

	//cube matrix
	block cubes[16][16][16];
	//block cubes[1][1][1];

	//GPU data
	GLfloat vertex_data[16*16*16*108];
	GLfloat texture_data[16*16*16*108];
	/*GLfloat vertex_data[108];
	GLfloat texture_data[72];*/

	chunk(glm::vec3 coor, biomeType biome, perlinNoise* mapGen);
	chunk();

	void updateLocal();
	void render();
	~chunk();

private:
	GLuint vertexbuffer;
	GLuint uvbuffer;
	int vertices_to_render;

	void computeVerticesAndTextures();
};

#endif