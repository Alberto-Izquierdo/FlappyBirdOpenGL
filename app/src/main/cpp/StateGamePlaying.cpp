#include "StateGamePlaying.h"
#include "Game.h"


StateGamePlaying::StateGamePlaying()
	: State()
{
}

StateGamePlaying::~StateGamePlaying()
{
}

void StateGamePlaying::OnEnter(Game* _pGame)
{
	_pGame->Jump();
}

void StateGamePlaying::OnExit(Game* _pGame)
{
	
}

void StateGamePlaying::OnScreenTouched(Game* _pGame)
{
	_pGame->Jump();
}

void StateGamePlaying::Update(Game* _pGame, float _fDeltaTime)
{
	_pGame->UpdatePlayer(_fDeltaTime);
	_pGame->UpdatePipes(_fDeltaTime);
}
