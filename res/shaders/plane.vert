#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 v;
uniform mat4 p;

out vec3 nearPoint;
out vec3 farPoint;

vec3 unprojectPoint(float x, float y, float z, mat4 v, mat4 p) {
    mat4 vi = inverse(v);
    mat4 pi = inverse(p);
    vec4 point = vi * pi * vec4(x, y, z, 1.f);
    return point.xyz / point.w;
}

void main()
{
        vec3 nearPoint = unprojectPoint(aPos.x, aPos.y, 0.f, v, p);
        vec3 farPoint = unprojectPoint(aPos.x, aPos.y, 1.f, v, p);
	gl_Position = p*v*vec4(aPos, 1.0f);
}
