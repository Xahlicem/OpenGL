#include <GL\glew.h>

#include "VertexObject.hpp"

VertexBufferObject::~VertexBufferObject() {
	//if (id != 0) glDeleteBuffers(1, &id);
}

VertexBufferObject::VertexBufferObject() {}

VertexBufferObject::VertexBufferObject(GLushort* data, GLsizeiptr ptrSize) {
	load(data, ptrSize);
}

VertexBufferObject::VertexBufferObject(GLfloat* data, GLuint axes, GLsizeiptr ptrSize) {
	load(data, axes, ptrSize);
}

void VertexBufferObject::load(GLushort* data, GLsizeiptr ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ELEMENT_ARRAY_BUFFER;
	type = GL_UNSIGNED_SHORT;
	size = 0;
	pSize = ptrSize;
	setData(data);
}

void VertexBufferObject::load(GLfloat* data, GLuint axes, GLsizeiptr ptrSize) {
	load(data, axes, ptrSize, false);
}

void VertexBufferObject::load(GLfloat* data, GLuint axes, GLsizeiptr ptrSize, bool pos) {
	glGenBuffers(1, &id);
	target = GL_ARRAY_BUFFER;
	type = GL_FLOAT;
	size = axes;
	pSize = ptrSize;
	setData(data, pos);
}

void VertexBufferObject::setData(GLushort* data) {
	bind();
	glBufferData(target, pSize, data, GL_STATIC_DRAW);
}

void VertexBufferObject::setData(GLfloat* data, bool dynamic) {
	bind();
	glBufferData(target, pSize, 0, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBufferSubData(target, 0, pSize, data);
}

void VertexBufferObject::bind(GLuint target, GLuint id) {
	glBindBuffer(target, id);
}

void VertexBufferObject::bind() {
	bind(target, id);
}

void VertexBufferObject::unbind() {
	bind(target, 0);
}

void VertexBufferObject::rebind(const GLfloat* data) {
	bind();
	glBufferSubData(target, 0, pSize, data);
	unbind();
}