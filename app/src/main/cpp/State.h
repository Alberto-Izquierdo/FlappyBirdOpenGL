#ifndef State_H
#define State_H

class Game;

#include "StateMachineGame.h"

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void OnEnter(Game* _pGame) = 0;
	virtual void OnExit(Game* _pGame) = 0;
	virtual void OnScreenTouched(Game* _pGame) = 0;
	virtual void Update(Game* _pGame, float _fDeltaTime) = 0;

protected:
};

#endif
