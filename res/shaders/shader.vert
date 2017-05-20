#version 330

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 textureCoords;

out vec2 texCoords;

uniform mat4 projection;

void main() {
	texCoords = textureCoords;
	gl_Position = projection * vec4(vertexPos, 1);
}