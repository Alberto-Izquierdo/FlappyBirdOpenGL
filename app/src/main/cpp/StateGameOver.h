#ifndef STATEGAMEOVER_H
#define STATEGAMEOVER_H

#include "State.h"
class Game;

class StateGameOver : public State
{
public:
	StateGameOver();
	~StateGameOver();

	void OnEnter(Game* _pGame) override;
	void OnExit(Game* _pGame) override;
	void OnScreenTouched(Game* _pGame) override;
	void Update(Game* _pGame, float _fDeltaTime) override;
};

#endif
