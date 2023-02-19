#include "Light.h"

namespace Vipera
{

	Light::Light() {
		
	}

	void Light::Init(Shader& shader)
	{
		shader.SetUniform1ui("LIGHTS_DIR_COUNT;", lightsDirCount);
		shader.SetUniform1ui("LIGHTS_POINT_COUNT", lightsPointCount);
		lightsDir.resize(lightsDirCount);
		lightsDir[1].Direction = glm::vec3(960.0f, 850.0f, -50.0f);
		lightsPoint.resize(lightsPointCount);
		lightsPoint[0].Position = glm::vec3(65.0f, 740.0f, 0.0f);
		lightsPoint[1].Position = glm::vec3(650.0f, 550.0f, 0.0f);
		lightsPoint[2].Position = glm::vec3(1150.0f, 540.0f, 0.0f);
		lightsPoint[0].AmbientIntensity = 0.0000001f;
		lightsPoint[1].AmbientIntensity = 0.0000001f;
		lightsPoint[2].AmbientIntensity = 0.0000001f;
	}

	void Light::SetDirectLights(const std::shared_ptr<Shader>& shader)
	{
		char Name[128];
		for (unsigned int i = 0; i < lightsDirCount; i++)
		{
			memset(Name, 0, sizeof(Name));
			snprintf(Name, sizeof(Name), "m_directLight[%d].Base.Color", i);
			shader->SetUniform4f(Name, lightsDir[i].Color.x, lightsDir[i].Color.y,
				lightsDir[i].Color.z, lightsDir[i].Color.w);

			snprintf(Name, sizeof(Name), "m_directLight[%d].Base.AmbientIntensity", i);
			shader->SetUniform1f(Name, lightsDir[i].AmbientIntensity);

			snprintf(Name, sizeof(Name), "m_directLight[%d].Base.DiffuseIntensity", i);
			shader->SetUniform1f(Name, lightsDir[i].AmbientIntensity);

			snprintf(Name, sizeof(Name), "m_directLight[%d].Base.SpecularIntensity", i);
			shader->SetUniform1f(Name, lightsDir[i].AmbientIntensity);

			snprintf(Name, sizeof(Name), "m_directLight[%d].Direction", i);
			shader->SetUniform3f(Name, lightsDir[i].Direction.x, lightsDir[i].Direction.y,
				lightsDir[i].Direction.z);
		}
	}

	void Light::SetPointLights(const std::shared_ptr<Shader>& shader)
	{
		char Name[128];
		for (unsigned int i = 0; i < lightsPointCount; i++)
		{
			memset(Name, 0, sizeof(Name));
			snprintf(Name, sizeof(Name), "m_pointLight[%d].Base.Color", i);
			shader->SetUniform4f(Name, lightsPoint[i].Color.x, lightsPoint[i].Color.y,
				lightsPoint[i].Color.z, lightsPoint[i].Color.w);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Base.AmbientIntensity", i);
			shader->SetUniform1f(Name, lightsPoint[i].AmbientIntensity);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Base.DiffuseIntensity", i);
			shader->SetUniform1f(Name, lightsPoint[i].AmbientIntensity);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Base.SpecularIntensity", i);
			shader->SetUniform1f(Name, lightsPoint[i].AmbientIntensity);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Direction", i);
			shader->SetUniform3f(Name, lightsPoint[i].Position.x, lightsPoint[i].Position.y,
				lightsPoint[i].Position.z);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Atten.Constant", i);
			shader->SetUniform1f(Name, lightsPoint[i].Attenuation.Constant);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Atten.Linear", i);
			shader->SetUniform1f(Name, lightsPoint[i].Attenuation.Linear);

			snprintf(Name, sizeof(Name), "m_pointLight[%d].Atten.Exp", i);
			shader->SetUniform1f(Name, lightsPoint[i].Attenuation.Exp);
		}
	}

	void Light::SetPositionAndColor(const std::shared_ptr<Shader>& shader, unsigned int index)
	{
		shader->SetUniform3f("light_pos", lightsPoint[index].Position.x,
			lightsPoint[index].Position.y, lightsPoint[index].Position.z);
		shader->SetUniform3f("light_color", lightsPoint[index].Color.x,
			lightsPoint[index].Color.y, lightsPoint[index].Color.z);
	}
};