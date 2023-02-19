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

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
{
	vec4 AmbientColor = Light.Color * Light.AmbientIntensity;

	float DiffuseFactor = dot(-LightDirection, Normal);
	vec4 DiffuseColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 SpecularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if (DiffuseFactor > 0)
	{
		DiffuseColor = Light.Color * Light.DiffuseIntensity * DiffuseFactor;

		vec3 VertexToEye = normalize(u_CameraPos - model_WP);
		vec3 LightReflect = normalize(reflect(LightDirection, Normal));
		float SpecularFactor = dot(VertexToEye, LightReflect);
		if (SpecularFactor > 0) {
			SpecularColor = vec4(Light.Color * Light.SpecularIntensity * SpecularFactor);
		}
	}

	return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcDirLights(vec3 Normal, vec4 texSpecular)
{
	vec4 color_out = vec4(0, 0, 0, 0);
	for (unsigned int i = 0u; i < LIGHTS_DIR_COUNT; i++)
	{
		color_out += CalcLightInternal(m_directLight[i].Base, m_directLight[i].Direction, Normal);
	}
	return color_out;
}

vec4 CalcPointLights(vec3 Normal, vec4 texSpecular)
{
	vec4 color_out = vec4(0.0, 0.0, 0.0, 0.0);

	for (unsigned int i = 0u; i < LIGHTS_POINT_COUNT; i++)
	{
		vec3 LightDirection = model_WP - m_pointLight[i].Position;
		float Distance = length(LightDirection);
		LightDirection = normalize(LightDirection);

		vec4 color_intermediate = CalcLightInternal(m_pointLight[i].Base, LightDirection, Normal);
		float Attenuation_coeff = m_pointLight[i].Atten.Constant +
			                      m_pointLight[i].Atten.Linear * Distance +
			                      m_pointLight[i].Atten.Exp * Distance * Distance;
		color_out += (color_intermediate / Attenuation_coeff);
	}

	return color_out;
};

void main()
{
	vec4 texSpecular = texture(Material.Specular, v_texCoord);
	vec3 Normal = normalize(v_normal);
	vec4 ColorLight = CalcDirLights(Normal, texSpecular);
	ColorLight += CalcPointLights(Normal, texSpecular);

	color = texture2D(Material.Diffuse, v_texCoord) * ColorLight;
};