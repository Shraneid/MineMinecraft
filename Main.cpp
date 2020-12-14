#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "glm/ext.hpp"
using namespace glm;

#include <loadShader.hpp>
#include <loadTexture.hpp>
#include <controls.hpp>
//#include <blockManager.hpp>
#include <chunk.hpp>
#include <Perlin.hpp>
#include <perlinNoise.hpp>

std::vector<chunk *> chunks;
//std::vector<float> val;

int main(int argc, char* argv[]) {
	perlinNoise* heightMapGenerator = new perlinNoise();
	heightMapGenerator->setBaseFrequency(0.5f);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 1920;
	int height = 1080;

	window = glfwCreateWindow(width, height, "very good copy of minecraft", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window, cheh\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW, cheh\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders(
		//"D:/WORK/Programmation/C++ Projects/OpenGLExamples/target/UvVertexShader.GLSL",
		"D:/WORK/Programmation/C++ Projects/OpenGLExamples/target/UvVertexShader.GLSL",
		//"D:/WORK/Programmation/C++ Projects/OpenGLExamples/target/SquareTextureFragmentShader.GLSL"
		"D:/WORK/Programmation/C++ Projects/OpenGLExamples/target/MultipleTexturesFragmentShader.GLSL"
	);

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	/* SETTING UP THE CAMERA AND projection + view transforms */
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		glm::vec3(1.0f, 1.0f, 3.0f),	//camera is at (4,3,3) in World Space
		glm::vec3(0.0f, 0.0f, 0.0f),	//looking at origin
		glm::vec3(0.0f, 1.0f, 0.0f)		//Head is up (e.g. (0,-1,0) would be looking upside down)
	);

	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model;


	//LOADING TEXTURES AND BINDING THEM
	GLuint grassTextureID = loadDDS("D:\\WORK\\Programmation\\C++ Projects\\OpenGLExamples\\assets\\textures\\grass.DDS", "grass");
	GLuint stoneTextureID = loadDDS("D:\\WORK\\Programmation\\C++ Projects\\OpenGLExamples\\assets\\textures\\stone.DDS", "stone");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grassTextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stoneTextureID);

	/*glUniform1i(glGetUniformLocation(grassTextureID,"grass"), 0);
	glUniform1i(glGetUniformLocation(stoneTextureID,"stone"), 1);*/
	//glUniform1i(stoneTextureID, 1);

	glm::vec3 cameraPosition = { 1,1,0 };
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//backface culling
	glEnable(GL_CULL_FACE);

	//creating chunks
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; i++) {
			chunks.push_back(new chunk(glm::vec3(float(i), -1.0f, float(-j)), biomeType::plain, heightMapGenerator));
		}
	}

	//optimize chunk vertices for rendering (removing the ones that are not visible on screen)
	for (chunk* c : chunks) {
		c->updateLocal();
	}

	do {
		//compute MVP matrices from user inputs to move around
		computeMatricesFromInputs();

		
		//updating camera for movement
		Projection = getProjectionMatrix();
		View = getViewMatrix();
		Model = glm::mat4(1.0f);

		mvp = Projection * View * Model;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		for (chunk* c : chunks) {
			c->render();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	//deleting chunks (not needed anymore because vectors are automatically destroyed)
	//delete chunks;
		
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &grassTextureID);
	glDeleteTextures(1, &stoneTextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}