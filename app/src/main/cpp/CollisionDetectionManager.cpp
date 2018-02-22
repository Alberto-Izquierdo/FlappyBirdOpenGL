#include "CollisionDetectionManager.h"
#include "Entity.h"

CollisionDetectionManager::CollisionDetectionManager()
{
}

CollisionDetectionManager::~CollisionDetectionManager()
{
}

bool CollisionDetectionManager::IsPlayerCollidingWithPipes(Entity* _pPlayer, std::vector<Entity*>& _vPipes)
{
	for (Entity* pPipe : _vPipes)
	{
		if (IsPlayerCollidingWithPipe(pPipe, _pPlayer))
		{
			return true;
		}
	}
	
	return false;
}

vec2 CollisionDetectionManager::GetClosestPositionToPlayer(Entity* _pPipe, vec2& _vPlayerCenter)
{
	float fPipeWidth = _pPipe->GetWidth();
	float fPipeHeight = _pPipe->GetHeight();
	float fPipeX = _pPipe->GetX() - fPipeWidth / 2.f;
	float fPipeY = _pPipe->GetY() - fPipeHeight / 2.f;

	if (_vPlayerCenter.Y > fPipeY && _vPlayerCenter.Y < fPipeY + fPipeHeight)
	{
		if (_vPlayerCenter.X < fPipeX + fPipeWidth / 2)
		{
			vec2 vClosestPoint = {fPipeX, _vPlayerCenter.Y};
			return vClosestPoint;
		}

		vec2 vClosestPoint = {fPipeX + fPipeWidth, _vPlayerCenter.Y};
		return vClosestPoint;
	}
	else if (_vPlayerCenter.X > fPipeX && _vPlayerCenter.X < fPipeX + fPipeWidth)
	{
		if (_vPlayerCenter.Y < fPipeY + fPipeHeight / 2)
		{
			vec2 vClosestPoint = {_vPlayerCenter.X, fPipeY};
			return vClosestPoint;
		}
		
		vec2 vClosestPoint = {_vPlayerCenter.X, fPipeY + fPipeHeight};
		return vClosestPoint;
	}

	vec2 vClosestPoint = {0, 0};

	if (_vPlayerCenter.X < fPipeX + fPipeWidth / 2)
	{
		vClosestPoint.X = fPipeX;
	}
	else
	{
		vClosestPoint.X = fPipeX + fPipeWidth;
	}

	if (_vPlayerCenter.Y < fPipeY + fPipeHeight / 2)
	{
		vClosestPoint.Y = fPipeY;
	}
	else
	{
		vClosestPoint.Y = fPipeY + fPipeHeight;
	}

	return vClosestPoint;
}

bool CollisionDetectionManager::IsPlayerCollidingWithPipe(Entity* _pPipe, Entity* _pPlayer)
{
	float fPlayerX = _pPlayer->GetX();
	float fPlayerY = _pPlayer->GetY();
	float fPlayerWidth = _pPlayer->GetWidth();
	float fPlayerHeight = _pPlayer->GetHeight();
	vec2 vPlayerCenter = {fPlayerX, fPlayerY};

	vec2 vClosestPositionToPlayer = GetClosestPositionToPlayer(_pPipe, vPlayerCenter);
	vec2 vDistanceBetweenPipeAndPlayer = {vClosestPositionToPlayer.X - vPlayerCenter.X, vClosestPositionToPlayer.Y - vPlayerCenter.Y};

	if (vDistanceBetweenPipeAndPlayer.X * vDistanceBetweenPipeAndPlayer.X + vDistanceBetweenPipeAndPlayer.Y * vDistanceBetweenPipeAndPlayer.Y < (fPlayerWidth / 2) * (fPlayerWidth / 2))
	{
		return true;
	}

	return false;
}
