#include "Features.h"

bool Settings::Resolver::resolveAll = false;
ResolverType Settings::Resolver::type = ResolverType::Type1;
std::vector<int64_t> Resolver::Players = {};

std::vector<std::pair<C_BasePlayer*, Vector>> player_data;
bool IsEntityMoving(C_BasePlayer *ent)
{
	return (ent->GetVelocity().Length2D() > 0.1f && ent->GetFlags() & FL_ONGROUND);
}
void Resolver::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!pEngine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*)pEntityList->GetClientEntity(pEngine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < pEngine->GetMaxClients(); ++i)
		{
			C_BasePlayer* player = (C_BasePlayer*)pEntityList->GetClientEntity(i);

			if (!player
				|| player == localplayer
				|| player->GetDormant()
				|| !player->GetAlive()
				|| player->GetImmune()
				|| player->GetTeam() == localplayer->GetTeam())
				continue;

			IEngineClient::player_info_t entityInformation;
			pEngine->GetPlayerInfo(i, &entityInformation);

			if (!Settings::Resolver::resolveAll && std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) == Resolver::Players.end())
				continue;

			player_data.push_back(std::pair<C_BasePlayer*, Vector>(player, *player->GetEyeAngles()));

			if (Settings::Resolver::type == ResolverType::Type1)
			{
					player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget();
			}
			else if (Settings::Resolver::type == ResolverType::Type2)
			{
				if (IsEntityMoving(player))
				{
					player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget();
					//p_Console->ConsoleColorPrintf(Color::Blue(), "IsEntityMoving: true\n");
				}
				else
				{
					player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget() + 180.f;
					//p_Console->ConsoleColorPrintf(Color(255, 119, 0, 255), "else: true\n");
				}
			}
			else if (Settings::Resolver::type == ResolverType::Type3)
			{
				static float OldLowerBodyYaws[64];
				static float OldYawDeltas[64];
				float CurYaw = *player->GetLowerBodyYawTarget();
				if (OldLowerBodyYaws[i] != CurYaw)
				{
					OldYawDeltas[i] = player->GetEyeAngles()->y - CurYaw;
					OldLowerBodyYaws[i] = CurYaw;
					player->GetEyeAngles()->y = CurYaw;
					continue;
				}
				else 
				{
					player->GetEyeAngles()->y = player->GetEyeAngles()->y - OldYawDeltas[i];
				}
			}

			//player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget();
		}
	}
	else if (stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (unsigned long i = 0; i < player_data.size(); i++)
		{
			std::pair<C_BasePlayer*, Vector> player_aa_data = player_data[i];
			*player_aa_data.first->GetEyeAngles() = player_aa_data.second;
		}

		player_data.clear();
	}
}

void Resolver::PostFrameStageNotify(ClientFrameStage_t stage)
{
}

void Resolver::FireGameEvent(IGameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_connect_full") != 0 && strcmp(event->GetName(), "cs_game_disconnected") != 0)
		return;

	if (event->GetInt("userid") && pEngine->GetPlayerForUserID(event->GetInt("userid")) != pEngine->GetLocalPlayer())
		return;

	Resolver::Players.clear();
}