#include "AntiAim.h"
#include "../Interfaces.h"
#include "../SDK/Engine.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/UserCmd.h"
#include "../Memory.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/Surface.h"
#include "../SDK/GameEvent.h"
#include <math.h>


static bool IsLocalPlayer() {
auto localPlayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());
if (localPlayer) return true;
else return false;
}

float AntiAim::getMaxDelta(AnimState* animState) {

	float speedFraction = std::max<float>(0.0f, std::min<float>(animState->feetShuffleSpeed, 1.0f));

	float speedFactor = std::max<float>(0.0f, std::min<float>(1.0f, animState->feetShuffleSpeed2)); 

	float unk1 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * speedFraction;
	float unk2 = unk1 + 1.0f;
	float delta;

	if (animState->duckProgress > 0)
	{
		unk2 += ((animState->duckProgress * speedFactor) * (0.5f - unk2));// - 1.f
	}

	delta = *(float*)((uintptr_t)animState + 0x3A4) * unk2;

	return delta - 0.5f;
}


void AntiAim::run(UserCmd* cmd, const Vector& previousViewAngles, const Vector& currentViewAngles, bool& sendPacket) noexcept
{
	static bool bFlip = false;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;
	Vector oldAngle = cmd->viewangles;
	auto localPlayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());
	if (config.antiAim.enabled) {
		if (interfaces.engine->isInGame())
		{
			if (IsLocalPlayer())
			{
				if (config.antiAim.pitch && cmd->viewangles.x == currentViewAngles.x)
					cmd->viewangles.x = config.antiAim.pitchAngle;
				if (config.antiAim.yaw && cmd->viewangles.y == currentViewAngles.y) {
					switch (config.antiAim.mode) {
					case 0: // legit
						if (!sendPacket) {
							cmd->viewangles.y += interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer())->getMaxDesyncAngle();
							if (fabsf(cmd->sidemove) < 5.0f) {
								if (cmd->buttons & UserCmd::IN_DUCK)
									cmd->sidemove = cmd->tickCount & 1 ? 3.25f : -3.25f;
								else
									cmd->sidemove = cmd->tickCount & 1 ? 1.1f : -1.1f;
							}
						}
						break;
					case 1: // static
						cmd->viewangles.y += 180; // TODO: add yaw offset slider.
						break;
					case 2: // jitter
						cmd->viewangles.y += 180;
						cmd->viewangles.y += (bFlip) ? 20 : -20; // TODO: add yaw range slider.
						bFlip ^= 1; // equal to x = !x
						break;
					case 3: // spin
						cmd->viewangles.y = previousViewAngles.y + 45;
						break;
					}
				}
				if (sendPacket) config.GlobalReal = cmd->viewangles;
				else if (!sendPacket) config.GlobalFake = cmd->viewangles;
				Aimbot::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

			}
		}
	}
}



void AntiAim::indicators() noexcept
{
	//do nothing
}
