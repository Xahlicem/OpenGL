#ifndef VERTEX_OBJECT_HPP
#define VERTEX_OBJECT_HPP

class VertexBufferObject {
public:
	VertexBufferObject(const int* data, int ptrSize);
	VertexBufferObject(const float* data, int axes, int ptrSize);

	 int type, size;

	static void bind(int target, GLuint id);
	void bind();
	void unbind();
private:
	GLuint id;
	int target, pSize;
	void setData(const int* data);
	void setData(const float* data);
};

class VertexArrayObject {
public:
	VertexArrayObject(int* index, int indexSize, float* vertices, int verticesSize, float* textureCoords, int textureCoordsSize);

	static void bind(GLuint id);
	void bind();
	void unbind();

	int count();

	VertexBufferObject addArray(float* data, int dataSize, int size);
	VertexBufferObject addArray(VertexBufferObject vbo);
	VertexBufferObject addIndex(int* index, int indexSize);

	void enableArray(int i);
	void disableArray(int i);
private:
	GLuint id;
	int arrays = 0;
	int length;
};

#endif