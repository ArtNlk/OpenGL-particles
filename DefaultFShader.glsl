#version 330 core
out vec4 fragColor;
in vec3 vPos;
uniform vec3 camPos;

void main(void)
{
    fragColor = vec4(1.0f*vPos.x + 1.0f, 1.0f*vPos.y + 1.0f, 1.0f*vPos.z + 1.0f, 1.0f);
    //fragColor = vec4(5.f*distance(camPos,vPos),5.f*distance(camPos,vPos),5.f*distance(camPos,vPos),1.f);
}
