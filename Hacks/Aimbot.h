#pragma once

#include "../SDK/UserCmd.h"

namespace Aimbot {
    Vector calculateRelativeAngle(const Vector& source, const Vector& destination, const Vector& viewAngles) noexcept;
    void run(UserCmd*) noexcept;
	void Autostop(UserCmd* pCmd) noexcept;
	void CorrectMovement(const Vector& vOldAngles, UserCmd* pCmd, float fOldForward, float fOldSidemove);
}
