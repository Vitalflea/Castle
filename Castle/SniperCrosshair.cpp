#include "Features.h"

bool Settings::SniperCrosshair::enabled = false;

void SniperCrosshair::BeginFrame()
{
	if (!pEngine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
	{
		C_BasePlayer* observerTarget = (C_BasePlayer*)pEntityList->GetClientEntityFromHandle(localplayer->GetObserverTarget());
		if (!observerTarget)
			return;

		localplayer = observerTarget;
	}

	//*CrosshairWeaponTypeCheck = Settings::SniperCrosshair::enabled && !localplayer->IsScoped() ? 255 : 5;
}