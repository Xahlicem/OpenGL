#ifndef TEXTURE_HPP
#define TEXTURE_HPP

GLuint texture_frog;
// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

void loadTextures() {
	texture_frog = loadDDS("res/FROG.DDS");
}

#endif