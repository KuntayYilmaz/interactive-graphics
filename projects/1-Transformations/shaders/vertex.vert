#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_PointSize = 1.0;
    gl_Position = projection * view * vec4(aPos, 1.0);
}