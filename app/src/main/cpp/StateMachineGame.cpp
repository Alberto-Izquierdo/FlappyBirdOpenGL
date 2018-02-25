#include "StateMachineGame.h"
#include "StateGameInit.h"
#include "StateGamePlaying.h"
#include "StateGameOver.h"
#include "Game.h"

StateMachineGame::StateMachineGame()
	: m_pCurrentState(nullptr)
	, m_pNextState(nullptr)
{
	InitStates();
}

StateMachineGame::~StateMachineGame()
{
	m_pCurrentState = nullptr;
	m_pNextState = nullptr;
	ClearStates();
}

void StateMachineGame::Init(Game* _pGame, StateID _eState)
{
	m_pCurrentState = m_mStates[_eState];
	m_pCurrentState->OnEnter(_pGame);
}

void StateMachineGame::Update(Game* _pGame, float _fDelta)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(_pGame, _fDelta);

		if (m_pNextState != nullptr)
		{
			m_pCurrentState->OnExit(_pGame);
			m_pCurrentState = m_pNextState;
			m_pCurrentState->OnEnter(_pGame);
			m_pNextState = nullptr;
			_pGame->ResetTimeInCurrentState();
		}
	}
}

void StateMachineGame::Render(Game* _pGame)
{
	m_pCurrentState->Render(_pGame);
}

void StateMachineGame::OnScreenTouched(Game* _pGame)
{
	m_pCurrentState->OnScreenTouched(_pGame);
}

void StateMachineGame::SwitchState(StateID _eState)
{
	m_pNextState = m_mStates[_eState];
}

void StateMachineGame::InitStates()
{
	m_mStates[StateID::INIT] = new StateGameInit();
	m_mStates[StateID::PLAYING] = new StateGamePlaying();
	m_mStates[StateID::OVER] = new StateGameOver();
}

void StateMachineGame::ClearStates()
{
	for (auto it = m_mStates.begin(); it != m_mStates.end(); ++it)
	{
		delete (*it).second;
	}

	m_mStates.clear();
}

StateID StateMachineGame::GetCurrentState() const
{
	return m_pCurrentState->GetStateID();
}
