#pragma warning(disable:4996)

#include <stdio.h>

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

Shader programDefault;

void loadShaders() {
	programDefault.loadProgram("res/shaders/shader.vert", "res/shaders/shader.frag");
}

Shader::Shader() {
}

Shader::~Shader() {
	if (id == 0) return;
	if (vShader != 0) {
		glDetachShader(id, vShader);
		glDeleteShader(vShader);
	}

	if (fShader != 0) {
		glDetachShader(id, fShader);
		glDeleteShader(fShader);
	}

	glDeleteProgram(id);
}

void Shader::bind() {
	glUseProgram(id);
}

int Shader::getProgram() {
	//printf("%d\n", program);
	return id;
}

void Shader::setProjection(glm::mat4 data) {
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::setProjection(const GLfloat* data) {
	glUniformMatrix4fv(projection, 1, GL_FALSE, data);
}

void Shader::setSampler(GLuint i) {
	glUniform1i(sampler, i);
}

void Shader::loadProgram(const char* vertFilePath, const char* fragFilePath) {

	// Create the shaders
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);


	loadShader(vertFilePath, vShader);
	loadShader(fragFilePath, fShader);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Link the program
	printf("Linking program\n");
	id = glCreateProgram();
	glAttachShader(id, vShader);
	glAttachShader(id, fShader);
	glLinkProgram(id);

	// Check the program
	glGetProgramiv(id, GL_LINK_STATUS, &Result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		char* errorMessage = (char*)malloc(InfoLogLength + 1);
		glGetProgramInfoLog(id, InfoLogLength, NULL, errorMessage);
		printf("%s\n", errorMessage);
		free(errorMessage);
	}

	projection = glGetUniformLocation(id, "projection");
	sampler = glGetUniformLocation(id, "sampler");
}

bool Shader::loadShader(const char* path, GLuint id) {
	FILE* file;

	// Read the Shader code from the file
	file = fopen(path, "rb");
	if (file) {

		fseek(file, 0L, SEEK_END);
		const int size = ftell(file) + 1;
		rewind(file);

		char* code = (char *)malloc(size);
		for (int i = 0; i < size - 1; i++) code[i] = getc(file);
		code[size - 1] = '\0';
		fclose(file);

		compileShader(&code[0], id, path);

		free(code);
		return true;
	} else printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", path);
	return false;
}

void Shader::compileShader(const char* code, GLuint id, const char* path) {
	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Shader
	printf("Compiling shader : %s\n", path);
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);

	// Check Shader
	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		char* errorMessage = (char*)malloc(InfoLogLength + 1);
		glGetShaderInfoLog(id, InfoLogLength, NULL, errorMessage);
		printf("%s\n", errorMessage);
		free(errorMessage);
	}
}