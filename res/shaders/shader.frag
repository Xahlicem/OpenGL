#version 330

uniform sampler2D sampler;

//out vec2 texCoords;
in vec2 texCoords;

out vec4 fragColor;

void main() {
	fragColor  = vec4(0, 1, 0, 1);//texture(sampler, texCoords);
}