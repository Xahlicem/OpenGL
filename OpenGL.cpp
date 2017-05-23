#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "include/VertexObject.hpp"
#include "include/gfx/Shader.hpp"
#include "include/gfx/Camera.hpp"
#include "include/gfx/Model.hpp"
#include "include/gfx/Texture.hpp"
#include "include/level/Level.hpp"

#include "OpenGL.hpp"

GLFWwindow* window;

float width = 800.0f;
float height = 600.0f;
float zoom = 64.0f;
float x, y;
Model model;
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

	int swap = 0;
	glfwSwapInterval(swap);

#ifdef _WIN32
	typedef BOOL(WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT)
		wglSwapIntervalEXT(swap);
#endif

	glEnable(GL_DEPTH_TEST);
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
	model.load(0, 0, 1, 1, 0.01f, texture_frog);

	Model m(3, 3, 1, 2, 0.01f, texture_frog);
	Model m1(0, 2, 2, 1, 0.02f, texture_frog);
	Model m2(1, 0, 3, 2, -0.2f, texture_frog);
	Model m3(2, 0, 2, 2, 0.03f, texture_frog);
	cam = Camera(width, height);
	cam.setScale(zoom);

	Level l(64, 64, textureTiles);
	//
	while (!glfwWindowShouldClose(window)) {
		programDefault.bind();
		programDefault.setSampler(0);
		programDefault.setProjection(cam.getProjection());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		l.draw();
		model.draw();
		m.draw();
		m1.draw();
		m2.draw();
		m3.draw();

		glBindVertexArray(0);

		showFPS();
		error("loop");
		glfwSwapBuffers(window);
		glfwPollEvents();
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
		if (key == GLFW_KEY_UP) y += 0.5f * i;
		if (key == GLFW_KEY_DOWN) y -= 0.5f * i;
		if (key == GLFW_KEY_LEFT) x -= 0.5f * i;
		if (key == GLFW_KEY_RIGHT) x += 0.5f * i;
		if (key == GLFW_KEY_E) zoom += 0.5f * i;
		if (key == GLFW_KEY_Q) zoom -= 0.5f * i;
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GL_TRUE);
		zoom = zoom > 255 ? 255 : zoom;
		zoom = zoom < 0 ? 0 : zoom;
		cam.setScale(zoom);
		cam.setPos(-x, -y);
		model.vao.rebindPosition(x, y);
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
