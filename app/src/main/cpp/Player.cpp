#include "Player.h"

Player::Player()
	: Entity()
	, m_fYVelocity(0.f)
{
    m_fX = 100.f;
    m_fY = 1000.f;
	m_fWidth = 100.f;
	m_fHeight = 100.f;
    m_Color[0] = 1.0f;
}

Player::~Player()
{
}

void Player::Update(float _fDeltaTime)
{
	m_fYVelocity += k_fGravity * _fDeltaTime;
	m_fY += m_fYVelocity;
}

void Player::ScreenTouched()
{
	m_fYVelocity = k_fJumpVelocity;
}

const float Player::k_fGravity = -40.f;
const float Player::k_fJumpVelocity = 19.f;
