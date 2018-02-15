//
// Created by Alberto on 15/02/2018.
//

#include "Game.h"
#include "Entity.h"
#include "Renderer.h"
#include <jni.h>
#include <time.h>
Game::Game()
        : m_iLastFrameTimeMiliSecs(0)
{
    m_pRenderer = new Renderer();
}

void Game::Update()
{
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    unsigned int iNowMiliSecs = now.tv_sec * 1000 + now.tv_nsec / 1000000;

    if (m_iLastFrameTimeMiliSecs > 0)
    {
        float fDeltaTime = (float)(iNowMiliSecs - m_iLastFrameTimeMiliSecs) / 1000.f;

        // Update the entities in the game
        for (int i = 0, iSize = m_vEntities.size(); i < iSize; ++i)
        {
            m_vEntities.at(i)->Update(fDeltaTime);
        }

        // Render the entities in the game
        for (int i = 0, iSize = m_vEntities.size(); i < iSize; ++i)
        {
            m_vEntities.at(i)->Render();
        }
    }

    m_iLastFrameTimeMiliSecs = iNowMiliSecs;
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
	return true;
}
