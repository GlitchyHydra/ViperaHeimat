#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_trans;
uniform mat4 u_MVP;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 model_WP;

void main()
{
	gl_Position = u_MVP * position;
	v_normal = (u_MVP * vec4(normal, 0.0)).xyz;
	model_WP = (u_trans * position).xyz;
	v_texCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 model_WP;

struct Material_ {
	sampler2D Diffuse;
	sampler2D Specular;
	float Schininess;
};

struct BaseLight
{
	vec4 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
	float SpecularIntensity;
};

struct DirectLight
{
	BaseLight Base;
	vec3 Direction;
};

struct Attenuation
{
	float Constant;
	float Linear;
	float Exp;
};

struct PointLight
{
	BaseLight Base;
	vec3 Position;

	Attenuation Atten;
};

const unsigned int LIGHTS_DIR_COUNT = 2u;
const unsigned int LIGHTS_POINT_COUNT = 3u;

uniform vec3 u_CameraPos;
uniform Material_ Material;
uniform DirectLight m_directLight[LIGHTS_DIR_COUNT];
uniform PointLight m_pointLight[LIGHTS_POINT_COUNT];


void main()
{
	color = vec4(0.5, 0.5, 0.5, 1.0);
};