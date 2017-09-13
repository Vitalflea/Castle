#include "Features.h"

bool Settings::AutoDefuse::enabled = false;

void AutoDefuse::CreateMove(CUserCmd *cmd)
{
	if (!Settings::AutoDefuse::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (localplayer->GetTeam() != TeamID::TEAM_COUNTER_TERRORIST)
		return;

	if (!(*pGameRules) || !(*pGameRules)->IsBombPlanted())
		return;

	C_PlantedC4* bomb = nullptr;

	for (int i = 1; i < pEntityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* entity = pEntityList->GetClientEntity(i);
		if (!entity)
			continue;

		if (entity->GetClientClass()->m_ClassID == EClassIds::CPlantedC4)
		{
			bomb = (C_PlantedC4*)entity;
			break;
		}
	}

	if (!bomb || bomb->IsBombDefused())
		return;

	float bombTimer = bomb->GetBombTime() - pGlobalVars->curtime;

	if (localplayer->HasDefuser() && bombTimer > 5.5f)
		return;

	if (!localplayer->HasDefuser() && bombTimer > 10.5f)
		return;

	float distance = localplayer->GetVecOrigin().DistTo(bomb->GetVecOrigin());
	if (distance <= 75.0f)
		cmd->buttons |= IN_USE;
}