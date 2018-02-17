//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

enum GLShader
{
	VERTEX,
	FRAGMENT
};

struct Vertex
{
	int m_vPosition[2];
	unsigned char m_vColor[4];
};

class Entity;

class Renderer {
public:
	Renderer();
	~Renderer();

	void PreRender();
	void Render(Entity* _pEntity);
private:
	unsigned int m_iProgram;
	unsigned int m_iPosAttrib;
	unsigned int m_iColoAttrib;
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	Vertex QUAD[4];
	unsigned int m_vIndices[6];

	unsigned int CreateShader(const char* _pSource, GLShader _eShaderType);
	void CreateProgram(unsigned int _iVertexShader, unsigned int _iFragmentShader);
	void InitBuffers();
	void DeleteBuffers();
	void InitAttribPointers();
};


#endif //GAME_RENDERER_H
