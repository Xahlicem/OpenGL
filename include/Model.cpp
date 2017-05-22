#include <GL\glew.h>

#include "VertexObject.hpp"
#include "Texture.hpp"

#include "Model.hpp"

Model::Model() {
	texture = 0;
}

Model::Model(float x, float y, float width, float height, float z, GLuint textureId) {
	float h = height / 2.0f;
	float w = width / 2.0f;
	GLfloat vertices[]{
		x - w, y + h, z,
		x - w, y - h, z,
		x + w, y - h, z,
		x + w, y + h, z
	};

	GLfloat textureCoords[]{
		0, 0,
		0, 0.25f,
		0.25f, 0.25f,
		0.25f, 0
	};
	GLuint indices[]{ 0, 1, 2, 0, 2, 3 };

	vao.load(indices, sizeof(indices), vertices, sizeof(vertices), textureCoords, sizeof(textureCoords));

	texture = textureId;
}

Model::Model(const VertexArrayObject v, const GLuint textureId) {
	vao = v;
	texture = textureId;
}

void Model::draw() {
	vao.bind();
	setTexure(texture);
	glDrawElements(GL_TRIANGLES, vao.count(), GL_UNSIGNED_INT, (GLvoid*)0);
}

VertexArrayObject Model::getVao() {
	return vao;
}

GLuint Model::getTextureId() {
	return texture;
}