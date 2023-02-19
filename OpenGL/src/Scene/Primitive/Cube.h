#pragma once

#include "abstractions/VertexArray.h"
#include "abstractions/VertexBuffer.h"
#include "abstractions/VertexBufferLayout.h"


struct Vertex {
	glm::vec3 pos;
	glm::vec2 tex_pos;
	glm::vec3 normal;
};

class Cube
{
public:
	 //position, texCoord, normal
	const Vertex vertexInfo[8]  {
				  Vertex {glm::vec3(-50.5f,  50.5f,  50.5f),	glm::vec2(0.f, 1.f), glm::vec3(0.0f, 0.0f, 0.0f)},
				  Vertex {glm::vec3(-50.5f, -50.5f,  50.5f),	glm::vec2(0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f)},
				  Vertex {glm::vec3( 50.5f, -50.5f,  50.5f),	glm::vec2(1.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f)},
				  Vertex {glm::vec3( 50.5f,  50.5f,  50.5f),	glm::vec2(1.f, 1.f), glm::vec3(0.0f, 0.0f, 0.0f)},

				  Vertex {glm::vec3( 50.5f,  50.5f, -50.5f),	glm::vec2(0.f, 1.f), glm::vec3(0.0f, 0.0f, 0.0f)},
				  Vertex {glm::vec3( 50.5f, -50.5f, -50.5f),	glm::vec2(0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f)},
				  Vertex {glm::vec3(-50.5f, -50.5f, -50.5f),	glm::vec2(1.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f)},
				  Vertex {glm::vec3(-50.5f,  50.5f, -50.5f),	glm::vec2(1.f, 1.f), glm::vec3(0.0f, 0.0f, 0.0f)},
	};
	const unsigned int indicesInfo[36] {
		//front
		0, 1, 2,
		2, 3, 0,
		//rear
		6, 5, 7,
		6, 4, 5,
		//top
		3, 5, 2,
		3, 4, 5,
		//bottom
		0, 7, 1,
		0, 6, 1,
		//left
		0, 3, 4,
		0, 4, 6,
		//right
		1, 5, 7,
		1, 2, 5
	};
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
private:
	unsigned int sizeVertex = (3 + 2 + 3) * 8;
	unsigned int sizeIndices = 36;
	VertexBufferLayout layout;
public:
	Cube();
	~Cube() {};


};



