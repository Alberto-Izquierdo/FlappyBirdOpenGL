#include "Entity.h"
#include "Constants.h"

Entity::Entity()
	: m_fX(0.f)
	, m_fY(0.f)
	, m_fWidth(0)
	, m_fHeight(0)
	, m_fRotation(0.f)
{
    m_Color[0] = 0.f;
    m_Color[1] = 0.f;
    m_Color[2] = 0.f;
    m_Color[3] = 1.f;
}

Entity::~Entity()
{
}
