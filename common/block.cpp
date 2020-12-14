#include "block.hpp"
#include "glm/ext.hpp"

block::block() {
	this->coordinates = glm::vec3(0.0f, 0.0f, 0.0f);
	this->type = blockType::air;
	this->visible = false;
}

block::block(glm::vec3 coor) {
	this->coordinates = coor;
	this->type = blockType::air;
	this->visible = false;
}

block::block(glm::vec3 coor, blockType t) {
	this->coordinates = coor;
	this->type = t;
	this->visible = true;
}


