#include "Player.h"

Player::Player()
	: m_fYVelocity(0.f)
{
	m_iWidth = m_iHeight = 20;
}

Player::~Player()
{
}

void Player::Update(float _fDeltaTime)
{
	m_fYVelocity += k_fGravity * _fDeltaTime;
	m_fY += m_fYVelocity;
}

const float Player::k_fGravity = -9.8f;
