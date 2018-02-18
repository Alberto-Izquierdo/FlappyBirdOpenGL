#include "Player.h"

Player::Player()
	: Entity()
	, m_fYVelocity(0.f)
{
    m_fX = 100.f;
    m_fY = k_fInitialPosition;
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

void Player::Jump()
{
	m_fYVelocity = k_fJumpVelocity;
}

void Player::ResetPosition()
{
	m_fY = k_fInitialPosition;
	m_fYVelocity = 0.f;
}

const float Player::k_fGravity = -40.f;
const float Player::k_fJumpVelocity = 19.f;
const float Player::k_fInitialPosition = 1000.f;
