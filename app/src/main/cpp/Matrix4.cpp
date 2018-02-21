#include "Matrix4.h"

#include <cmath>

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; ++i)
	{
		if (i % 5 == 0)
		{
			m_vElements[i] = 1.f;
		}
		else
		{
			m_vElements[i] = 0;
		}
	}
}

Matrix4::Matrix4(const float* _pElements)
{
	for (int i = 0; i < 16; ++i)
	{
		m_vElements[i] = _pElements[i];
	}
}

Matrix4 Matrix4::Translate(float _fX, float _fY, float _fZ)
{
	Matrix4 result = Matrix4();
	result.m_vElements[0]  = 1;
	result.m_vElements[5]  = 1;
	result.m_vElements[10] = 1;
	result.m_vElements[3]  = _fX;
	result.m_vElements[7]  = _fY;
	result.m_vElements[11] = _fZ;
	return result;
}

Matrix4 Matrix4::Scale(float _fX, float _fY, float _fZ)
{
	Matrix4 result = Matrix4();
	result.m_vElements[0]  = _fX;
	result.m_vElements[5]  = _fY;
	result.m_vElements[10] = _fZ;
	return result;
}

Matrix4 Matrix4::RotationZ(float _fAngle)
{
	Matrix4 result = Matrix4();
	float fCos, fSin;
	fCos = std::cos(_fAngle);
	fSin = std::sin(_fAngle);
	result.m_vElements[0] =  fCos;
	result.m_vElements[1] = -fSin;
	result.m_vElements[4] =  fSin;
	result.m_vElements[5] =  fCos;
	return result;
}
