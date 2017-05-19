#include <GL\glew.h>

#include "VertexObject.hpp"

VertexBufferObject::VertexBufferObject(const GLuint* data, GLsizeiptr ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ELEMENT_ARRAY_BUFFER;
	type = GL_INT;
	size = 0;
	pSize = ptrSize;
	setData(data);
}

VertexBufferObject::VertexBufferObject(const GLfloat* data, GLuint axes, GLsizeiptr ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ELEMENT_ARRAY_BUFFER;
	type = GL_INT;
	size = axes;
	pSize = ptrSize;
	setData(data);
}

void VertexBufferObject::setData(const GLuint* data) {
	bind();
	glBufferData(target, pSize, data, GL_STATIC_DRAW);
}

void VertexBufferObject::setData(const GLfloat* data) {
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