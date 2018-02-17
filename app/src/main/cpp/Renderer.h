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
	float m_vPosition[2];
	float m_vColor[4];
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
	int m_iPosAttribute;
	int m_iColorAttribute;
	int m_iPosUniform;
	int m_iColorUniform;
	unsigned int m_VBO;
	Vertex m_Rectangle[6];

	unsigned int CreateShader(const char* _pSource, GLShader _eShaderType);
	void CreateProgram(unsigned int _iVertexShader, unsigned int _iFragmentShader);
	void InitBuffers();
	void DeleteBuffers();
	void GetAttribLocations();
	void FillDefaultRectangle();
};


#endif //GAME_RENDERER_H
