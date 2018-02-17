#ifndef Pipe_H
#define Pipe_H

#include "Entity.h"

class Pipe : public Entity
{
public:
	Pipe();
	virtual ~Pipe();

	void Update(float _fDeltaTime) override;

	bool IsFinished() override;

protected:
	const static float k_fPipeSpeed;
};

#endif
