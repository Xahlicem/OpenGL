#version 130

uniform sampler2D sampler;

//out vec2 texCoords;
in vec2 texCoords;

out vec4 fragColor;

void main() {
	fragColor  = texture(sampler, texCoords);
}