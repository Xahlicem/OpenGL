#version 120

attribute vec3 vertexPos;
attribute vec2 textureCoords;

varying vec2 texCoords;

uniform mat4 projection;

void main() {
	texCoords = textureCoords;
	gl_Position = projection * vec4(vertexPos, 1);
}