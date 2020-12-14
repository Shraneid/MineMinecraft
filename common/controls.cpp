// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

#include <iostream>

glm::mat4 ProjectionMatrix;
glm::mat4 ViewMatrix;

glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
glm::mat4 getViewMatrix() {
	return ViewMatrix;
}


glm::vec3 position = glm::vec3(-3, 1, -3);
glm::vec3 movementDirection = glm::vec3(0, 0, 0);

float horizontalAngle = 3.14f/4;
float verticalAngle = -3.14f/10;
float initialFoV = 45.0f;

float movementSpeed = 7.0f;
float mouseSpeed = 0.2f;

void computeMatricesFromInputs() {
	static float lastTime = glfwGetTime();

	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;


	//VISION / MOUSE
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

	horizontalAngle += mouseSpeed * deltaTime * float(windowWidth / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(windowHeight / 2 - ypos);

	//lock vertical view to top down, can't rotate head to see behind (on vert axis)
	if (verticalAngle > 3.14 / 2.0f) {
		verticalAngle = 3.14 / 2.0f;
	} else if (verticalAngle < -3.14 / 2.0f) {
		verticalAngle = -3.14 / 2.0f;
	}

	//get absolute horizontal angle
	/*if (horizontalAngle > 3.14 * 2.0f) {
		horizontalAngle = std::fmod(horizontalAngle, (3.14 * 2.0));
	}
	else if (horizontalAngle < -3.14 * 2.0f) {
		horizontalAngle = std::fmod(horizontalAngle, (-3.14 * 2.0));
	}*/

	//std::cout << horizontalAngle << std::endl;

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = -1.0f * glm::cross(direction, right);

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 worldRight = glm::vec3(1.0f, 0.0f, 0.0f);


	glm::vec3 directionMovementVector = direction * glm::vec3(1.0f, 0.0f, 1.0f);


	//POSITION / KEYS
	//front/back
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		movementDirection += directionMovementVector;
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		movementDirection -= directionMovementVector;
	}

	//sideways
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		movementDirection += right;
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		movementDirection -= right;
	}

	//fly up/down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		movementDirection += worldUp;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		movementDirection -= worldUp;
	}

	movementDirection = glm::normalize(movementDirection);
	if (isnan(movementDirection.x)) {
		movementDirection.x = 0.0f;
	}
	if (isnan(movementDirection.y)) {
		movementDirection.y = 0.0f;
	}
	if (isnan(movementDirection.z)) {
		movementDirection.z = 0.0f;
	}

	//std::cout << "x : " << movementDirection.x << " || y : " << movementDirection.y << " || z : " << movementDirection.z << std::endl;

	//update the position
	position += movementDirection * deltaTime * movementSpeed;

	ProjectionMatrix = glm::perspective(glm::radians(initialFoV), float(windowWidth)/float(windowHeight), 0.1f, 1000.0f);
	ViewMatrix = glm::lookAt(
		position,
		position + direction,
		up
	);

	movementDirection = glm::vec3(0, 0, 0);
	lastTime = currentTime;
}


