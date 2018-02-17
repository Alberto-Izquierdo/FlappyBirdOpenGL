#include "Player.h"

Player::Player()
	: m_fYVelocity(0.f)
{
    m_fX = -0.5f;
    m_fY = -0.5f;
	m_fWidth = m_fHeight = 1.f;
    m_Color[0] = 1.0f;
}

Player::~Player()
{
}

void Player::Update(float _fDeltaTime)
{
	//m_fYVelocity += k_fGravity * _fDeltaTime;
	//m_fY += m_fYVelocity;
}

const float Player::k_fGravity = -9.8f;
