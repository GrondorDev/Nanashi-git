#pragma once

#include <cstddef>

struct AnimState {
    std::byte pad[164];
    float duckAmount;
    std::byte pad1[80];
    float footSpeed;
    float footSpeed2;
    std::byte pad2[22];
    float stopToFullRunningFraction;
    std::byte pad3[532];
    float velocitySubtractY;
	char pad6[91];
	void* pBaseEntity;
	void* pActiveWeapon;
	void* pLastActiveWeapon;
	float m_flLastClientSideAnimationUpdateTime;
	int m_iLastClientSideAnimationUpdateFramecount;
	float m_flEyePitch;
	float m_flEyeYaw;
	float m_flPitch;
	float m_flGoalFeetYaw;
	float m_flCurrentFeetYaw;
	float m_flCurrentTorsoYaw;
	float m_flUnknownVelocityLean;
	float m_flLeanAmount;
	float duckProgress; //0x00B8 Progress 0.0-1.0, 0.0 = standing, 1.0 = fully crouched. Also used for jumping. Counts backwards from 1.0 for jumps
	float runningAccelProgress; //0x0130 0 - 1.0, Only affected by Running, reaches 1.0 when you are at full speed (ex: 250 w/ knife )
	float feetShuffleSpeed; //0x010C // 0.0-2.0 (approx)
	float feetShuffleSpeed2; //0x0110 // 0.0-3.0 (approx)
};
