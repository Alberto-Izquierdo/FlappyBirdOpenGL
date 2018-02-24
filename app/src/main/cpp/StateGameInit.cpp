#include "StateGameInit.h"
#include "Game.h"


StateGameInit::StateGameInit()
	: State()
{
}

StateGameInit::~StateGameInit()
{
}

void StateGameInit::OnEnter(Game* _pGame)
{
	_pGame->InitPlayer();
}

void StateGameInit::OnExit(Game* _pGame)
{
	
}

void StateGameInit::OnScreenTouched(Game* _pGame)
{
	_pGame->GetStateMachine()->SwitchState(StateID::PLAYING);
}

void StateGameInit::Update(Game* _pGame, float _fDeltaTime)
{

}
