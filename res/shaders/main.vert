#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texpos;

out vec2 tex_pos;


uniform mat4 m;
uniform mat4 vp;

uniform vec4 color;


void main()
{
  tex_pos = vec2(texpos.x, texpos.y);
	gl_Position = vp*m*vec4(aPos, 1.0f);
}
