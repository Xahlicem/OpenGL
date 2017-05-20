#version 330

uniform sampler2D sampler;

in vec2 texCoords;

layout(location = 0) out vec4 color;

void main() {
	color = texture(sampler, texCoords);
	if (color.a < 0.25) discard;
	//vec4 darkness = vec4(0.25f, 0.25, 0.25, 1);
	//color = color * darkness;
}