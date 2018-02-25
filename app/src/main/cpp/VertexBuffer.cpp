#include <GLES3/gl3.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float* _pPositions, float* _pTexCoords)
{
	for (unsigned int i = 0; i < 6; ++i)
	{
		m_vertices[i].m_vPosition[0] = _pPositions[i * 2];
		m_vertices[i].m_vPosition[1] = _pPositions[i * 2 + 1];
		m_vertices[i].m_vTexCoord[0] = _pTexCoords[i * 2];
		m_vertices[i].m_vTexCoord[1] = _pTexCoords[i * 2 + 1];
	}

	glGenBuffers(1, &m_iRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_iRendererID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_iRendererID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_iRendererID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
