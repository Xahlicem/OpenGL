#include <stdio.h>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GLFW\glfw3.h>

#include "include\Texture.hpp"
#include "include\Shader.hpp"
#include "include\VertexObject.hpp"

#include "OpenGL.hpp"

GLFWwindow* window;

int width = 800;
int height = 600;
float zoom = 1.0f;

int init() {
	if (!glfwInit()) return 0;


	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, height, "Game", 0, 0);

	//glfwSetWindowAspectRatio(window, 4, 3);
	glfwSetKeyCallback(window, keyCall);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	centerWindow();

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 0;
	}

	glfwSwapInterval(0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	loadTextures();
	loadShaders();

	glfwShowWindow(window);
	return 1;
}

void loop() {
	//
	GLfloat vertices[] {
		-1, 01, 00,
		-1, -1, 00,
		01, -1, 00,
		01, 01, 00
	};

	GLfloat textureCoords[] {
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};
	GLuint indices[] { 0, 1, 2, 0, 2, 3 };
	//
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		programDefault.bind();
		glActiveTexture(GL_TEXTURE0);
		glfwPollEvents();

		glBindTexture(GL_TEXTURE_2D, texture_frog);
		
		GLfloat modelView[16];


		VertexArrayObject vao(indices, 6 * sizeof(GLuint), vertices, (4 * 3) * sizeof(GLfloat), textureCoords, (4 * 2) * sizeof(GLfloat));
		vao.bind();
		programDefault.setProjection(modelView);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		vao.unbind();
		vao.~VertexArrayObject();

		showFPS();
		glfwSwapBuffers(window);

		switch (glGetError()) {
		case GL_INVALID_ENUM:
			printf("%s\n", "GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			printf("%s\n", "GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			printf("%s\n", "GL_INVALID_OPERATION");
			break;
		case GL_NO_ERROR:
			//printf("%s\n", "GL_NO_ERROR");
			break;
		}
	}
}

void close() {
	glfwTerminate();
}

void centerWindow() {
	int *pWidth = new int;
	int *pHeight = new int;

											// Get the window size passed to glfwCreateWindow
	glfwGetWindowSize(window, pWidth, pHeight);

	// Get the resolution of the primary monitor
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	// Center the window
	glfwSetWindowPos(window, (vidmode->width - *pWidth) / 2, (vidmode->height - *pHeight) / 2);
	delete pWidth;
	delete pHeight;
}

void keyCall(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_UP) zoom += 0.05f;
		if (key == GLFW_KEY_DOWN) zoom -= 0.05f;
	}
}

int fps;
double lastTime, currentTime;

void showFPS() {
	// Measure speed
	currentTime = glfwGetTime();
	fps++;
	if (currentTime - lastTime >= 1.0) { // If last cout was more than 1 sec ago
		printf("%d\n", fps);
		fps = 0;
		lastTime += 1.0;
	}
}
