#include <GL\glew.h>

#include "VertexObject.hpp"
#include "Texture.hpp"

#include "Model.hpp"

Model::Model() {
	texture = 0;
}

Model::Model(float x, float y, float width, float height, GLuint textureId) {
	GLfloat vertices[] {
		x, height + y, 00,
		x, y, 00,
		width + x, y, 00,
		width + x, height + y, 00
	};

	GLfloat textureCoords[] {
		0, 0,
		0, 0.25f,
		0.25f, 0.25f,
		0.25f, 0
	};
	GLuint indices[] { 0, 1, 2, 0, 2, 3 };

	vao.load(indices, sizeof(indices), vertices, sizeof(vertices), textureCoords, sizeof(textureCoords));
	
	texture = textureId;
}

Model::Model(const VertexArrayObject v, const GLuint textureId) {
	vao = v;
	texture = textureId;
}

void Model::draw() {
	vao.bind();
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, vao.count(), GL_UNSIGNED_INT, (GLvoid*)0);
	vao.unbind();
}

VertexArrayObject Model::getVao() {
	return vao;
}

GLuint Model::getTextureId() {
	return texture;
}