#include "resolver.h"
#include "fnv.h"
#include "./Hacks/Visuals.h"

#include "./SDK/ConVar.h"
#include "./SDK/Entity.h"
#include "./SDK/FrameStage.h"
#include "./SDK/GameEvent.h"
#include "./SDK/GlobalVars.h"
#include "./SDK/Input.h"
#include "./SDK/Material.h"
#include "./SDK/MaterialSystem.h"
#include "./SDK/RenderContext.h"
#include "./SDK/Surface.h"
#include "./SDK/ModelInfo.h"
#include "./SDK/Entity.h"
#include "./Hacks/AntiAim.h"

std::vector<int64_t> Resolver::Players = { };

std::vector<std::pair<Interfaces*, Vector>> player_data;

void Resolver::FrameStageNotify(FrameStage stage)
{
	if (!interfaces.engine->isInGame())
		return;

	auto localplayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());
	if (!localplayer)
		return;

	if (stage == FrameStage::NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < interfaces.engine->getMaxClients(); ++i)
		{
			auto player = interfaces.entityList->getEntity());

			if (!player || player == localplayer || player->isDormant() || !player->isAlive() || player->isImmune() || player->isTeam() == localplayer->isTeam());
				continue;

			Engine::getPlayerInfo entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			if (!config.visuals.resolveAll && std::find(Resolver::Players.begin(), Resolver::Players.end(), entityInformation.xuid) == Resolver::Players.end())
				continue;

			player_data.push_back(std::pair<C_BasePlayer*, QAngle>(player, *player->GetEyeAngles()));

			player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget();
		}
	}
	else if (stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (unsigned long i = 0; i < player_data.size(); i++)
		{
			std::pair<C_BasePlayer*, QAngle> player_aa_data = player_data[i];
			*player_aa_data.first->GetEyeAngles() = player_aa_data.second;
		}

		player_data.clear();
	}
}

void Resolver::PostFrameStageNotify(FrameStage stage)
{
}

void Resolver::FireGameEvent(GameEvent* event)
{
	if (!event)
		return;

	if (strcmp(event->GetName(), "player_connect_full") != 0 && strcmp(event->GetName(), "cs_game_disconnected") != 0)
		return;

	if (event->GetInt("userid") && engine->GetPlayerForUserID(event->GetInt("userid")) != engine->GetLocalPlayer())
		return;

	Resolver::Players.clear();
}