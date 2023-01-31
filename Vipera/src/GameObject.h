#pragma once

#include <vector>

namespace Vipera
{
	class GameObject
	{
	public:
		struct Vertex
		{
			float pos[3];
			float color[4];
			float uv[2];
		};

		GameObject(std::vector<Vertex> vertices, std::vector<int> indices);

		static GameObject generate_pyramid();

	private:
		std::vector<Vertex> vertices;
		std::vector<int> indices;
	};
}

