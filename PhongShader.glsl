#version 330 core
out vec4 fragColor;
in vec3 vPos;
in vec3 vNorm;
uniform vec3 camPos;
uniform vec4 ambientLight;
uniform vec4 objectColor;
uniform vec3 sunDir;
uniform vec4 sunColor;

void main(void)
{
    //fragColor = vec4(vNorm.xyz,1.f);
    vec3 ambient = ambientLight.xyz;
    vec3 diffuse = sunColor.xyz * max(dot(vNorm, normalize(sunDir)), 0.0);
    fragColor = vec4((ambient+diffuse)*objectColor.xyz,1.f);
}
