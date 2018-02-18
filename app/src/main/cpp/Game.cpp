//
// Created by Alberto on 15/02/2018.
//

#include "Game.h"
#include "Player.h"
#include "Pipe.h"
#include "Renderer.h"
#include "PipeFactory.h"
#include "StateMachineGame.h"
#include <jni.h>
#include <time.h>
#include <cstdlib>

Game::Game()
	: m_iLastFrameTimeMiliSecs(0)
	, m_pPlayer(nullptr)
{
	m_pStateMachine = new StateMachineGame();
	m_pStateMachine->Init(this, StateID::INIT);
    m_pRenderer = new Renderer();
	m_pPipeFactory = new PipeFactory(&m_vEntities);
}

Game::~Game()
{
	delete m_pRenderer;
	delete m_pPlayer;
	delete m_pPipeFactory;

	for (Entity* pEntity : m_vEntities)
	{
		delete pEntity;
	}

	m_vEntities.clear();
}

void Game::Update()
{
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    unsigned int iNowMiliSecs = now.tv_sec * 1000 + now.tv_nsec / 1000000;

    if (m_iLastFrameTimeMiliSecs > 0)
    {
        float fDeltaTime = (float)(iNowMiliSecs - m_iLastFrameTimeMiliSecs) / 1000.f;
		m_fTimeInCurrentState += fDeltaTime;

		m_pStateMachine->Update(this, fDeltaTime);

		Render();
    }

    m_iLastFrameTimeMiliSecs = iNowMiliSecs;
}

void Game::Render()
{
	// Clean the screen
	m_pRenderer->PreRender();
	// Render the entities in the game
	for (unsigned int i = 0, iSize = m_vEntities.size(); i < iSize; ++i)
	{
		m_pRenderer->Render(m_vEntities.at(i));
	}

	m_pRenderer->Render(m_pPlayer);
}

void Game::HandleScreenTouched()
{
	m_pStateMachine->OnScreenTouched(this);
}

void Game::InitPlayer()
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new Player();
	}

	m_pPlayer->ResetPosition();
}

void Game::Jump()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Jump();
	}
}

void Game::UpdatePipes(float _fDelta)
{
	for (int i = 0, iSize = m_vEntities.size(); i < iSize; ++i)
	{
		Entity* pEntity = m_vEntities.at(i);
		pEntity->Update(_fDelta);

		if (pEntity->IsFinished())
		{
			delete pEntity;
			m_vEntities.erase(m_vEntities.begin() + i);
			--i;
			--iSize;
		}
	}

	m_pPipeFactory->Update(_fDelta);
}

void Game::UpdatePlayer(float _fDelta)
{
	m_pPlayer->Update(_fDelta);
}

static Game* pGame = NULL;

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_project_game_GameLib_init(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_example_project_game_GameLib_resize(JNIEnv* env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_example_project_game_GameLib_step(JNIEnv* env, jobject obj);
    JNIEXPORT bool JNICALL Java_com_example_project_game_GameLib_touch(JNIEnv* env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_example_project_game_GameLib_init(JNIEnv* env, jobject obj)
{
	std::srand(time(nullptr));

	if (pGame != NULL)
	{
		delete pGame;
	}

	pGame = new Game();
}
JNIEXPORT void JNICALL Java_com_example_project_game_GameLib_resize(JNIEnv* env, jobject obj, jint width, jint height)
{

}
JNIEXPORT void JNICALL Java_com_example_project_game_GameLib_step(JNIEnv* env, jobject obj)
{
	pGame->Update();
}
JNIEXPORT bool JNICALL Java_com_example_project_game_GameLib_touch(JNIEnv* env, jobject obj)
{
	pGame->HandleScreenTouched();
	return true;
}
