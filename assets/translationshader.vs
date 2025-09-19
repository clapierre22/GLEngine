#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 Translation;

void main()
{
    gl_Position = Translation * vec4(Position, 1.0);
}