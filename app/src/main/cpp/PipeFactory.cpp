#include "PipeFactory.h"
#include "Pipe.h"
#include "Constants.h"
#include <cstdlib>

PipeFactory::PipeFactory(std::vector<Entity*>* _vPipes)
	: m_vEntities(_vPipes)
	, m_fTimeSinceLastPipeSpawned(k_fTimeBetweenPipes / 2)
{
}

PipeFactory::~PipeFactory()
{
}

void PipeFactory::Update(float _fDelta)
{
	m_fTimeSinceLastPipeSpawned -= _fDelta;

	if (m_fTimeSinceLastPipeSpawned < 0)
	{
		// Create top and bot pipes
		int iPipesPosition = (std::rand() % (int)(Constants::k_fWorldHeight - (k_fMinimumDistanceToWindowBorder * 2 + k_fYDistanceBetweenPipes / 2))) + k_fMinimumDistanceToWindowBorder;

		float fPipePosition = iPipesPosition - k_fYDistanceBetweenPipes / 2 - Constants::k_fWorldHeight / 2;
		m_vEntities->push_back(new Pipe(fPipePosition, true));
		fPipePosition = iPipesPosition + k_fYDistanceBetweenPipes / 2 + Constants::k_fWorldHeight / 2;
		m_vEntities->push_back(new Pipe(fPipePosition, false));

		m_fTimeSinceLastPipeSpawned = k_fTimeBetweenPipes;
	}
}

const float PipeFactory::k_fTimeBetweenPipes = 2.f;
const float PipeFactory::k_fYDistanceBetweenPipes = 430;
const float PipeFactory::k_fMinimumDistanceToWindowBorder = 50.f;
