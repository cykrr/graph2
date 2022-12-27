#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 m;

uniform vec4 color;

void main()
{
	gl_Position = m*vec4(aPos, 1.0f);
}
