#include "Pipe.h"
#include "Constants.h"

Pipe::Pipe(float _fY, bool _bBottom)
	: Entity()
	, m_bIsBottom(_bBottom)
{
	m_Color[1] = 1.f;
	m_fWidth = 200.f;
	m_fHeight = Constants::k_fWorldHeight;
	m_fX = Constants::k_fWorldWidth;
	m_fY = _fY;
}

Pipe::~Pipe()
{
}

void Pipe::Update(float _fDeltaTime)
{
	m_fX += k_fPipeSpeed * _fDeltaTime;
}

bool Pipe::IsFinished()
{
	if (m_fX < -m_fWidth)
	{
		return true;
	}
	
	return false;
}

const float Pipe::k_fPipeSpeed = -300.f;
