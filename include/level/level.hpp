#pragma once
#ifndef LEVEL_HPP
#define LEVEL_HPP

class Level {
public:
	~Level();
	Level();
	Level(int width, int height, GLuint tileset);

	void load(int width, int height, GLuint tileset);

	void draw();
private:
	int width = 0, height = 0;
	GLuint tileset = 0;
	VertexArrayObject vao;
	GLushort *indices;
	GLfloat *pos, *vertices, *textureCoords;

	void loadVao();
};

#endif