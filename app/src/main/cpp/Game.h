//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>

class Renderer;
class Entity;
class Player;
class PipeFactory;

class Game {
public:
    Game();
	~Game();
	void Update();
	void Render();
	void HandleScreenTouched();
private:
	unsigned int m_iLastFrameTimeMiliSecs;
	Renderer* m_pRenderer;
	Player* m_pPlayer;
	std::vector<Entity*> m_vEntities;
	PipeFactory* m_pPipeFactory;
};


#endif //GAME_GAME_H
