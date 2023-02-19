#include "Camera.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace Vipera {

	glm::mat4& Camera::GetView() const
	{
        /*
                    |Rx Ry Rz 0|   |1 0 0 -Px|   |Rx Ry Rz -(Rx * Px + Ry * Py + Rz * Pz)|
        LookAt =	|Ux Uy Uz 0| * |0 1 0 -Py| = |Ux Uy Uz -(Ux * Px + Uy * Py + Uz * Pz)|
                    |Dx Dy Dz 0|   |0 0 1 -Pz|   |Dx Dy Dz -(Dx * Px + Dy * Py + Dz * Pz)|
                    |0  0  0  1|   |0 0 0  1 |   |0  0  0    1                           |

        */
        view = glm::lookAt(position,
                           position + target,
                           up);
		return view;
	}

    void Camera::SetEyeInShader(const std::shared_ptr<Shader>& shader) const
	{
        glm::vec3 eye = position + target;
        shader->SetUniform3f("u_CameraPos", eye.x, eye.y, eye.z);
    }

    void Camera::SetRotation(glm::vec2& rotationVec)
    {
        
        yaw += rotationVec.x;
        pitch += rotationVec.y;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        target = glm::normalize(direction);
    }

    void Camera::Right()
    {
        glm::vec3 Right = glm::normalize(glm::cross(up, target));
        Right.x *= stepSpeed;
        Right.y *= stepSpeed;
        Right.z *= stepSpeed;
        position += Right;
    }

    void Camera::Left()
    {
        glm::vec3 Left = glm::normalize(glm::cross(target, up));
        Left.x *= stepSpeed;
        Left.y *= stepSpeed;
        Left.z *= stepSpeed;
        position += Left;
    }

    void Camera::Forward()
    {
        glm::vec3 m_Target = glm::vec3(target.x * stepSpeed,
                                       target.y * stepSpeed,
                                       target.z * stepSpeed);
        position += m_Target;
    }

    void Camera::Back()
    {
        glm::vec3 m_Target = glm::vec3(target.x * stepSpeed,
                                       target.y * stepSpeed,
                                       target.z * stepSpeed);
        position -= m_Target;
    }
}
