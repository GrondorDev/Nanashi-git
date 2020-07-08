#pragma once
#include "Aimbot.h"
#include "../Config.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../SDK/ConVar.h"
#include "../SDK/Entity.h"
#include "../SDK/UserCmd.h"
#include "../SDK/Vector.h"
#include "../SDK/WeaponId.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/PhysicsSurfaceProps.h"
#include "../SDK/WeaponData.h"

struct UserCmd;
struct Vector;
namespace AntiAim {
    void run(UserCmd*, const Vector&, const Vector&, bool&) noexcept;
	void indicators() noexcept;
	float getMaxDelta(AnimState *animstate);
}

