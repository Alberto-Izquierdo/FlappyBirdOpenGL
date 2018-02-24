#ifndef StateMachineGame_H
#define StateMachineGame_H

#include <map>

enum StateID {
	INIT,
	PLAYING,
	OVER
};

class State;
class Game;

class StateMachineGame
{
public:
	StateMachineGame();
	~StateMachineGame();

	void Init(Game* _pGame, StateID);

	void Update(Game* _pGame, float _fDelta);
	void Render(Game* _pGame);
	void OnScreenTouched(Game* _pGame);

	void SwitchState(StateID _eState);
	void InitStates();
	void ClearStates();

protected:
	State* m_pCurrentState;
	State* m_pNextState;
	std::map<StateID, State*> m_mStates;
};

#endif
