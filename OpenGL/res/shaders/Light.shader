#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 offset;
uniform vec4 light_pos;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * (position + light_pos);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) in vec3 light_color;

void main()
{
    color = vec4(light_color, 1.0);

};