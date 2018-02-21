#ifndef Matrix4_H
#define Matrix4_H

class Matrix4
{
public:
	Matrix4();
	Matrix4(const float* _vElements);

	static Matrix4 Translate(float _fX, float _fY, float _fZ);
	static Matrix4 Scale(float _fX, float _fY, float _fZ);
	static Matrix4 RotationZ(float _fAngle);
	// No need to implement the other rotations as this is a 2D game

private:
	float m_vElements[16];
};

#endif
