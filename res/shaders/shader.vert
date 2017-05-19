#version 130

in vec3 vertexPos;
in vec2 textureCoords;

out vec2 texCoords;

uniform mat4 projection;

void main() {
	texCoords = textureCoords;
	gl_Position = projection * vec4(vertexPos, 1);
}