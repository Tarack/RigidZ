// RigidZ Menu 2017
// Created by: Taraack
// All rights reserved!

#pragma once
#include "..\..\inc\natives.h"

enum FEATURE_FUNCS
{
	FEATURE_FUNC_CLEAR_WANTED,
	FEATURE_FUNC_TINY_PLAYER,
	FEATURE_FUNC_FILL_HEALTH,
	FEATURE_FUNC_FILL_ARMOR,
	FEATURE_FUNC_TOG_GOD,
	FEATURE_FUNC_TOG_VANISH,
	FEATURE_FUNC_CLEAR_BLOOD,
	FEATURE_FUNC_TOG_NO_RAGDOLL,
	FEATURE_FUNC_TOG_FASTRUN,

	FEATURE_FUNC_TOG_VEH_GOD,
	FEATURE_FUNC_TOG_VEH_VANISH,
	FEATURE_FUNC_VEH_UNFLIP,
	FEATURE_FUNC_VEH_REPAIR,
	FEATURE_FUNC_VEH_SPAWN,
	FEATURE_FUNC_VEH_CHANGELICENSE,

	FEATURE_FUNC_WEAPON_GIVE_ALL,
	FEATURE_FUNC_WEAPON_REMOVE_ALL,

	FEATURE_FUNC_TELEPORT,
	FEATURE_FUNC_ENABLE_YANKTON,

	FEATURE_FUNC_TIME_SET,
	FEATURE_FUNC_WEATHER_SET,

	FEATURE_FUNC_MISC_THERMALVISION,
	FEATURE_FUNC_MISC_NIGHTVISION,
	FEATURE_FUNC_MISC_MOBILERADIO,
	FEATURE_FUNC_MISC_EXPANDEDRADAR,
	FEATURE_FUNC_MISC_ACHIEVEMENT_UNLOCK,

	FEATURE_FUNC_CAM_EFFECT,

	FEATURE_FUNC_MENU_DESIGN,

};

void notifyAboveMap(char* Text);
void MenuFunctions(FEATURE_FUNCS features, bool Toggle, char* Args, float FloatArg[], int IntArg);