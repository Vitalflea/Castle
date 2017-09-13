#include "Features.h"
bool Settings::FakeWalk::enabled;

bool IsMoving(C_BasePlayer *ent)
{
	return (ent->GetVelocity().Length2D() > 0.1f && ent->GetFlags() & FL_ONGROUND);
}
void FakeWalk(CUserCmd* cmd, bool & bSendPacket)
{
	if (!Settings::FakeWalk::enabled)
		return;

	if (!pInputSystem->IsButtonDown(KEY_LSHIFT))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localplayer)
		return;

	static int iChoked = -1;
	iChoked++;

	if (iChoked < 1)
	{
		bSendPacket = false;

		cmd->tick_count += 10;
		cmd->command_number += 7 + cmd->tick_count % 2 ? 0 : 1;

		cmd->buttons |= localplayer->GetMoveType() == IN_BACK;
		cmd->forwardmove = cmd->sidemove = 0.f;
	}
	else
	{
		bSendPacket = true;
		iChoked = -1;

		pGlobalVars->frametime *= (localplayer->GetVelocity().Length2D()) / 1.f;
		cmd->buttons |= localplayer->GetMoveType() == IN_FORWARD;
	}
	
}