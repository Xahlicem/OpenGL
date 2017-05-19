#include <GL\glew.h>

#include "VertexObject.hpp"

VertexBufferObject::VertexBufferObject(const int* data, int ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ELEMENT_ARRAY_BUFFER;
	type = GL_INT;
	size = 0;
	pSize = ptrSize;
	setData(data);
}

VertexBufferObject::VertexBufferObject(const float* data, int axes, int ptrSize) {
	glGenBuffers(1, &id);
	target = GL_ELEMENT_ARRAY_BUFFER;
	type = GL_INT;
	size = axes;
	pSize = ptrSize;
	setData(data);
}

void VertexBufferObject::setData(const int* data) {
	bind();
	glBufferData(target, pSize, data, GL_STATIC_DRAW);
}

void VertexBufferObject::setData(const float* data) {
	bind();
	glBufferData(target, pSize, data, GL_STATIC_DRAW);
}

void VertexBufferObject::bind(int target, GLuint id) {
	glBindBuffer(target, id);
}

void VertexBufferObject::bind() {
	bind(target, id);
}

void VertexBufferObject::unbind() {
	bind(target, 0);
}