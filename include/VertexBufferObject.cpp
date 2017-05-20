#include <GL\glew.h>

#include "VertexObject.hpp"

VertexBufferObject::VertexBufferObject(GLuint* data, GLsizeiptr ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ELEMENT_ARRAY_BUFFER;
	type = GL_UNSIGNED_SHORT;
	size = 0;
	pSize = ptrSize;
	setData(data);
}

VertexBufferObject::VertexBufferObject(GLfloat* data, GLuint axes, GLsizeiptr ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ARRAY_BUFFER;
	type = GL_FLOAT;
	size = axes;
	pSize = ptrSize;
	setData(data);
}

void VertexBufferObject::setData(GLuint* data) {
	bind();
	glBufferData(target, pSize, data, GL_STATIC_DRAW);
}

void VertexBufferObject::setData(GLfloat* data) {
	bind();
	glBufferData(target, pSize, data, GL_STATIC_DRAW);
}

void VertexBufferObject::bind(GLuint target, GLuint id) {
	glBindBuffer(target, id);
}

GLuint VertexBufferObject::bind() {
	bind(target, id);
	return id;
}

GLuint VertexBufferObject::unbind() {
	bind(target, 0);
	return id;
}