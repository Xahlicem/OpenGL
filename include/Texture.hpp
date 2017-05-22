#ifndef TEXTURE_HPP
#define TEXTURE_HPP

extern GLuint texture_frog;
// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

void loadTextures();
void setTexure(GLuint texture);

#endif