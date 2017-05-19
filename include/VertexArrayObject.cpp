#include <GL\glew.h>

#include "VertexObject.hpp"

VertexArrayObject::~VertexArrayObject() {
	glDeleteBuffers(1, &vertId);
	glDeleteBuffers(1, &textId);
	glDeleteBuffers(1, &indexId);

	glDeleteVertexArrays(1, &id);
}

VertexArrayObject::VertexArrayObject(GLuint* index, GLsizeiptr indexSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize) {
	glGenVertexArrays(1, &id);
	bind();
	vertId = addArray(vertices, verticesSize, 3).unbind();
	textId = addArray(textureCoords, textureCoordsSize, 2).unbind();
	VertexBufferObject vbo = addIndex(index, indexSize);
	unbind();
	indexId = vbo.unbind();
}

void VertexArrayObject::bind(GLuint id) {
	glBindVertexArray(id);
}

GLuint VertexArrayObject::bind() {
	bind(id);
	return id;
}

GLuint VertexArrayObject::unbind() {
	bind(0);
	return id;
}

int VertexArrayObject::count() {
	return length;
}

VertexBufferObject VertexArrayObject::addArray(GLfloat* data, GLuint dataSize, GLsizeiptr size) {
	VertexBufferObject vbo(data, size, dataSize);
	addArray(vbo);
	return vbo;
}

VertexBufferObject VertexArrayObject::addArray(VertexBufferObject vbo) {
	glVertexAttribPointer(arrays, vbo.size, vbo.type, false, 0, 0);
	enableArray(arrays++);
	return vbo;
}

VertexBufferObject VertexArrayObject::addIndex(GLuint* index, GLsizeiptr indexSize) {
	length = indexSize;
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