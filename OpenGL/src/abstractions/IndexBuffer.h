#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	mutable unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();

	IndexBuffer(const IndexBuffer& rhs) = delete;
	IndexBuffer(IndexBuffer&& rhs);

	void Bind() const;
	void Unbind() const;
	void setupData(const unsigned int* data, unsigned int count) const;

	inline unsigned int GetCount() const { return m_Count; }
};

