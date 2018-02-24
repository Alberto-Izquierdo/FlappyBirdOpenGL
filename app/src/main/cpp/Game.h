//
// Created by Alberto on 15/02/2018.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <cstdint>

class Renderer;
class Entity;
class Player;
class PipeFactory;
class StateMachineGame;
class CollisionDetectionManager;

class Game {
public:
    Game();
	~Game();
	void Update();
	void UpdatePlayer(float _fDelta);
	void UpdatePipes(float _fDelta);
	void Render();
	void RenderPopup(bool _bStart);
	void HandleScreenTouched();
	StateMachineGame* GetStateMachine() { return m_pStateMachine; };
	void InitPlayer();

	void ClearPipes();
	void Jump();
	float GetTimeInCurrentState() { return m_fTimeInCurrentState; };
	void ResetTimeInCurrentState() { m_fTimeInCurrentState = 0;};
	bool IsPlayerCollidingWithPipes();
	bool IsPlayerOutOfTheScreen();

    static int LoadImage(const char* _pFileName);
private:
	StateMachineGame* m_pStateMachine;
	unsigned int m_iLastFrameTimeMiliSecs;
	float m_fTimeInCurrentState;
	Renderer* m_pRenderer;
	CollisionDetectionManager* m_pCollisionManager;
	Player* m_pPlayer;
	std::vector<Entity*> m_vEntities;
	PipeFactory* m_pPipeFactory;
};


#endif //GAME_GAME_H
