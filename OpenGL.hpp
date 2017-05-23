#pragma once
#ifndef OPEN_GL_HPP
#define OPEN_GL_HPP

int init();
void loop();
void close();
void centerWindow();
void keyCall(struct GLFWwindow*, int, int, int, int);
void showFPS();
void error(const char* text);

#endif