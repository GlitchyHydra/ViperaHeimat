#shader vertex
#version 330 core
layout(location = 0) in vec3 Position;

uniform mat4 gMVP;

out vec3 TexCoord0;

void main()
{
    vec4 WVP_Pos = gMVP * vec4(Position, 1.0);

    gl_Position = WVP_Pos.xyww;

    TexCoord0 = Position;
}

#shader fragment
#version 330 core

in vec3 TexCoord0;

out vec4 FragColor;

uniform samplerCube gCubemapTexture;

void main()
{
    FragColor = texture(gCubemapTexture, TexCoord0);
}