#version 330 core
out vec4 FragColor;
uniform vec4 color;

in vec3 aPos;

uniform sampler2D tex;

in vec2 tex_pos;

void main()
{
	FragColor = texture(tex, tex_pos);
	// FragColor = color;
	// FragColor = vec4(1, 0, 0, 1);
}
