#version 330 core
out vec4 fragColor;
in vec3 vPos;
uniform vec3 camPos;

void main(void)
{
    fragColor = vec4(1.f, 0.f, 0.f, 1.0f);
}
