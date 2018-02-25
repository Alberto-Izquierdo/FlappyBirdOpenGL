#ifndef VertexBuffer_H
#define VertexBuffer_H

struct Vertex
{
	float m_vPosition[2];
	float m_vTexCoord[2];
};

class VertexBuffer
{
public:
	VertexBuffer(float* _pPositions, float* _pTexCoords);
	virtual ~VertexBuffer();

	void Bind();
	void Unbind();

protected:
	unsigned int m_iRendererID;
	Vertex m_vertices[6];
};

#endif
