#ifndef VERTEX_OBJECT_HPP
#define VERTEX_OBJECT_HPP

class VertexBufferObject {
public:
	VertexBufferObject(const GLuint* data, GLsizeiptr ptrSize);
	VertexBufferObject(const GLfloat* data, GLuint axes, GLsizeiptr ptrSize);

	GLuint size;
	GLenum type;

	static void bind(GLuint target, GLuint id);
	GLuint bind();
	GLuint unbind();
private:
	GLuint id;
	GLenum target;
	GLsizeiptr pSize;
	void setData(const GLuint* data);
	void setData(const GLfloat* data);
};

class VertexArrayObject {
public:
	~VertexArrayObject();
	VertexArrayObject(GLuint* index, GLsizeiptr indexSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize);


	static void bind(GLuint id);
	GLuint bind();
	GLuint unbind();

	int count();

	VertexBufferObject addArray(GLfloat* data, GLuint dataSize, GLsizeiptr size);
	VertexBufferObject addArray(VertexBufferObject vbo);
	VertexBufferObject addIndex(GLuint* index, GLsizeiptr indexSize);

	void enableArray(GLuint i);
	void disableArray(GLuint i);
private:
	GLuint id, vertId, textId, indexId;
	GLuint arrays = 0;
	GLuint length;
};

#endif