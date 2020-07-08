#pragma once

#include <array>
#include <filesystem>
#include <string>

#include "imgui/imgui.h"
#include "nSkinz/config_.hpp"
#include "SDK/Vector.h"

class Config {
public:
	int GlobalScreenHeight;
	int GlobalScreenWidth;
	int GlobalFPS;
	int GlobalPing = 0;
	int GlobalIsThirdPerson = 0;
	Vector GlobalReal;
	Vector GlobalFake;
	int GlobalIsComp = 1;

	explicit Config(const char*) noexcept;
	void load(size_t) noexcept;
	void save(size_t) const noexcept;
	void add(const char*) noexcept;
	void remove(size_t) noexcept;
	void rename(size_t, const char*) noexcept;
	void reset() noexcept;

	constexpr auto& getConfigs() noexcept
	{
		return configs;
	}

	constexpr auto& getConsole() noexcept
	{
		return consoleText;
	}

	struct Color {
		float color[3]{ 1.0f, 1.0f, 1.0f };
		bool rainbow{ false };
		float rainbowSpeed{ 0.6f };
	};

	struct ColorToggle : public Color {
		bool enabled{ false };
	};

	struct Aimbot {
		bool enabled{ false };
		bool onKey{ false };
		int key{ 0 };
		int keyMode{ 0 };
		bool aimlock{ false };
		bool silent{ false };
		bool friendlyFire{ false };
		bool visibleOnly{ false };
		bool scopedOnly{ false };
		bool ignoreFlash{ false };
		bool ignoreSmoke{ false };
		bool autoShot{ false };
		bool autoScope{ false };
		float fov{ 0.0f };
		float smooth{ 1.0f };
		int bone{ 0 };
		float maxAimInaccuracy{ 1.0f };
		float maxShotInaccuracy{ 1.0f };
		int minDamage{ 1 };
		bool killshot{ false };
		bool betweenShots{ false };
	};
	std::array<Aimbot, 40> aimbot;

	struct Triggerbot {
		bool enabled{ false };
		bool onKey{ false };
		int key{ 0 };
		bool friendlyFire{ false };
		bool scopedOnly{ false };
		bool ignoreFlash{ false };
		bool ignoreSmoke{ false };
		int hitgroup{ 0 };
		int shotDelay{ 0 };
		int minDamage{ 1 };
		bool killshot{ false };
	};
	std::array<Triggerbot, 40> triggerbot;

	struct {
		bool enabled{ false };
		bool drawAllTicks{ false };
		bool ignoreSmoke{ false };
		bool recoilBasedFov{ false };
		int timeLimit{ 200 };
	} backtrack;

	struct {
		bool enabled{ false };
		int mode{ 0 };
		bool pitch{ false };
		float pitchAngle{ 0.0f };
		bool yaw{ false };
		bool rage{ false };
	} antiAim;

	struct Glow {
		bool enabled{ false };
		bool healthBased{ false };
		float thickness{ 1.0f };
		float alpha{ 1.0f };
		int style{ 0 };
		Color color;
	};
	std::array<Glow, 21> glow;

	struct Chams {
		struct Material {
			bool enabled{ false };
			bool healthBased{ false };
			Color color;
			bool blinking{ false };
			int material{ 0 };
			bool wireframe{ false };
			float alpha{ 1.0f };
		};
		std::array<Material, 2> materials;
	};

	std::array<Chams, 18> chams;

	struct Esp {
		struct Shared {
			bool enabled{ false };
			int font{ 5 };
			ColorToggle snaplines;
			ColorToggle box;
			int boxType{ 0 };
			ColorToggle name;
			ColorToggle outline{ 0.0f, 0.0f, 0.0f };
			ColorToggle distance;
			float maxDistance{ 0.0f };
		};

		struct Player : public Shared {
			ColorToggle eyeTraces;
			ColorToggle health;
			ColorToggle healthBar;
			ColorToggle armor;
			ColorToggle armorBar;
			ColorToggle money;
			ColorToggle headDot;
			ColorToggle activeWeapon;
			bool deadesp{ false };
		};

		struct Weapon : public Shared { } weapon;

		struct Projectile : public Shared { };
		std::array<Projectile, 9> projectiles;

		struct DangerZone : public Shared { };
		std::array<DangerZone, 18> dangerZone;

		std::array<Player, 6> players;
	} esp;

