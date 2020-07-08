#pragma once

#include "fnv.h"
#include "./Hacks/Visuals.h"
#include "SDK/Entity.h"
#include "SDK/FrameStage.h"
#include "SDK/GameEvent.h"
#include "SDK/GlobalVars.h"
#include "SDK/ModelInfo.h"
#include "SDK/Entity.h"
#include "./Hacks/AntiAim.h"

static bool IsLocalPlayer() {
	auto localPlayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());
	if (localPlayer) return true;
	else return false;
}


class resolver
{
public:
	std::vector<int64_t> Players = { };
	std::vector<std::pair<Entity*, Vector>> player_data;
	void ResolverFrameStageNotify(FrameStage  stage)
	{
		auto localPlayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());
		if (config.misc.resolver == true)
		{

			if (!interfaces.engine->isInGame())
				return;

			if (localPlayer != nullptr)
			{
				if(IsLocalPlayer())
				{ 
					if (stage == FrameStage::NET_UPDATE_POSTDATAUPDATE_START)
					{
						for (int i = 1; i < interfaces.engine->getMaxClients(); ++i)
						{
							auto player = interfaces.entityList->getEntity(i);

							if (!player || player == localPlayer || !player->isDormant() || !player->isAlive());
							continue;
							PlayerInfo entityInformation;
							interfaces.engine->getPlayerInfo(i, entityInformation);

							if (!config.misc.resolveAll && std::find(Players.begin(), Players.end(), entityInformation.xuid) == Players.end())
								continue;

							player_data.push_back(std::pair<Entity*, Vector>(player, player->eyeAngles()));
							//player->eyeAngles().y = player->GetLowerBodyYawTarget();
							//Take account of decync and brute force.
							player->eyeAngles().y = (rand() % 2) ?
								player->eyeAngles().y + (localPlayer->getMaxDesyncAngle() /* * 0.66f*/ ):
								player->eyeAngles().y - (localPlayer->getMaxDesyncAngle() /* * 0.66f*/ );

						}
					}
					else if (stage == FrameStage::RENDER_END)
					{
						for (unsigned long i = 0; i < player_data.size(); i++)
						{
							std::pair<Entity*, Vector> player_aa_data = player_data[i];
							player_aa_data.first->eyeAngles() = player_aa_data.second;
						}

						player_data.clear();
					}
				}
			}
		}
	}

	void ResolverPostFrameStageNotify(FrameStage  stage);
	void ResolverFireGameEvent(GameEvent* event) {
		if (!event)
			return;
		if (strcmp(event->getName(), "player_connect_full") != 0 && strcmp(event->getName(), "cs_game_disconnected") != 0)
			return;

		if (event->getInt("userid") && interfaces.engine->getPlayerForUserID(event->getInt("userid")) != interfaces.engine->getLocalPlayer())
			return;

		Players.clear();
	}
};
