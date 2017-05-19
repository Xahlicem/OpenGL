#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm\glm.hpp>

void loadShaders();

class Shader {
public:
	Shader();
	~Shader();

	void bind();
	int getProgram();
	void setProjection(glm::fmat4 data);
	void setProjection(GLfloat* data);
	void loadProgram(const char* vertFilePath, const char* fragFilePath);
private:
	GLuint id;
	GLuint vShader, fShader;
	GLuint projection;

	bool loadShader(const char* path, int id);
	void compileShader(const char* code, int id, const char* path);
};

extern Shader programDefault;

#endif