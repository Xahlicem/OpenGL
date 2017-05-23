#include <stdlib.h>

#include <GL/glew.h>

#include "../VertexObject.hpp"
#include "../gfx/Camera.hpp"
#include "../gfx/Texture.hpp"

#include "level.hpp"

Level::~Level() {
	free(indices);
	free(pos);
	free(vertices);
	free(textureCoords);
}

Level::Level() {}

Level::Level(int width, int height, GLuint tileset) {
	load(width, height, tileset);
}

void Level::load(int width, int height, GLuint tileset) {
	this->width = width;
	this->height = height;
	this->tileset = tileset;
	loadVao();
}

void Level::loadVao() {
	GLsizeiptr posSize = 2 * sizeof(GLfloat);
	pos = (GLfloat *)malloc(posSize);
	pos[0] = 0;
	pos[1] = 0;

	GLsizeiptr indexSize = width * height * 6 * sizeof(GLfloat);
	indices = (GLushort *)malloc(indexSize);

	GLsizeiptr size = width * height * 4 * sizeof(GLfloat);
	vertices = (GLfloat *)malloc(size * 3);
	textureCoords = (GLfloat *)malloc(size * 2);
	int w = width / 2;
	int h = height / 2;
	int i = 0, j = 0, k = 0, l = 0;
	for (int y = -h; y < h; y++)
		for (int x = -w; x < w; x++) {
			vertices[i++] = 0 + x; // x
			vertices[i++] = 0 + y + 1; // y
			vertices[i++] = 0; // z
			textureCoords[j++] = 12.0f * 0.0625f + 0.001f; // x
			textureCoords[j++] = 11.0f * 0.0625f + 0.001f; // y


			vertices[i++] = 0 + x; // x
			vertices[i++] = 0 + y; // y
			vertices[i++] = 0; // z
			textureCoords[j++] = 12.0f * 0.0625f + 0.001f; // x
			textureCoords[j++] = 12.0f * 0.0625f - 0.001f; // y

			vertices[i++] = 0 + x + 1; // x
			vertices[i++] = 0 + y; // y
			vertices[i++] = 0; // z
			textureCoords[j++] = 13.0f * 0.0625f - 0.001f; // x
			textureCoords[j++] = 12.0f * 0.0625f - 0.001f; // y

			vertices[i++] = 0 + x + 1; // x
			vertices[i++] = 0 + y + 1; // y
			vertices[i++] = 0; // z
			textureCoords[j++] = 13.0f * 0.0625f - 0.001f; // x
			textureCoords[j++] = 11.0f * 0.0625f + 0.001f; // y

			indices[k++] = l;
			indices[k++] = l + 1;
			indices[k++] = l + 2;
			indices[k++] = l;
			indices[k++] = l + 2;
			indices[k++] = l + 3;
			l += 4;
		}

	vao.load(indices, indexSize, pos, posSize, vertices, size * 3, textureCoords, size * 2);
}

void Level::draw() {
	vao.bind();
	setTexure(tileset);
	glDrawElements(GL_TRIANGLES, vao.count(), GL_UNSIGNED_SHORT, (GLvoid*)0);
}