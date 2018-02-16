#include "Entity.h"

Entity::Entity()
	: m_fX(0.f)
	, m_fY(0.f)
	, m_iWidth(0)
	, m_iHeight(0)
{
    m_Color[0] = 0;
    m_Color[1] = 0;
    m_Color[2] = 0;
    m_Color[3] = 255;
}

Entity::~Entity()
{
}
