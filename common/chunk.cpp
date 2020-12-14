#include "chunk.hpp"

static const GLfloat g_vertex_buffer_data[] = {
	//TOP
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,

	-1.0f,1.0f,-1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,

	//BOT
	-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,

	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,

	//FRONT
	1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,

	1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,

	//RIGHT
	1.0f,1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,

	1.0f,1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f,

	//LEFT
	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,

	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	-1.0f,1.0f,1.0f,

	//BACK
	1.0f,1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,

	1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,1.0f,-1.0f
};
//static const GLfloat g_uv_buffer_data[] = {
//	//TOP
//	0.0f, 0.0f,
//	0.0f, 0.333333f,
//	0.333333f, 0.333333f,
//
//	0.0f, 0.0f,
//	0.333333f, 0.333333f,
//	0.333333f, 0.0f,
//
//	//BOTTOM
//	0.333333f, 0.0f,
//	0.333333f, 0.333333f,
//	0.666666f, 0.333333f,
//
//	0.333333f, 0.0f,
//	0.666666f, 0.333333f,
//	0.666666f, 0.0f,
//
//	//FRONT
//	0.666666f, 0.0f,
//	1.0f, 0.333333f,
//	0.666666f, 0.333333f,
//
//	0.666666f, 0.0f,
//	1.0f, 0.0f,
//	1.0f, 0.333333f,
//
//	//RIGHT
//	0.0f, 0.333333f,
//	0.0f, 0.666666f,
//	0.333333f, 0.666666f,
//
//	0.0f, 0.333333f,
//	0.333333f, 0.666666f,
//	0.333333f, 0.333333f,
//
//	//LEFT
//	0.333333f, 0.333333f,
//	0.333333f, 0.666666f,
//	0.666666f, 0.666666f,
//
//	0.333333f, 0.333333f,
//	0.666666f, 0.666666f,
//	0.666666f, 0.333333f,
//
//	//BACK
//	0.666666f, 0.333333f,
//	0.666666f, 0.666666f,
//	1.0f, 0.666666f,
//
//	0.666666f, 0.333333f,
//	1.0f, 0.666666f,
//	1.0f, 0.333333f
//};
static const GLfloat g_uv_buffer_data[] = {
	//TOP
	0.0f, 0.0f,
	0.0f, 0.333333f,
	0.333333f, 0.333333f,

	0.0f, 0.0f,
	0.333333f, 0.333333f,
	0.333333f, 0.0f,

	//BOTTOM
	0.333333f, 0.0f,
	0.333333f, 0.333333f,
	0.666666f, 0.333333f,

	0.333333f, 0.0f,
	0.666666f, 0.333333f,
	0.666666f, 0.0f,

	//FRONT
	0.666666f, 0.0f,
	1.0f, 0.333333f,
	0.666666f, 0.333333f,

	0.666666f, 0.0f,
	1.0f, 0.0f,
	1.0f, 0.333333f,

	//RIGHT
	0.0f, 0.333333f,
	0.0f, 0.666666f,
	0.333333f, 0.666666f,

	0.0f, 0.333333f,
	0.333333f, 0.666666f,
	0.333333f, 0.333333f,

	//LEFT
	0.333333f, 0.333333f,
	0.333333f, 0.666666f,
	0.666666f, 0.666666f,

	0.333333f, 0.333333f,
	0.666666f, 0.666666f,
	0.666666f, 0.333333f,

	//BACK
	0.666666f, 0.333333f,
	0.666666f, 0.666666f,
	1.0f, 0.666666f,

	0.666666f, 0.333333f,
	1.0f, 0.666666f,
	1.0f, 0.333333f
};

//remove seems between textures
float texture_offset = 0.02;

chunk::chunk(glm::vec3 coor, biomeType biome, perlinNoise* p)
{
	//this->vertexbuffer = NULL;
	glGenBuffers(1, &vertexbuffer);

	//this->uvbuffer = NULL;
	glGenBuffers(1, &uvbuffer);

	this->coordinates = coor;
	this->biome = biome;
	this->vertices_to_render = 0;
	this->visible = true;

	glm::vec3 blockCoordinates;

	srand(time(NULL));



	for (int z = 0; z < 16; ++z) {
		for (int y = 0; y < 16; ++y) {
			int height_b = rand() % 4 + 12; //height between 8 and 16
			for (int x = 0; x < 16; ++x) {
				blockCoordinates = glm::vec3(this->coordinates.x * 16 + x, this->coordinates.y * 16 + y, this->coordinates.z * 16 + z);

				if (y > 16* p->noise(float(this->coordinates.x) + float(x)/16.0f, float(this->coordinates.y) + float(y)/16.0f, float(this->coordinates.z) + float(z)/16.0f)) {
					this->cubes[x][y][z] = block(blockCoordinates);
				}
				else {
					this->cubes[x][y][z] = block(blockCoordinates, blockType::stone);
				}
			}
		}
	}
}
chunk::chunk()
{
	this->coordinates = glm::vec3(0,0,0);
	this->biome = biomeType::plain;
	this->vertices_to_render = 0;
	this->visible = false;

	glm::vec3 blockCoordinates;
}

