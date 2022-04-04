#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 v;
uniform mat4 p;

void main()
{
	gl_Position = p * v * vec4(aPos, 1.0f);
}
