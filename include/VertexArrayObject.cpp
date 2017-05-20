#include <GL\glew.h>

#include "VertexObject.hpp"

VertexArrayObject::~VertexArrayObject() {
	bind();
	if (vertId != 0) glDeleteBuffers(1, &vertId);
	if (textId != 0) glDeleteBuffers(1, &textId);
	if (indexId != 0) glDeleteBuffers(1, &indexId);
	unbind();

	glDeleteVertexArrays(1, &id);
}

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &id);
}

VertexArrayObject::VertexArrayObject(GLuint* index, GLsizeiptr indexSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize) {
	glGenVertexArrays(1, &id);
	load(index, indexSize, vertices, verticesSize, textureCoords, textureCoordsSize);
}

void VertexArrayObject::load(GLuint* index, GLsizeiptr indexSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize) {
	bind();
	vertId = addArray(vertices, verticesSize, 3).unbind();
	textId = addArray(textureCoords, textureCoordsSize, 2).unbind();
	VertexBufferObject vbo = addIndex(index, indexSize);
	unbind();
	indexId = vbo.bind();
	length = 6;
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

GLuint VertexArrayObject::count() {
	return length;
}

GLuint VertexArrayObject::getId() {
	return id;
}

VertexBufferObject VertexArrayObject::addArray(GLfloat* data, GLuint dataSize, GLsizeiptr size) {
	VertexBufferObject vbo(data, size, dataSize);
	addArray(vbo);
	return vbo;
}

VertexBufferObject VertexArrayObject::addArray(VertexBufferObject vbo) {
	glVertexAttribPointer(arrays, vbo.size, vbo.type, false, 0, (GLvoid*)0);
	enableArray(arrays++);
	return vbo;
}

VertexBufferObject VertexArrayObject::addIndex(GLuint* index, GLsizeiptr indexSize) {
	VertexBufferObject vbo(index, indexSize);
	vbo.bind();
	return vbo;
}

void VertexArrayObject::enableArray(GLuint i) {
	if (i < 0 || i >= arrays) return;
	glEnableVertexAttribArray(i);
}

void VertexArrayObject::disableArray(GLuint i) {
	if (i < 0 || i >= arrays) return;
	glDisableVertexAttribArray(i);

}