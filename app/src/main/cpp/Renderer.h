//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

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
};


#endif //GAME_RENDERER_H
