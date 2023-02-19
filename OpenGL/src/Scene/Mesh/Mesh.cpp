#include "Mesh.h"

Mesh::Mesh() 
{}

Mesh Mesh::createPlane()
{
	std::vector<Vertex> vertices = {{{0.f,0.f,0.f}, {}, {0.f, 0.f}},
					  { {0.f,1.f,0.f}, {}, {0.f, 1.f}},
					  { {1.f,0.f,0.f}, {}, {1.f, 0.f}},
					  { {1.f,1.f,0.f}, {}, {1.f, 1.f}} };
	std::vector<unsigned int> indices = { 0, 1, 1, 1 };
	return Mesh(vertices, indices);
}

Mesh Mesh::createCube()
{


	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};
	//return Mesh(vertices, indices)
	return  Mesh();
}

Mesh::Mesh(std::vector<Vertex> vert, std::vector<unsigned int> ind)
	: vertices(vert), indices(ind)
{
	SetupMesh();
}

Mesh::~Mesh()
{

}

Mesh::Mesh(const Mesh& mesh)
{
	vertices = std::vector(mesh.vertices.begin(), mesh.vertices.end());
	indices = std::vector(mesh.indices.begin(), mesh.indices.end());
	matInd = mesh.matInd;


	SetupMesh();
}

Mesh::Mesh(Mesh&& rhs) noexcept
	: vertices(std::exchange(rhs.vertices, std::vector<Vertex>())),
	indices(std::exchange(rhs.indices, std::vector<unsigned int>())),
	matInd(std::exchange(rhs.matInd, -1)),
	va(std::move(rhs.va)),
	ib(std::move(rhs.ib)),
	vb(std::move(rhs.vb)),
	vbl(std::move(rhs.vbl))
{

}

void Mesh::Bind() const
{
	va.Bind();
}

void Mesh::SetupMesh()
{
	va.Bind();
	vb.setupData(vertices.data(), vertices.size() * sizeof(Vertex));
	ib.setupData(indices.data(), indices.size());
	auto s = sizeof(Vertex);

	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);
	va.AddBuffer(vb, vbl);
	va.Unbind();
}

void Mesh::InitMesh()
{

}

Mesh& Mesh::operator=(const Mesh& rhs)
{
	if (this == &rhs)
		return *this;

	vertices.clear();
	indices.clear();

	vertices = std::vector<Vertex>(rhs.vertices.begin(), rhs.vertices.end());
	indices = std::vector<unsigned int>(rhs.indices.begin(), rhs.indices.end());


}
