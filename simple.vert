#version 130

uniform mat4 projection, view;

in vec3 position;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0);
}
