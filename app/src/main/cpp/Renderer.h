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

	unsigned int CreateShader(const char* _pSource, GLShader _eShaderType);
	void CreateProgram(unsigned int _iVertexShader, unsigned int _iFragmentShader);
};


#endif //GAME_RENDERER_H
