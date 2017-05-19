#include <GL\glew.h>

#include "VertexObject.hpp"

VertexArrayObject::VertexArrayObject(int* index, int indexSize, float* vertices, int verticesSize, float* textureCoords, int textureCoordsSize) {
	glGenVertexArrays(1, &id);
	bind();
	addArray(vertices, verticesSize, 3).unbind();
	addArray(textureCoords, textureCoordsSize, 2).unbind();
	VertexBufferObject vbo = addIndex(index, indexSize);
	unbind();
	vbo.unbind();
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

int VertexArrayObject::count() {
	return length;
}

VertexBufferObject VertexArrayObject::addArray(float* data, int dataSize, int size) {
	VertexBufferObject vbo(data, size, dataSize);
	addArray(vbo);
	return vbo;
}

VertexBufferObject VertexArrayObject::addArray(VertexBufferObject vbo) {
	glVertexAttribPointer(arrays, vbo.size, vbo.type, false, 0, 0);
	enableArray(arrays++);
	return vbo;
}

VertexBufferObject VertexArrayObject::addIndex(int* index, int indexSize) {
	length = indexSize;
	VertexBufferObject vbo(index, indexSize);
	vbo.bind();
	return vbo;
}

void VertexArrayObject::enableArray(int i) {
	if (i < 0 || i >= arrays) return;
	glEnableVertexAttribArray(i);
}

void VertexArrayObject::disableArray(int i) {
	if (i < 0 || i >= arrays) return;
	glDisableVertexAttribArray(i);

}