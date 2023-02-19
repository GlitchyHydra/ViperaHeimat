#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	VertexBuffer(const VertexBuffer& rhs) = delete;
	VertexBuffer(VertexBuffer&& rhs) noexcept;

	void setupData(const void* data, unsigned int size) const;
	void Bind() const;
	void Unbind() const;
};

