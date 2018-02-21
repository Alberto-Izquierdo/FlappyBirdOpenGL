#ifndef Entity_H
#define Entity_H

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float _fDeltaTime) = 0;

	float GetX() const { return m_fX; };
	float GetY() const { return m_fY; };
	float GetWidht() const { return m_fWidth; };
	float GetHeight() const { return m_fHeight; };
	float* GetColor() { return m_Color; };
	float GetRotation() const { return m_fRotation; };

	virtual bool IsFinished() = 0;

protected:
	float m_fX, m_fY;
	float m_fWidth, m_fHeight;
	float m_fRotation;
	float m_Color[4];
};

#endif
