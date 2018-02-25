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
	bool DoesItAddPointsToScore() const { return m_bAddsPointsToScore; };
	void ScoreAdded() { m_bAddsPointsToScore = false; };

protected:
	bool m_bIsBottom;
	bool m_bAddsPointsToScore;
	const static float k_fPipeSpeed;
};

#endif
