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

const float& Matrix4::operator()(int _iX, int _iY) const
{
	return m_vElements[_iX + _iY * 4];
}

const float& Matrix4::operator()(int _iPos) const
{
	return m_vElements[_iPos];
}

Matrix4 Matrix4::operator*(const Matrix4& B)
{
	// A loop could be used, but for optimization reasons, it will not be used
	float array [16] = {
		m_vElements[0]*B(0) + m_vElements[1]*B(4) + m_vElements[2]*B(8) + m_vElements[3]*B(12),
		m_vElements[0]*B(1) + m_vElements[1]*B(5) + m_vElements[2]*B(9) + m_vElements[3]*B(13),
		m_vElements[0]*B(2) + m_vElements[1]*B(6) + m_vElements[2]*B(10) + m_vElements[3]*B(14),
		m_vElements[0]*B(3) + m_vElements[1]*B(7) + m_vElements[2]*B(11) + m_vElements[3]*B(15),
		m_vElements[4]*B(0) + m_vElements[5]*B(4) + m_vElements[6]*B(8) + m_vElements[7]*B(12),
		m_vElements[4]*B(1) + m_vElements[5]*B(5) + m_vElements[6]*B(9) + m_vElements[7]*B(13),
		m_vElements[4]*B(2) + m_vElements[5]*B(6) + m_vElements[6]*B(10) + m_vElements[7]*B(14),
		m_vElements[4]*B(3) + m_vElements[5]*B(7) + m_vElements[6]*B(11) + m_vElements[7]*B(15),
		m_vElements[8]*B(0) + m_vElements[9]*B(4) + m_vElements[10]*B(8) + m_vElements[11]*B(12),
		m_vElements[8]*B(1) + m_vElements[9]*B(5) + m_vElements[10]*B(9) + m_vElements[11]*B(13),
		m_vElements[8]*B(2) + m_vElements[9]*B(6) + m_vElements[10]*B(10) + m_vElements[11]*B(14),
		m_vElements[8]*B(3) + m_vElements[9]*B(7) + m_vElements[10]*B(11) + m_vElements[11]*B(15),
		m_vElements[12]*B(0) + m_vElements[13]*B(4) + m_vElements[14]*B(8) + m_vElements[15]*B(12),
		m_vElements[12]*B(1) + m_vElements[13]*B(5) + m_vElements[14]*B(9) + m_vElements[15]*B(13),
		m_vElements[12]*B(2) + m_vElements[13]*B(6) + m_vElements[14]*B(10) + m_vElements[15]*B(14),
		m_vElements[12]*B(3) + m_vElements[13]*B(7) + m_vElements[14]*B(11) + m_vElements[15]*B(15)
	};

	Matrix4 result = Matrix4(array);
	return result;
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
