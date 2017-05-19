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
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
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
	float vertices[] {
		-0.5F*width, 00.5F*height, 00,
			-0.5F*width, -0.5F*height, 00,
			00.5F*width, -0.5F*height, 00,
			00.5F*width, 00.5F*height, 00
	};

	float textureCoords[] {
		0, 0,
			0, 1,
			1, 1,
			1, 0
	};
	int indices[] { 0, 1, 2, 0, 2, 3 };

	VertexArrayObject vao(indices, 6, vertices, 6 * 3, textureCoords, 6 * 2);
	//
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		programDefault.bind();
		glActiveTexture(GL_TEXTURE0);
		glfwPollEvents();

		glBindTexture(GL_TEXTURE_2D, texture_frog);
		/*
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-0.5f*zoom, 0.5f*zoom, 0);
			glTexCoord2f(0, 0.25f);
			glVertex3f(-0.5f*zoom, -0.5f*zoom, 0);
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(0.5f*zoom, -0.5f*zoom, 0);
			glTexCoord2f(0.25f, 0);
			glVertex3f(0.5f*zoom, 0.5f*zoom, 0);
		}
		glEnd();
		*/
		vao.bind();
		programDefault.setProjection(glm::fmat4());
		glDrawElements(GL_TRIANGLES, vao.count(), GL_UNSIGNED_INT, 0);
		vao.unbind();

		showFPS();
		glfwSwapBuffers(window);
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
