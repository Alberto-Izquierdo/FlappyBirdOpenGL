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
	int GetWidht() const { return m_iWidth; };
	int GetHeight() const { return m_iHeight; };
	unsigned char* GetColor() { return m_Color; };

protected:
	float m_fX, m_fY;
	int m_iWidth, m_iHeight;
	float m_fRotation;
	unsigned char m_Color[4];
};

#endif
