#version 330 core
out vec4 FragColor;

in vec3 aPos;

in vec3 nearPoint;
in vec3 farPoint;
out float xd;

void main()
{
        float t = -nearPoint.y / (farPoint.y - nearPoint.y);        

        FragColor = vec4(1.f, 1.f*float(t > 0), 0.f, 1.f);

}
