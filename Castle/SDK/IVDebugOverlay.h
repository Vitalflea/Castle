#pragma once

class IVDebugOverlay
{
public:
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(__thiscall* oScreenPosition)(void*, const Vector&, Vector&);
		return getvfunc<oScreenPosition>(this, 13)(this, vIn, vOut);
	}
};