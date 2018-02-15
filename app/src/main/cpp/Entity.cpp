#include "Entity.h"

Entity::Entity()
	: m_fX(0.f)
	, m_fY(0.f)
{
    m_Color[0] = 0;
    m_Color[1] = 0;
    m_Color[2] = 0;
    m_Color[3] = 255;
}

Entity::~Entity()
{
}

void Entity::Update(float _fDeltaTime)
{

}
void Entity::Render()
{

}

void Entity::SetPosition(float _fX, float _fY)
{
	
}

void Entity::SetColor(unsigned char _Color[4])
{
	
}
