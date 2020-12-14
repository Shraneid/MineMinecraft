#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "glm/ext.hpp"

enum class blockType { grass, dirt, stone, air };

class block {
public:
	glm::vec3 coordinates;
	blockType type;
	bool visible;

	block();
	block(glm::vec3 coor);
	block(glm::vec3 coor, blockType t);

	/*void render();
	void update();*/
};

#endif