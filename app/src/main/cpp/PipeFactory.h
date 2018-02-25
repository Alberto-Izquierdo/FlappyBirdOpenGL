#ifndef PipeFactory_H
#define PipeFactory_H

#include <vector>

class Entity;

class PipeFactory
{
public:
	PipeFactory(std::vector<Entity*>* _vPipes);
	virtual ~PipeFactory();

	void Update(float _fDelta);

protected:
	float m_fTimeSinceLastPipeSpawned;
	float m_iLastPosition;
	std::vector<Entity*>* m_vEntities;
	static const float k_fTimeBetweenPipes;
	static const float k_fYDistanceBetweenPipes;
	static const float k_fMinimumDistanceToWindowBorder;
	static const int k_iYMaximumDistanceBetweenPipes;
};

#endif
