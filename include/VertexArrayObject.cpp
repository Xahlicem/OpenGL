#include <GL/glew.h>

#include "VertexObject.hpp"

VertexArrayObject::~VertexArrayObject() {
	if (id == 0) return;
	bind();
	position.~VertexBufferObject();
	vertex.~VertexBufferObject();
	texture.~VertexBufferObject();
	indices.~VertexBufferObject();
	unbind();

	glDeleteVertexArrays(1, &id);
}

VertexArrayObject::VertexArrayObject() {
}

VertexArrayObject::VertexArrayObject(GLushort* index, GLsizeiptr indexSize, GLfloat* pos, GLsizeiptr posSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize) {
	load(index, indexSize, pos, posSize, vertices, verticesSize, textureCoords, textureCoordsSize);
}

void VertexArrayObject::load(GLushort* index, GLsizeiptr indexSize, GLfloat* pos, GLsizeiptr posSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize) {
	glGenVertexArrays(1, &id);
	bind();
	position.load(pos, 2, posSize, true);
	addArray(position);

	vertex.load(vertices, 3, verticesSize);
	addArray(vertex);

	texture.load(textureCoords, 2, textureCoordsSize);
	addArray(texture);
	texture.unbind();

	indices.load(index, indexSize);
	unbind();
	indices.unbind();

	length = indexSize / sizeof(GLushort);
}

void VertexArrayObject::bind(GLuint id) {
	glBindVertexArray(id);
}

void VertexArrayObject::bind() {
	bind(id);
}

void VertexArrayObject::unbind() {
	bind(0);
}

void VertexArrayObject::rebindPosition(const GLfloat* data) {
	position.rebind(data);
}

void VertexArrayObject::rebindPosition(GLfloat x, GLfloat y) {
	const GLfloat data[] {
		x, y,
		x, y,
		x, y,
		x, y
	};
	rebindPosition(data);
}

GLuint VertexArrayObject::count() {
	return length;
}

GLuint VertexArrayObject::getId() {
	return id;
}

void VertexArrayObject::addArray(VertexBufferObject vbo) {
	glVertexAttribPointer(arrays, vbo.size, vbo.type, false, 0, (GLvoid*)0);
	enableArray(arrays++);
}

void VertexArrayObject::enableArray(GLuint i) {
	if (i < 0 || i >= arrays) return;
	glEnableVertexAttribArray(i);
}

void VertexArrayObject::disableArray(GLuint i) {
	if (i < 0 || i >= arrays) return;
	glDisableVertexAttribArray(i);

}