#include "Features.h"
#include "Hooks.h"
#include "FindPattern.h"
typedef void(__thiscall* SetHost_t)(void*, void*);
float m_flOldCurtime;
float m_flOldFrametime;
MoveData data;
void Prediction::Start(CUserCmd* cmd)
{
	//if (!Settings::Misc::EnginePrediction::Enabled)
	//	return;

	C_BasePlayer * Local = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!Local)
		return;

	*pPredSeed = cmd->command_number;

	m_flOldCurtime = pGlobalVars->frametime;
	m_flOldFrametime = pGlobalVars->curtime;

	pGlobalVars->frametime = pGlobalVars->interval_per_tick;
	pGlobalVars->curtime = Local->GetTickBase() * pGlobalVars->interval_per_tick;

	pGameMovement->StartTrackPredictionErrors(Local);

	memset(&data, 0, sizeof(MoveData));

	pMoveHelper->SetHost(Local);
	pPrediction->SetupMove(Local, cmd, pMoveHelper, &data);
	pGameMovement->ProcessMovement(Local, &data);
	pPrediction->FinishMove(Local, cmd, &data);
}


void Prediction::End()
{
	//if (!Settings::Misc::EnginePrediction::Enabled)
	//	return;

	C_BasePlayer * Local = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!Local)
		return;

	pGameMovement->FinishTrackPredictionErrors(Local);
	pMoveHelper->SetHost(nullptr);

	*pPredSeed = -1;

	pGlobalVars->curtime = m_flOldCurtime;
	pGlobalVars->frametime = m_flOldFrametime;
}

