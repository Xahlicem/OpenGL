#ifndef VERTEX_OBJECT_HPP
#define VERTEX_OBJECT_HPP

class VertexBufferObject {
public:
	~VertexBufferObject();
	VertexBufferObject();
	VertexBufferObject(GLushort* data, GLsizeiptr ptrSize);
	VertexBufferObject(GLfloat* data, GLuint axes, GLsizeiptr ptrSize);

	GLuint size;
	GLenum type;

	void load(GLushort* data, GLsizeiptr ptrSize);
	void load(GLfloat* data, GLuint axes, GLsizeiptr ptrSize);
	void load(GLfloat* data, GLuint axes, GLsizeiptr ptrSize, bool pos);

	static void bind(GLuint target, GLuint id);
	GLuint bind();
	GLuint unbind();
	GLuint rebind(const GLfloat* data);

private:
	GLuint id = 0;
	GLenum target;
	GLsizeiptr pSize;
	void setData(GLushort* data);
	void setData(GLfloat* data, bool dynamic);
};

class VertexArrayObject {
public:
	~VertexArrayObject();
	VertexArrayObject();
	VertexArrayObject(GLushort* index, GLsizeiptr indexSize, GLfloat* pos, GLsizeiptr posSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize);

	void load(GLushort* index, GLsizeiptr indexSize, GLfloat* pos, GLsizeiptr posSize, GLfloat* vertices, GLsizeiptr verticesSize, GLfloat* textureCoords, GLsizeiptr textureCoordsSize);

	static void bind(GLuint id);
	void bind();
	void unbind();

	void rebindPosition(const GLfloat* data);
	void rebindPosition(GLfloat x, GLfloat y);

	GLuint count();
	GLuint getId();

	void addArray(VertexBufferObject vbo);

	void enableArray(GLuint i);
	void disableArray(GLuint i);
private:
	GLuint id = 0;
	VertexBufferObject position, vertex, texture, indices;
	GLuint arrays = 0;
	GLsizei length;
};

#endif