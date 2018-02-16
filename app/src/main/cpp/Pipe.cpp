#include "Pipe.h"

Pipe::Pipe()
{
	m_Color[1] = 255;
}

Pipe::~Pipe()
{
}

void Pipe::Update(float _fDeltaTime)
{
	m_fX -= k_fPipeSpeed * _fDeltaTime;
}

const float Pipe::k_fPipeSpeed = 10.f;
