#include "Pipe.h"
#include "Constants.h"

Pipe::Pipe()
	: Entity()
{
	m_Color[1] = 1.f;
	m_fWidth = 600.f;
	m_fHeight = 1000.f;
	m_fX = Constants::k_fWorldWidth;
	m_fY = 300.f;
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

const float Pipe::k_fPipeSpeed = -100.f;
