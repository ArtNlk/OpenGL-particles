#version 330 core
in vec3 vertex;
in vec3 vertexNormal;
out vec3 vPos;
out vec3 vNorm;
uniform mat4 cameraMatrix;
uniform vec3 camPos;
uniform float pointSize;
void main(void)
{
    gl_Position = cameraMatrix * vec4(vertex,1.0f);
    vPos = vertex;
    vNorm = normalize(vertexNormal);
}
