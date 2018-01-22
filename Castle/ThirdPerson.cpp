#include "Features.h"

bool Settings::ThirdPerson::enabled = false;
float Settings::ThirdPerson::distance = 30.f;
bool Settings::ThirdPerson::Fake;
bool Settings::ThirdPerson::Real;
void ThirdPerson::FrameStageNotify(ClientFrameStage_t stage)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	
	if (pEngine->IsInGame() && localplayer && stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		static Vector vecAngles;
		pEngine->GetViewAngles(vecAngles);
		if (Settings::ThirdPerson::enabled && localplayer->GetAlive())
		{
			if (!pInput->ThirdPerson)
				pInput->ThirdPerson = true;

			pInput->CameraVac = Vector(vecAngles.x, vecAngles.y, Settings::ThirdPerson::distance);

			if((Settings::ThirdPerson::Fake || Settings::ThirdPerson::Real) && (Settings::AntiAim::Pitch::enabled || Settings::AntiAim::Yaw::enabled))
				*localplayer->GetVAngles() = lastTickViewAngles;
		}
		else
		{
			if (pInput->ThirdPerson)
			{
				pInput->ThirdPerson = false;
				pInput->CameraVac = Vector(vecAngles.x, vecAngles.y, 0);
			}
		}
	}
}
