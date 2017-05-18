#include "OpenGL.hpp"


int main() {
	if (!init()) return -1;

	loop();

	close();
	return 0;
}

