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
class StateMachineGame;

class Game {
public:
    Game();
	~Game();
	void Update();
	void UpdatePlayer(float _fDelta);
	void UpdatePipes(float _fDelta);
	void Render();
	void HandleScreenTouched();
	StateMachineGame* GetStateMachine() { return m_pStateMachine; };
	void InitPlayer();
	void Jump();
	float GetTimeInCurrentState();
	void ResetTimeInCurrentState() { m_fTimeInCurrentState = 0;};
private:
	StateMachineGame* m_pStateMachine;
	unsigned int m_iLastFrameTimeMiliSecs;
	float m_fTimeInCurrentState;
	Renderer* m_pRenderer;
	Player* m_pPlayer;
	std::vector<Entity*> m_vEntities;
	PipeFactory* m_pPipeFactory;
};


#endif //GAME_GAME_H