	struct {
		bool disablePostProcessing{ false };
		bool inverseRagdollGravity{ false };
		bool noFog{ false };
		bool no3dSky{ false };
		bool noAimPunch{ false };
		bool noViewPunch{ false };
		bool noHands{ false };
		bool noSleeves{ false };
		bool noWeapons{ false };
		bool noSmoke{ false };
		bool noBlur{ false };
		bool noScopeOverlay{ false };
		bool noGrass{ false };
		bool noShadows{ false };
		bool wireframeSmoke{ false };
		bool zoom{ false };
		int zoomKey{ 0 };
		bool thirdperson{ false };
		bool thirdpersonReal{ false };
		int thirdpersonKey{ 0 };
		int thirdpersonDistance{ 0 };
		int viewmodelFov{ 0 };
		int fov{ 0 };
		bool remScopeFOV;
		int farZ{ 0 };
		int flashReduction{ 0 };
		float brightness{ 0.0f };
		int skybox{ 0 };
		ColorToggle world;
		ColorToggle sky;
		bool deagleSpinner{ false };
		int screenEffect{ 0 };
		int hitEffect{ 0 };
		float hitEffectTime{ 0.0f };
		int hitMarker{ 0 };
		float hitMarkerTime{ 0.0f };
		int playerModelT{ 0 };
		int playerModelCT{ 0 };
		bool fullBright{ false };
		struct {
			bool enabled = false;
			float blue = 0.0f;
			float red = 0.0f;
			float mono = 0.0f;
			float saturation = 0.0f;
			float ghost = 0.0f;
			float green = 0.0f;
			float yellow = 0.0f;
		} colorCorrection;
		int SESPage{ 0 };
	} visuals;

	std::array<item_setting, 36> skinChanger;

	struct {
		int chickenVolume{ 100 };

		struct Player {
			int masterVolume{ 100 };
			int headshotVolume{ 100 };
			int weaponVolume{ 100 };
			int footstepVolume{ 100 };
		};

		std::array<Player, 3> players;
	} sound;

	struct {
		int menuStyle{ 1 };
		int menuColors{ 1 };
	} style;

	struct {
		int menuKey{ 0x2D }; // VK_INSERT
		bool antiAfkKick{ false };
		bool autoStrafe{ false };
		bool bunnyHop{ false };
		bool customClanTag{ false };
		bool clocktag{ false };
		std::string clanTag = "Nanashi.meme ";
		bool animatedClanTag{ true };
		bool fastDuck{ false };
		bool moonwalk{ false };
		bool edgejump{ false };
		int edgejumpkey{ 0 };
		bool slowwalk{ false };
		int slowwalkKey{ 0 };
		bool sniperCrosshair{ false };
		bool recoilCrosshair{ false };
		bool autoPistol{ false };
		bool autoReload{ false };
		bool autoAccept{ false };
		bool radarHack{ false };
		bool revealRanks{ false };
		bool revealMoney{ false };
		bool revealSuspect{ false };
		ColorToggle spectatorList;
		ColorToggle watermark;
		ColorToggle Menu;
		bool fixAnimationLOD{ false };
		bool fixBoneMatrix{ false };
		bool fixMovement{ false };
		bool disableModelOcclusion{ false };
		float aspectratio{ 0 };
		bool killMessage{ false };
		bool consoleMessage{ false };
		std::string killMessageString{ "Gotcha!" };
		std::string cMessageString{ "sv_cheats 1" };
		bool nameStealer{ false };
		bool disablePanoramablur{ false };
		int banColor{ 6 };
		std::string banText{ "Nanashi" };
		std::string voteText{ "Press f1 if ur gey" };
		bool fastPlant{ false };
		ColorToggle bombTimer{ 1.0f, 0.55f, 0.0f };
		bool quickReload{ false };
		bool prepareRevolver{ false };
		int prepareRevolverKey{ 0 };
		int hitSound{ 0 };
		int chokedPackets{ 0 };
		int chokedPacketsKey{ 0 };
		int quickHealthshotKey{ 0 };
		bool nadePredict{ false };
		bool fixTabletSignal{ false };
		float maxAngleDelta{ 255.0f };
		bool fakePrime{ false };
		float viewmodel_x;
		float viewmodel_y;
		float viewmodel_z;
		bool resolver{ false };
		bool resolveAll{ false };
		ColorToggle  drawAimbotFov;
		bool AutoStop{ false };
	} misc;

	struct {
		bool enabled{ false };
		bool textAbuse{ false };
		bool griefing{ false };
		bool wallhack{ true };
		bool aimbot{ true };
		bool other{ true };
		int target{ 0 };
		int delay{ 1 };
		int rounds{ 1 };
	} reportbot;
private:
	std::filesystem::path path;
	std::vector<std::string> configs;
	std::vector<std::string> consoleText;
};

extern Config config;
