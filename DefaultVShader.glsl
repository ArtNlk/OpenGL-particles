attribute vec4 vertex;
uniform mat4 cameraMatrix;

void main(void)
{
    gl_Position = cameraMatrix * vertex;
}
