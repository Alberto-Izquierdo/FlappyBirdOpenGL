#ifndef Entity_H
#define Entity_H

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float _fDeltaTime);
	virtual void Render();

	void SetPosition(float _fX, float _fY);
	void SetColor(unsigned char _Color[4]);

protected:
	float m_fX, m_fY;
	unsigned char m_Color[4];
};

#endif
