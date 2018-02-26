//
// Created by Alberto on 15/02/2018.
//

#include "Game.h"
#include "Player.h"
#include "Pipe.h"
#include "Renderer.h"
#include "PipeFactory.h"
#include "StateMachineGame.h"
#include "CollisionDetectionManager.h"
#include "Constants.h"
#include <jni.h>
#include <time.h>
#include <cstdlib>

// Variables to call to java functions from cpp
static JNIEnv* pEnv = NULL;
static jobject pObject = NULL;

Game::Game()
	: m_iLastFrameTimeMiliSecs(0)
	, m_pPlayer(nullptr)
	, m_iScore(0)
{
	m_pStateMachine = new StateMachineGame();
	m_pStateMachine->Init(this, StateID::INIT);
	int iImageID = LoadImage("texture_map.png");
	m_pRenderer = new Renderer();
	m_pRenderer->SetTextureNumbers(iImageID);
	m_pPipeFactory = new PipeFactory(&m_vEntities);
	m_pCollisionManager = new CollisionDetectionManager();
}

Game::~Game()
{
	delete m_pRenderer;
	delete m_pPlayer;
	delete m_pPipeFactory;
	delete m_pCollisionManager;
	
	ClearPipes();
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
	StateID eCurrentState = m_pStateMachine->GetCurrentState();
	m_pRenderer->RenderBackground(eCurrentState == StateID::PLAYING ? m_fTimeInCurrentState * 0.05f : -1.f, eCurrentState == StateID::INIT);
	// Render the entities in the game
	m_pRenderer->RenderPipes(m_vEntities);
	m_pRenderer->RenderPlayer(m_pPlayer);
	m_pStateMachine->Render(this);
}

void Game::RenderPopup(bool _bStart)
{
	m_pRenderer->RenderPopup(_bStart);
}

void Game::RenderScore()
{
	m_pRenderer->RenderScore(m_iScore);
}

void Game::HandleScreenTouched()
{
	m_pStateMachine->OnScreenTouched(this);
}

void Game::SetupNewGame()
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new Player();
	}

	m_pPlayer->ResetPosition();
	ClearPipes();
	m_iScore = 0;
}

void Game::ClearPipes()
{
	for (Entity* pEntity : m_vEntities)
	{
		delete pEntity;
	}

	m_vEntities.clear();
}

void Game::Jump()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Jump();
	}
}

bool Game::IsPlayerCollidingWithPipes()
{
	return m_pCollisionManager->IsPlayerCollidingWithPipes(m_pPlayer, m_vEntities);
}

bool Game::IsPlayerOutOfTheScreen()
{
	float fY = m_pPlayer->GetY();
	float fHeight = m_pPlayer->GetHeight();

	if (fY < 0 || fY + fHeight > Constants::k_fWorldHeight)
	{
		return true;
	}

	return false;
}

void Game::UpdatePipes(float _fDelta)
{
	for (int i = 0, iSize = m_vEntities.size(); i < iSize; ++i)
	{
		Entity* pEntity = m_vEntities.at(i);
		if (pEntity->GetType() == EntityType::PIPE)
		{
			pEntity->Update(_fDelta);

			if (pEntity->IsFinished())
			{
				delete pEntity;
				m_vEntities.erase(m_vEntities.begin() + i);
				--i;
				--iSize;
			}
			else
			{
				if (pEntity->GetX() + pEntity->GetWidth() / 2 < m_pPlayer->GetX())
				{
					Pipe* pPipe = static_cast<Pipe*>(pEntity);

					if (pPipe->DoesItAddPointsToScore())
					{
						pPipe->ScoreAdded();
						AddPointsToScore(1);
					}
				}
			}
		}
	}

	m_pPipeFactory->Update(_fDelta);
}

void Game::AddPointsToScore(int _iPoints)
{
	m_iScore += _iPoints;
}

void Game::UpdatePlayer(float _fDelta)
{
	m_pPlayer->Update(_fDelta);
}

int Game::LoadImage(const char *_pFileName)
{
    jstring filename = pEnv->NewStringUTF(_pFileName);
    jclass clazz = pEnv->FindClass("com/example/project/game/GameLib");
    jmethodID methodID = pEnv->GetStaticMethodID(clazz, "LoadTexture", "(Ljava/lang/String;)I");
    jint out = pEnv->CallStaticIntMethod(clazz, methodID, filename);
	return out;
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

    pEnv = env;
    pObject = obj;

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
