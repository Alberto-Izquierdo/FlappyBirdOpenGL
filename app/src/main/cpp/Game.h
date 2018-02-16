//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>

class Renderer;
class Entity;

class Game {
public:
    Game();
	void Update();
	void Render();
private:
	unsigned int m_iLastFrameTimeMiliSecs;
	Renderer* m_pRenderer;
	Entity* m_pPlayer;
	std::vector<Entity*> m_vEntities;
};


#endif //GAME_GAME_H
