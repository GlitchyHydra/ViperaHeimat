#pragma once

#include <memory>

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "abstractions/Shader.h"

namespace Vipera {

	struct BaseLight
	{
		glm::vec4 Color;
		float AmbientIntensity;
		float DiffuseIntensity;
		float SpecularIntensity;

		BaseLight()
		{
			Color = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			AmbientIntensity = 0.0005f;
			DiffuseIntensity = 0.2f;
			SpecularIntensity = 0.3f;
		}
	};

	struct DirectionalLight : BaseLight
	{
		glm::vec3 Direction{ 1000.f, 500.f, -50.0f };

		DirectionalLight()
		{
			Direction = glm::vec3(960.0f, 550.0f, -50.0f);
		}
	};

	struct PointLight : BaseLight
	{
		glm::vec3 Position;

		struct
		{
			float Constant;
			float Linear;
			float Exp;
		} Attenuation;

		PointLight()
		{
			Position = glm::vec3(0.0f, 0.0f, 0.0f);
			Attenuation.Constant = 0.0001f;
			Attenuation.Linear = 0.00001f;
			Attenuation.Exp = 0.00001f;
		}
	};

	class Light {
	public:
		Light();
		void Init(Shader& shader);
		void SetDirectLights(const std::shared_ptr<Shader>& shader);
		void SetPointLights(const std::shared_ptr<Shader>& shader);
		void SetPositionAndColor(const std::shared_ptr<Shader>& shader, unsigned int index);
		
		std::vector<DirectionalLight>& GetDirectLight() { return lightsDir; }
		std::vector<PointLight>& GetPointLight() { return lightsPoint; }

	private:
		std::vector<DirectionalLight> lightsDir;
		std::vector<PointLight> lightsPoint;

		const unsigned int lightsDirCount = 2;
		const unsigned int lightsPointCount = 3;
	};
};
