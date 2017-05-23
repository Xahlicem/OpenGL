#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
public:
	Model();
	Model(float xPos, float yPos, float width, float height, float z, const GLuint textureId);
	void load(float xPos, float yPos, float width, float height, float z, const GLuint textureId);
	void draw();
	GLuint getTextureId();
	VertexArrayObject vao;
private:
	GLuint texture;
	GLfloat position[8];
};

#endif