void chunk::updateLocal()
{
	for (int z = 0; z < 16; ++z) {
		for (int y = 0; y < 16; ++y) {
			for (int x = 0; x < 16; ++x) {
				if (x != 0 && x != 15 && y != 0 && y != 15 && z != 0 && z != 15) {
					if (   cubes[x + 1][y]    [z]    .type != blockType::air
						&& cubes[x - 1][y]    [z]    .type != blockType::air
						&& cubes[x]    [y + 1][z]    .type != blockType::air
						&& cubes[x]    [y - 1][z]    .type != blockType::air
						&& cubes[x]    [y]    [z + 1].type != blockType::air
						&& cubes[x]    [y]    [z - 1].type != blockType::air)
					{
						cubes[x][y][z].visible = false;
					}
				}
			}
		}
	}
}

void chunk::computeVerticesAndTextures() {
	int vertex_index = 0;
	int texture_index = 0;
	this->vertices_to_render = 0;

	for (int z = 0; z < 16; ++z) {
		for (int y = 0; y < 16; ++y) {
			for (int x = 0; x < 16; ++x) {
				//IF NOT AIR BLOCK OR BLOCK IS NOT VISIBLE, WE RENDER
				if (this->cubes[x][y][z].type != blockType::air && this->cubes[x][y][z].visible) {
					for (int it = 0; it < 108; it+=3) {
						//adding vertices of the cube to buffer
						this->vertex_data[vertex_index    ] = g_vertex_buffer_data[(it    ) % 108]/2 + this->cubes[x][y][z].coordinates.x;
						this->vertex_data[vertex_index + 1] = g_vertex_buffer_data[(it + 1) % 108]/2 + this->cubes[x][y][z].coordinates.y;
						this->vertex_data[vertex_index + 2] = g_vertex_buffer_data[(it + 2) % 108]/2 + this->cubes[x][y][z].coordinates.z;

						vertex_index += 3;
						this->vertices_to_render += 3;

						//adding texture uv coordinates to buffer
						//the legacy code is inside the elses, originally it was only that,
						//however because of some graphical artifacts between cubes, (some kind of AA seem),
						//I decided to cut small portions of the textures so that those seems would be 
						//diminished as much as possible, without needing to reconstruct the whole rendering pipeline
						if (g_uv_buffer_data[(it / 3 * 2) % 72] == 0.0f) {
							this->texture_data[texture_index] = g_uv_buffer_data[(it / 3 * 2) % 72] + texture_offset;
						} else if (g_uv_buffer_data[(it / 3 * 2) % 72] == 1.0f) {
							this->texture_data[texture_index] = g_uv_buffer_data[(it / 3 * 2) % 72] - texture_offset;
						}
						else {
							this->texture_data[texture_index] = g_uv_buffer_data[(it / 3 * 2) % 72];
						}

						if (g_uv_buffer_data[(it / 3 * 2+1) % 72] == 0.0f) {
							this->texture_data[texture_index + 1] = g_uv_buffer_data[(it / 3 * 2+1) % 72] + texture_offset;
						}
						else if (g_uv_buffer_data[(it / 3 * 2+1) % 72] == 1.0f) {
							this->texture_data[texture_index + 1] = g_uv_buffer_data[(it / 3 * 2+1) % 72] - texture_offset;
						}
						else {
							this->texture_data[texture_index + 1] = g_uv_buffer_data[(it / 3 * 2 + 1) % 72];
						}

						texture_index += 2;
					}
				}
			}
		}
	}
}

void chunk::render() {
	if (this->visible) {
		this->computeVerticesAndTextures();

		//VERTICES
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex_data), this->vertex_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		//TEXTURES
		glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->texture_data), this->texture_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


		//RENDERING
		//glDrawArrays(GL_TRIANGLES, 0, sizeof(this->vertex_data) / 12);
		glDrawArrays(GL_TRIANGLES, 0, this->vertices_to_render);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}

chunk::~chunk() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
}
