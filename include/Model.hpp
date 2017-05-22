#ifndef MODEL_HPP
#define MODEL_HPP

class Model {
public:
	Model();
	Model(float xPos, float yPos, float width, float height, float z, const GLuint textureId);
	Model(const VertexArrayObject v, const GLuint textureId);
	void draw();
	VertexArrayObject getVao();
	GLuint getTextureId();
private:
	VertexArrayObject vao;
	GLuint texture, vaoId;
};

#endif