#pragma once

#include "SDK/SDK.h"

namespace Math {
	void inline SinCos(float radians, float *sine, float *cosine);
	void AngleVectors(const Vector &angles, Vector &forward);
	void NormalizeAngles(Vector& angle);
	void ClampAngles(Vector& angle);
	void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	float GetFov(const Vector &viewAngle, const Vector &aimAngle);
	float DotProduct(Vector &v1, const float* v2);
	float DotProduct2(const Vector& a, const Vector& b);
	void VectorAngles(const Vector &forward, Vector &angles);
	void VectorTransform(Vector &in1, const matrix3x4_t& in2, Vector &out);
	Vector CalcAngle(Vector src, Vector dst);
	float float_rand(float min, float max);
}