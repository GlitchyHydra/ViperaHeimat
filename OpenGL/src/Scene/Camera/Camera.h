#pragma once

#include <memory>

#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "abstractions/Shader.h"

namespace Vipera {
	class Camera
	{
	public:
		glm::mat4& GetView() const;
		const glm::vec3 GetPosition() const { return position; }

		void SetEyeInShader(const std::shared_ptr<Shader>& shader) const;
		void SetRotation(glm::vec2& rotationVec);

		void Right();
		void Left();
		void Forward();
		void Back();

	private:
		glm::vec3 position { 0.0f, 0.0f,  0.0f };
		glm::vec3 target   { 0.0f, 0.0f, -1.0f };
		glm::vec3 up       { 0.0f, 1.0f,  0.0f };
		mutable glm::mat4 view = glm::lookAt(position,
										     position + target,
									         up);
		float stepSpeed = 5.0f;
		float yaw = 0.0f, pitch = 0.0f;
	};
};