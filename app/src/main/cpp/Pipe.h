#ifndef Pipe_H
#define Pipe_H

#include "Entity.h"

class Pipe : public Entity
{
public:
	Pipe(float _fY, bool _bBottom);
	virtual ~Pipe();

	void Update(float _fDeltaTime) override;

	bool IsFinished() override;

protected:
	float m_bIsBottom;
	const static float k_fPipeSpeed;
};

#endif
