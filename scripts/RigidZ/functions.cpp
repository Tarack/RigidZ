// RigidZ Menu 2017
// Created by: Tarack
// All rights reserved!

#include "functions.h"

void notifyAboveMap(char* Text)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Text);
	UI::_DRAW_NOTIFICATION(false, false);
}

void kickYoAss()
{
	#pragma region KickYoAss
	GAMEPLAY::_FORCE_SOCIAL_CLUB_UPDATE();
	#pragma endregion
}

#pragma region Hash/Name Tables
char* Weapons[] = { "WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN",
"WEAPON_COMBATPDW", "WEAPON_KNUCKLE", "WEAPON_MARKSMANPISTOL",
"WEAPON_FLASHLIGHT", "WEAPON_MACHETE", "WEAPON_MACHINEPISTOL",
"WEAPON_SWITCHBLADE", "WEAPON_REVOLVER","weapon_assaultrifle_mk2", "weapon_carbinerifle_mk2", "weapon_combatmg_mk2", "weapon_heavysniper_mk2",
"weapon_pistol_mk2",
"weapon_smg_mk2", };
#pragma endregion

#pragma region Menu Functions no Toggle / Toggle

void MenuFunctions(FEATURE_FUNCS features, bool Toggle, char* Args, float FloatArg[], int IntArg)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()));
	Player player = PLAYER::GET_PLAYER_INDEX();
	Ped pPed = PLAYER::GET_PLAYER_PED(player);

	switch (features)
	{
		case FEATURE_FUNC_FILL_HEALTH:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				ENTITY::SET_ENTITY_HEALTH(pPed, 200);
			}
			break;

		case FEATURE_FUNC_FILL_ARMOR:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				PED::SET_PED_ARMOUR(pPed, 100);
			}
			break;

		case FEATURE_FUNC_TINY_PLAYER:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				PED::SET_PED_CONFIG_FLAG(pPed, 223, Toggle);
			}
			break;

		case FEATURE_FUNC_TOG_FASTRUN:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				if (Toggle)
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);
				else
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1);
			}

		case FEATURE_FUNC_CLEAR_WANTED:
			if (ENTITY::DOES_ENTITY_EXIST(pPed)) 
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(player, 0, false);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, false);
			}
		break;

		case FEATURE_FUNC_CLEAR_BLOOD:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				PED::CLEAR_PED_BLOOD_DAMAGE(pPed);
			}
			break;

		case FEATURE_FUNC_TOG_GOD:
			PLAYER::SET_PLAYER_INVINCIBLE(player, Toggle);
			break;

		case FEATURE_FUNC_TOG_VANISH:
			ENTITY::SET_ENTITY_VISIBLE(pPed, !Toggle, false);
			break;

		case FEATURE_FUNC_TOG_NO_RAGDOLL:
			PED::SET_PED_CAN_RAGDOLL(pPed, !Toggle);
			break;

		case FEATURE_FUNC_TOG_VEH_GOD:
			ENTITY::SET_ENTITY_INVINCIBLE(veh, Toggle);
			ENTITY::SET_ENTITY_PROOFS(veh, Toggle, Toggle, Toggle, Toggle, Toggle, Toggle, Toggle, Toggle);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, !Toggle);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, !Toggle);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, !Toggle);
			break;

		case FEATURE_FUNC_TOG_VEH_VANISH:
			ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX())), !Toggle, false);
			break;

		case FEATURE_FUNC_VEH_REPAIR:
			if (PED::IS_PED_IN_ANY_VEHICLE(pPed, false))
			{
				VEHICLE::SET_VEHICLE_FIXED(PED::GET_VEHICLE_PED_IS_USING(pPed));
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(PED::GET_VEHICLE_PED_IS_USING(pPed));
				VEHICLE::SET_VEHICLE_UNDRIVEABLE(PED::GET_VEHICLE_PED_IS_USING(pPed), false);
			}
			break;

		case FEATURE_FUNC_VEH_CHANGELICENSE:
			if (PED::IS_PED_IN_ANY_VEHICLE(pPed, false))
			{
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "FMMC_KEY_TIP8S", "", "", "", "", "", 20);
				while (true)
				{
					int Result = GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD();
					char* ResultString = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
					if (Result == 1)
					{
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_USING(pPed), ResultString);
						break;
					}
					else if (Result == 2)
					{
						break;
					}
					WAIT(0);
				}
			}
			break;

		case FEATURE_FUNC_VEH_UNFLIP:
			if (PED::IS_PED_IN_ANY_VEHICLE(pPed, false))
			{
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_USING(pPed));
			}
			break;

		case FEATURE_FUNC_WEAPON_REMOVE_ALL:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				WEAPON::REMOVE_ALL_PED_WEAPONS(pPed, false);
			}
			break;

		case FEATURE_FUNC_WEAPON_GIVE_ALL:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				for (int id = 1; id < sizeof(Weapons) / sizeof(Weapons[0]); id++)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(pPed, GAMEPLAY::GET_HASH_KEY(Weapons[id]), 9999, false);
			}
			break;

		case FEATURE_FUNC_TELEPORT:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				if (FloatArg[0] == NULL || FloatArg[1] == NULL || FloatArg[2] == NULL)
				{
					Vector3 coords;
					bool blipFound;

					// Waypoint
					int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
					for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
					{
						if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
						{
							coords = UI::GET_BLIP_INFO_ID_COORD(i);
							blipFound = true;
							break;
						}
					}
					if (blipFound)
					{
						bool groundFound = false;
						static float groundCheckHeight[] = {
							100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
							450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
						};
						for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
						{
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(pPed, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
							WAIT(100);
							if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, FALSE))
							{
								groundFound = true;
								coords.z += 3.0;
								break;
							}
						}
						if (!groundFound)
						{
							coords.z = 1000.0;
							WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
						}
						if (PED::IS_PED_IN_ANY_VEHICLE(pPed, false))
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PED::GET_VEHICLE_PED_IS_USING(pPed), coords.x, coords.y, coords.z, 0, 0, 1);
						else
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(pPed, coords.x, coords.y, coords.z, 0, 0, 1);
					}
				}
				else 
				{
					// Coords
					if (PED::IS_PED_IN_ANY_VEHICLE(pPed, false))
						ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_USING(pPed), FloatArg[0], FloatArg[1], FloatArg[2], 0, 0, 0, 0);
					else
						ENTITY::SET_ENTITY_COORDS(pPed, FloatArg[0], FloatArg[1], FloatArg[2], 0, 0, 0, 0);
				}
			}
			break;

		case FEATURE_FUNC_ENABLE_YANKTON:
			if (Toggle)
			{
				#pragma region North Yankton IPLS
				STREAMING::REQUEST_IPL("plg_01");
				STREAMING::REQUEST_IPL("prologue01");
				STREAMING::REQUEST_IPL("prologue01_lod");
				STREAMING::REQUEST_IPL("prologue01c");
				STREAMING::REQUEST_IPL("prologue01c_lod");
				STREAMING::REQUEST_IPL("prologue01d");
				STREAMING::REQUEST_IPL("prologue01d_lod");
				STREAMING::REQUEST_IPL("prologue01e");
				STREAMING::REQUEST_IPL("prologue01e_lod");
				STREAMING::REQUEST_IPL("prologue01f");
				STREAMING::REQUEST_IPL("prologue01f_lod");
				STREAMING::REQUEST_IPL("prologue01g");
				STREAMING::REQUEST_IPL("prologue01h");
				STREAMING::REQUEST_IPL("prologue01h_lod");
				STREAMING::REQUEST_IPL("prologue01i");
				STREAMING::REQUEST_IPL("prologue01i_lod");
				STREAMING::REQUEST_IPL("prologue01j");
				STREAMING::REQUEST_IPL("prologue01j_lod");
				STREAMING::REQUEST_IPL("prologue01k");
				STREAMING::REQUEST_IPL("prologue01k_lod");
				STREAMING::REQUEST_IPL("prologue01z");
				STREAMING::REQUEST_IPL("prologue01z_lod");
				STREAMING::REQUEST_IPL("plg_02");
				STREAMING::REQUEST_IPL("prologue02");
				STREAMING::REQUEST_IPL("prologue02_lod");
				STREAMING::REQUEST_IPL("plg_03");
				STREAMING::REQUEST_IPL("prologue03");
				STREAMING::REQUEST_IPL("prologue03_lod");
				STREAMING::REQUEST_IPL("prologue03b");
				STREAMING::REQUEST_IPL("prologue03b_lod");
				STREAMING::REQUEST_IPL("prologue03_grv_dug");
				STREAMING::REQUEST_IPL("prologue03_grv_dug_lod");
				STREAMING::REQUEST_IPL("prologue_grv_torch");
				STREAMING::REQUEST_IPL("plg_04");
				STREAMING::REQUEST_IPL("prologue04");
				STREAMING::REQUEST_IPL("prologue04_lod");
				STREAMING::REQUEST_IPL("prologue04b");
				STREAMING::REQUEST_IPL("prologue04b_lod");
				STREAMING::REQUEST_IPL("prologue04_cover");
				STREAMING::REQUEST_IPL("des_protree_end");
				STREAMING::REQUEST_IPL("des_protree_start");
				STREAMING::REQUEST_IPL("des_protree_start_lod");
				STREAMING::REQUEST_IPL("plg_05");
				STREAMING::REQUEST_IPL("prologue05");
				STREAMING::REQUEST_IPL("prologue05_lod");
				STREAMING::REQUEST_IPL("prologue05b");
				STREAMING::REQUEST_IPL("prologue05b_lod");
				STREAMING::REQUEST_IPL("plg_06");
				STREAMING::REQUEST_IPL("prologue06");
				STREAMING::REQUEST_IPL("prologue06_lod");
				STREAMING::REQUEST_IPL("prologue06b");
				STREAMING::REQUEST_IPL("prologue06b_lod");
				STREAMING::REQUEST_IPL("prologue06_int");
				STREAMING::REQUEST_IPL("prologue06_int_lod");
				STREAMING::REQUEST_IPL("prologue06_pannel");
				STREAMING::REQUEST_IPL("prologue06_pannel_lod");
				STREAMING::REQUEST_IPL("prologue_m2_door");
				STREAMING::REQUEST_IPL("prologue_m2_door_lod");
				STREAMING::REQUEST_IPL("plg_occl_00");
				STREAMING::REQUEST_IPL("prologue_occl");
				STREAMING::REQUEST_IPL("plg_rd");
				STREAMING::REQUEST_IPL("prologuerd");
				STREAMING::REQUEST_IPL("prologuerdb");
				STREAMING::REQUEST_IPL("prologuerd_lod");
			}
			else
			{
				STREAMING::REMOVE_IPL("plg_01");
				STREAMING::REMOVE_IPL("prologue01");
				STREAMING::REMOVE_IPL("prologue01_lod");
				STREAMING::REMOVE_IPL("prologue01c");
				STREAMING::REMOVE_IPL("prologue01c_lod");
				STREAMING::REMOVE_IPL("prologue01d");
				STREAMING::REMOVE_IPL("prologue01d_lod");
				STREAMING::REMOVE_IPL("prologue01e");
				STREAMING::REMOVE_IPL("prologue01e_lod");
				STREAMING::REMOVE_IPL("prologue01f");
				STREAMING::REMOVE_IPL("prologue01f_lod");
				STREAMING::REMOVE_IPL("prologue01g");
				STREAMING::REMOVE_IPL("prologue01h");
				STREAMING::REMOVE_IPL("prologue01h_lod");
				STREAMING::REMOVE_IPL("prologue01i");
				STREAMING::REMOVE_IPL("prologue01i_lod");
				STREAMING::REMOVE_IPL("prologue01j");
				STREAMING::REMOVE_IPL("prologue01j_lod");
				STREAMING::REMOVE_IPL("prologue01k");
				STREAMING::REMOVE_IPL("prologue01k_lod");
				STREAMING::REMOVE_IPL("prologue01z");
				STREAMING::REMOVE_IPL("prologue01z_lod");
				STREAMING::REMOVE_IPL("plg_02");
				STREAMING::REMOVE_IPL("prologue02");
				STREAMING::REMOVE_IPL("prologue02_lod");
				STREAMING::REMOVE_IPL("plg_03");
				STREAMING::REMOVE_IPL("prologue03");
				STREAMING::REMOVE_IPL("prologue03_lod");
				STREAMING::REMOVE_IPL("prologue03b");
				STREAMING::REMOVE_IPL("prologue03b_lod");
				STREAMING::REMOVE_IPL("prologue03_grv_dug");
				STREAMING::REMOVE_IPL("prologue03_grv_dug_lod");
				STREAMING::REMOVE_IPL("prologue_grv_torch");
				STREAMING::REMOVE_IPL("plg_04");
				STREAMING::REMOVE_IPL("prologue04");
				STREAMING::REMOVE_IPL("prologue04_lod");
				STREAMING::REMOVE_IPL("prologue04b");
				STREAMING::REMOVE_IPL("prologue04b_lod");
				STREAMING::REMOVE_IPL("prologue04_cover");
				STREAMING::REMOVE_IPL("des_protree_end");
				STREAMING::REMOVE_IPL("des_protree_start");
				STREAMING::REMOVE_IPL("des_protree_start_lod");
				STREAMING::REMOVE_IPL("plg_05");
				STREAMING::REMOVE_IPL("prologue05");
				STREAMING::REMOVE_IPL("prologue05_lod");
				STREAMING::REMOVE_IPL("prologue05b");
				STREAMING::REMOVE_IPL("prologue05b_lod");
				STREAMING::REMOVE_IPL("plg_06");
				STREAMING::REMOVE_IPL("prologue06");
				STREAMING::REMOVE_IPL("prologue06_lod");
				STREAMING::REMOVE_IPL("prologue06b");
				STREAMING::REMOVE_IPL("prologue06b_lod");
				STREAMING::REMOVE_IPL("prologue06_int");
				STREAMING::REMOVE_IPL("prologue06_int_lod");
				STREAMING::REMOVE_IPL("prologue06_pannel");
				STREAMING::REMOVE_IPL("prologue06_pannel_lod");
				STREAMING::REMOVE_IPL("prologue_m2_door");
				STREAMING::REMOVE_IPL("prologue_m2_door_lod");
				STREAMING::REMOVE_IPL("plg_occl_00");
				STREAMING::REMOVE_IPL("prologue_occl");
				STREAMING::REMOVE_IPL("plg_rd");
				STREAMING::REMOVE_IPL("prologuerd");
				STREAMING::REMOVE_IPL("prologuerdb");
				STREAMING::REMOVE_IPL("prologuerd_lod");
				#pragma endregion
			}
			break;

		case FEATURE_FUNC_VEH_SPAWN:
			Vector3 pos;
			pos = ENTITY::GET_ENTITY_COORDS(pPed, false);
			Vehicle vehicle;
			notifyAboveMap(Args);
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(Args));
			while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(Args)))
				WAIT(0);

			vehicle = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(Args), pos.x, pos.y, pos.z + 1.5, 0, 1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(vehicle))
			{
				PED::SET_PED_INTO_VEHICLE(pPed, vehicle, -1);

				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle);
			}
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY(Args));
			break;

		case FEATURE_FUNC_TIME_SET:
			TIME::SET_CLOCK_TIME(IntArg, 0, 0);
			break;

		case FEATURE_FUNC_WEATHER_SET:
			GAMEPLAY::SET_WEATHER_TYPE_NOW(Args);
			break;

		case FEATURE_FUNC_MISC_EXPANDEDRADAR:
			UI::_SET_RADAR_BIGMAP_ENABLED(Toggle, false);
			break;

		case FEATURE_FUNC_MISC_THERMALVISION:
			GRAPHICS::SET_SEETHROUGH(Toggle);
			break;

		case FEATURE_FUNC_MISC_NIGHTVISION:
			GRAPHICS::SET_NIGHTVISION(Toggle);
			break;

		case FEATURE_FUNC_MISC_MOBILERADIO:
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(Toggle);
			break;

		case FEATURE_FUNC_MISC_ACHIEVEMENT_UNLOCK:
			for (int i = 0; i < 57; i++)
				PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER(i);
			break;

		case FEATURE_FUNC_CAM_EFFECT:
			if (ENTITY::DOES_ENTITY_EXIST(pPed))
			{
				if (Toggle)
					GRAPHICS::_START_SCREEN_EFFECT(Args, 0, true);
				else
					GRAPHICS::_STOP_SCREEN_EFFECT(Args);
			}
			break;

	}
}

#pragma endregion