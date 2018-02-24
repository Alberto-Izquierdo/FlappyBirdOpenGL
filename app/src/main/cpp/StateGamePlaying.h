#ifndef STATEGAMEPLAYING_H
#define STATEGAMEPLAYING_H

#include "State.h"
class Game;

class StateGamePlaying : public State
{
public:
	StateGamePlaying();
	~StateGamePlaying();

	void OnEnter(Game* _pGame) override;
	void OnExit(Game* _pGame) override;
	void OnScreenTouched(Game* _pGame) override;
	void Update(Game* _pGame, float _fDeltaTime) override;
	void Render(Game* _pGame) override;
};

#endif
