#include <stdio.h>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "include\Texture.hpp"
#include "include\Shader.hpp"
#include "include\VertexObject.hpp"
#include "include\Camera.hpp"
#include "include\Model.hpp"

#include "OpenGL.hpp"

GLFWwindow* window;

float width = 800.0f;
float height = 600.0f;
float zoom = 64.0f;
float x, y;
Camera cam;

int init() {
	if (!glfwInit()) return 0;


	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow((int)width, (int)height, "Game", 0, 0);

	//glfwSetWindowAspectRatio(window, 4, 3);
	glfwSetKeyCallback(window, keyCall);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	centerWindow();

	glfwMakeContextCurrent(window);
	error("make context");

	// Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 0;
	}
	error("GLEW");

	glfwSwapInterval(0);
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	error("enable");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	loadTextures();
	loadShaders();
	error("load");

	glfwShowWindow(window);
	return 1;
}

void loop() {
	
	GLfloat vertices[] {
		-1, 01, 00,
		-1, -1, 00,
		01, -1, 00,
		01, 01, 00
	};


	GLfloat vertices1[] {
		00, 02, 00,
		00, 00, 00,
		02, 00, 00,
		02, 02, 00
	};


	GLfloat vertices2[] {
		00, 01.5f, -0.3f,
		00, 00, -0.3f,
		01.5f, 00, -0.3f,
		01.5f, 01.5f, -0.3f
	};

	GLfloat textureCoords[] {
		0, 0,
		0, 0.25f,
		0.25f, 0.25f,
		0.25f, 0
	};
	GLuint indices[] { 0, 1, 2, 0, 2, 3 };

	VertexArrayObject vao(indices, sizeof(indices), vertices, sizeof(vertices), textureCoords, sizeof(textureCoords));
	
	VertexArrayObject vao1(indices, sizeof(indices), vertices1, sizeof(vertices1), textureCoords, sizeof(textureCoords));

	VertexArrayObject vao2(indices, sizeof(indices), vertices2, sizeof(vertices2), textureCoords, sizeof(textureCoords));
	

	Model m(-0.25, -1, 2, 2, texture_frog);
	Model m1(0, 0, 2, 2, texture_frog);
	Model m2(1, 0, 2, 2, texture_frog);
	cam = Camera(width, height);
	cam.setScale(zoom);
	//
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		programDefault.bind();
		glActiveTexture(GL_TEXTURE0);
		glfwPollEvents();

		glBindTexture(GL_TEXTURE_2D, texture_frog);
		programDefault.setSampler(0);

		programDefault.setProjection(cam.getView());
		m.draw();
		m1.draw();
		m2.draw();
		vao2.bind();
		glDrawElements(GL_TRIANGLES, vao2.count(), GL_UNSIGNED_INT, (GLvoid*)0);
		vao.bind();
		glDrawElements(GL_TRIANGLES, vao.count(), GL_UNSIGNED_INT, (GLvoid*)0);
		vao1.bind();
		glDrawElements(GL_TRIANGLES, vao1.count(), GL_UNSIGNED_INT, (GLvoid*)0);
		glBindVertexArray(0);

		showFPS();
		glfwSwapBuffers(window);
		//error("loop");
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
		int i = 1;
		if (mods == GLFW_MOD_SHIFT) i = 10;
		if (key == GLFW_KEY_UP) zoom += 0.5f * i;
		if (key == GLFW_KEY_DOWN) zoom -= 0.5f * i;
		if (key == GLFW_KEY_LEFT) x -= 0.5f * i;
		if (key == GLFW_KEY_RIGHT) x += 0.5f * i;
		cam.setScale(zoom);
		cam.setPos(x, y);
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

void error(const char* text) {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
		switch (err) {
		case GL_INVALID_ENUM:
			printf("%s - %s\n", text, "GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			printf("%s - %s\n", text, "GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			printf("%s - %s\n", text, "GL_INVALID_OPERATION");
			break;
		case GL_NO_ERROR:
			printf("%s - %s\n", text, "GL_NO_ERROR");
			break;
		}
}
