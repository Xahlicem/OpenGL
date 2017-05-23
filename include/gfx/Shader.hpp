#ifndef SHADER_HPP
#define SHADER_HPP

void loadShaders();

class Shader {
public:
	Shader();
	~Shader();

	void bind();
	int getProgram();
	void setProjection(const GLfloat* data);
	void setSampler(GLuint i);
	void loadProgram(const char* vertFilePath, const char* fragFilePath);
private:
	GLuint id;
	GLuint vShader, fShader;
	GLuint projection, sampler;

	bool loadShader(const char* path, GLuint id);
	void compileShader(const char* code, GLuint id, const char* path);
};

extern Shader programDefault;

#endif