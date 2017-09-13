#include "DDI.h"
#include "Draw.h"
#include <string>
//display debug info
void Info()
{
	if (pEngine->IsInGame() && (*pGameRules) && (*pGameRules)->IsValveDS())
		Draw::Text(200, -1, "VAC Server", esp_font, Color(0, 255, 0, 255));

	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	Vector Eye;	pEngine->GetViewAngles(Eye);
	
	Draw::Text(150, 0, std::string("lby: " + std::to_string(*localplayer->GetLowerBodyYawTarget())).c_str(), esp_font, Color(255, 255, 255, 255));
	Draw::Text(150, 20, std::string("yaw: " + std::to_string(Eye.y)).c_str(), esp_font, Color(255, 255, 255, 255));
	
}