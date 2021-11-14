#version 330 core
in vec3 vertex;
out vec3 vPos;
uniform mat4 cameraMatrix;
uniform vec3 camPos;
uniform float pointSize;
void main(void)
{
    gl_Position = cameraMatrix * vec4(vertex,1.0f);
    vPos = vertex;
    //gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);
    gl_PointSize = pointSize/(2*distance(camPos,vertex));
}
