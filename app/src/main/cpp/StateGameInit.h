#ifndef StateGameInit_H
#define StateGameInit_H

#include "State.h"
class Game;

class StateGameInit : public State
{
public:
	StateGameInit();
	~StateGameInit();

	void OnEnter(Game* _pGame) override;
	void OnExit(Game* _pGame) override;
	void OnScreenTouched(Game* _pGame) override;
	void Update(Game* _pGame, float _fDeltaTime) override;
	void Render(Game* _pGame) override;
};

#endif
