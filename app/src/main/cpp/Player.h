#ifndef Player_H
#define Player_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	virtual ~Player();

	void Update(float _fDeltaTime) override;

	bool IsFinished() override { return false; };

	void ScreenTouched();

protected:
	float m_fYVelocity;
	const static float k_fGravity;
	const static float k_fJumpVelocity;
};

#endif
