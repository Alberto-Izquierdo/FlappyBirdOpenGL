#include "StateGameOver.h"
#include "Game.h"


StateGameOver::StateGameOver()
	: State()
{
}

StateGameOver::~StateGameOver()
{
}

void StateGameOver::OnEnter(Game* _pGame)
{
	_pGame->Jump();
}

void StateGameOver::OnExit(Game* _pGame)
{
	_pGame->ClearPipes();
}

void StateGameOver::OnScreenTouched(Game* _pGame)
{
	if (_pGame->GetTimeInCurrentState() > 2.f)
	{
		_pGame->GetStateMachine()->SwitchState(StateID::INIT);
	}
}

void StateGameOver::Update(Game* _pGame, float _fDeltaTime)
{
	_pGame->UpdatePlayer(_fDeltaTime);
}
