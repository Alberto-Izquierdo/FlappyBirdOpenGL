#ifndef CollisionDetectionManager_H
#define CollisionDetectionManager_H

#include <vector>

struct vec2
{
	float X;
	float Y;
};

class Entity;

class CollisionDetectionManager
{
public:
	CollisionDetectionManager();
	virtual ~CollisionDetectionManager();

	bool IsPlayerCollidingWithPipes(Entity* _pPlayer, std::vector<Entity*>& _vPipes);

protected:

	bool IsPlayerCollidingWithPipe(Entity* _pPlayer, Entity* _pPipe);
	vec2 GetClosestPositionToPlayer(Entity* _pPipe, vec2& _vPlayerCenter);
};

#endif
