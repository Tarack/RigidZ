// RigidZ Menu 2017
// Created by: Tarack
// All rights reserved!

#include "menu.h"
#include "keyboard.h"
#include "drawings.h"
#include "functions.h"
#include "config.h"

#include <string>
#include <ctime>
#include <fstream>
#include <iostream>


#pragma region Options
// You can change theese options :)

// Menu open key
DWORD main_key = VK_SUBTRACT;
// Nav down key
DWORD down_key = VK_NUMPAD2;
// Nav up key
DWORD up_key = VK_NUMPAD8;
// Nav left key
DWORD left_key = VK_NUMPAD4;
// Nav right key
DWORD right_key = VK_NUMPAD6;
// Nav back key
DWORD back_key = VK_NUMPAD0;

// Menu Sizes
float MenuX = 165;
float MenuY = 95;
float MenuWidth = 289;
float MenuHeight = 27;

// Menu Colors [ R G B A ]
int MenuColors[3][4] = { 

// Menu background color
{ 0, 0, 0, 125 }, 

// Menu lines color
{ 110, 10, 0, 255 },

// Menu text color
{ 255, 255, 255, 255 }

};
#pragma endregion

#pragma region Variables
// Dont change this :)

char* MenuCaptions;
int CurrentMenu;
char* LatestMenu;
int MenuLines;
int CurrentLine[256] = { 0 };
int loopLock = 0;

int x;
int y;

int CurrentModel = 0;
int Time = 0;
int CurrentWeather = 0;
int MoneyDropAmount = 1500;
int CurrentDesign = 1;
int CurrentTitleFont = 1;

char Name[32];
char Position[64];
char Angle[32];

DWORD timer;

bool CategoryPressed;
#pragma endregion

#pragma region Features with Toggle
bool featureGOD;
bool featureVanish;
bool featureNeverWanted;
bool featureNoRagdoll;
bool featureInfinityAbility;
bool featureSuperJump;
bool featureExplosiveMelee;
bool featureTinyPlayer;
bool featureFastRun;

bool featureVehicleGOD;
bool featureVehicleStickToGround;
bool featureVehicleVanish;
bool featureVehicleRainbow;
bool featureVehicleWarp;

bool featureWeaponInfinityAmmo;
bool featureWeaponExplosiveAmmo;
bool featureWeaponVehicleGun;

bool featureTimeFreeze;
bool featureWeatherFreeze;

bool featureLoadNorthYankton;

bool featureMiscExpandedRadar;
bool featureMiscThermalVision;
bool featureMiscNightVision;
bool featureMiscMobileRadio;
bool featureMiscChaosMode;
bool featureMiscPedBox;

bool featureDropMoney;

bool featureFuncEffectChopVision;
bool featureFuncEffectTazer;
bool featureFuncEffectRampage;
bool featureFuncRaceTurbo;
#pragma endregion

#pragma region Arrays / Structs
char* Vehicles[400] = {
	 "NINEF", "NINEF2", "BLISTA", "ASEA", "ASEA2", "BOATTRAILER", "BUS", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2" ,
	 "SUNTRAP", "COACH", "AIRBUS", "ASTEROPE", "AIRTUG", "AMBULANCE", "BARRACKS", "BARRACKS2", "BALLER", "BALLER2" ,
	 "BJXL", "BANSHEE", "BENSON", "BFINJECTION", "BIFF", "BLAZER", "BLAZER2", "BLAZER3", "BISON", "BISON2" ,
	 "BISON3", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BOBCATXL", "BODHI2", "BUCCANEER", "BUFFALO", "BUFFALO2", "BULLDOZER" ,
	 "BULLET", "BLIMP", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "CAVALCADE", "CAVALCADE2", "POLICET" ,
	 "GBURRITO", "CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CHEETAH", "COMET2", "COGCABRIO", "COQUETTE" ,
	 "CUTTER", "GRESLEY", "DILETTANTE", "DILETTANTE2", "DUNE", "DUNE2", "HOTKNIFE", "DLOADER", "DUBSTA", "DUBSTA2" ,
	 "DUMP", "RUBBLE", "DOCKTUG", "DOMINATOR", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENTITYXF", "EXEMPLAR", "ELEGY2" ,
	 "F620", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FLATBED", "FORKLIFT", "FQ2" ,
	 "FUSILADE", "FUGITIVE", "FUTO", "GRANGER", "GAUNTLET", "HABANERO", "HAULER", "HANDLER", "INFERNUS", "INGOT" ,
	 "INTRUDER", "ISSI2", "JACKAL", "JOURNEY", "JB700", "KHAMELION", "LANDSTALKER", "LGUARD", "MANANA", "MESA" ,
	 "MESA2", "MESA3", "CRUSADER", "MINIVAN", "MIXER", "MIXER2", "MONROE", "MOWER", "MULE", "MULE2" ,
	 "ORACLE", "ORACLE2", "PACKER", "PATRIOT", "PBUS", "PENUMBRA", "PEYOTE", "PHANTOM", "PHOENIX", "PICADOR" ,
	 "POUNDER", "POLICE", "POLICE4", "POLICE2", "POLICE3", "POLICEOLD1", "POLICEOLD2", "PONY", "PONY2", "PRAIRIE" ,
	 "PRANGER", "PREMIER", "PRIMO", "PROPTRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RADI", "RATLOADER" ,
	 "REBEL", "REGINA", "REBEL2", "RENTALBUS", "RUINER", "RUMPO", "RUMPO2", "RHINO", "RIOT", "RIPLEY" ,
	 "ROCOTO", "ROMERO", "SABREGT", "SADLER", "SADLER2", "SANDKING", "SANDKING2", "SCHAFTER2", "SCHWARZER", "SCRAP" ,
	 "SEMINOLE", "SENTINEL", "SENTINEL2", "ZION", "ZION2", "SERRANO", "SHERIFF", "SHERIFF2", "SPEEDO", "SPEEDO2" ,
	 "STANIER", "STINGER", "STINGERGT", "STOCKADE", "STOCKADE3", "STRATUM", "SULTAN", "SUPERD", "SURANO", "SURFER" ,
	 "SURFER2", "SURGE", "TACO", "TAILGATER", "TAXI", "TRASH", "TRACTOR", "TRACTOR2", "TRACTOR3", "GRAINTRAILER" ,
	 "BALETRAILER", "TIPTRUCK", "TIPTRUCK2", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2" ,
	 "UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3", "VOODOO2", "WASHINGTON", "STRETCH", "YOUGA", "ZTYPE", "SANCHEZ", "SANCHEZ2" ,
	 "SCORCHER", "TRIBIKE", "TRIBIKE2", "TRIBIKE3", "FIXTER", "CRUISER", "BMX", "POLICEB", "AKUMA", "CARBONRS" ,
	 "BAGGER", "BATI", "BATI2", "RUFFIAN", "DAEMON", "DOUBLE", "PCJ", "VADER", "VIGERO", "FAGGIO2" ,
	 "HEXER", "ANNIHILATOR", "BUZZARD", "BUZZARD2", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "SKYLIFT", "POLMAV", "MAVERICK" ,
	 "NEMESIS", "FROGGER", "FROGGER2", "CUBAN800", "DUSTER", "STUNT", "MAMMATUS", "JET", "SHAMAL", "LUXOR" ,
	 "TITAN", "LAZER", "CARGOPLANE", "SQUALO", "MARQUIS", "DINGHY", "DINGHY2", "JETMAX", "PREDATOR", "TROPIC" ,
	 "SEASHARK", "SEASHARK2", "SUBMERSIBLE", "TRAILERS", "TRAILERS2", "TRAILERS3", "TVTRAILER", "RAKETRAILER", "TANKER", "TRAILERLOGS" ,
	 "TR2", "TR3", "TR4", "TRFLAT", "TRAILERSMALL", "VELUM", "ADDER", "VOLTIC", "VACCA", "BIFTA" ,
	 "SPEEDER", "PARADISE", "KALAHARI", "JESTER", "TURISMOR", "VESTRA", "ALPHA", "HUNTLEY", "THRUST", "MASSACRO" ,
	 "MASSACRO2", "ZENTORNO", "BLADE", "GLENDALE", "PANTO", "PIGALLE", "WARRENER", "RHAPSODY", "DUBSTA3", "MONSTER" ,
	 "SOVEREIGN", "INNOVATION", "HAKUCHOU", "FUROREGT", "MILJET", "COQUETTE2", "BTYPE", "BUFFALO3", "DOMINATOR2", "GAUNTLET2" ,
	 "MARSHALL", "DUKES", "DUKES2", "STALION", "STALION2", "BLISTA2", "BLISTA3", "DODO", "SUBMERSIBLE2", "HYDRA" ,
	 "INSURGENT", "INSURGENT2", "TECHNICAL", "SAVAGE", "VALKYRIE", "KURUMA", "KURUMA2", "JESTER2", "CASCO", "VELUM2" ,
	 "GUARDIAN", "ENDURO", "LECTRO", "SLAMVAN", "SLAMVAN2", "RATLOADER2", "SWIFT2", "LUXOR2", "FELTZER3", "OSIRIS" ,
	 "VIRGO", "WINDSOR", "BESRA", "SWIFT", "BLIMP2", "VINDICATOR", "TORO", "T20", "COQUETTE3", "CHINO" ,
	 "BRAWLER", "BUCCANEER2", "CHINO2", "FACTION", "FACTION2", "MOONBEAM", "MOONBEAM2", "PRIMO2", "VOODOO", "LURCHER" ,
	 "BTYPE2", "BALLER3", "BALLER4", "BALLER5", "BALLER6", "CARGOBOB4", "COG55", "COG552", "COGNOSCENTI", "COGNOSCENTI2" ,
	 "DINGHY4", "LIMO2", "MAMBA", "NIGHTSHADE", "SCHAFTER3", "SCHAFTER4", "SCHAFTER5", "SCHAFTER6", "SEASHARK3", "SPEEDER2" ,
	 "SUPERVOLITO", "SUPERVOLITO2", "TORO2", "TROPIC2", "VALKYRIE2", "VERLIERER2", "TAMPA", "BANSHEE2", "SULTANRS", "BTYPE3",
};

char* Weathers[7] = { "RAIN", "THUNDER", "SNOW", "SMOG", "FOGGY", "CLEAR", "EXTRASUNNY" };

char* WeatherNames[7] = { "Rainy", "Thunder", "Snow", "Smog", "Foggy", "Clear", "Sunny" };

const int Teleports = 15; // Number of elements in the teleport struct array.
static struct {
	char*  text;
	float x;
	float y;
	float z;
} lines[Teleports] = {
	{ "Waypoint" },
	{ "LS Customs (Los Santos #1)" ,-368, -134, 38.5 },
	{ "LS Airport", -1336.0f, -3044.0f, 13.9f },
	{ "Chilliad", 425.4f, 5614.3f, 766.5f },
	{ "LS Stripclub", 127.4f, -1307.7f, 29.2f },
	{ "Sandy Shores Airfield", 1741.3f, 3279.4f, 41.0f},
	{ "Elburro Heights", 1384.0f, -2057.1f, 52.0f },
	{ "Ferris Wheel", -1670.7f, -1125.0f, 13.0f },
	{ "North Chumash", -3192.6f, 1100.0f, 20.2f },
	{ "Windfarm", 2354.0f, 1830.3f, 101.1f },
	{ "Military Base", -2047.4f, 3132.1f, 32.8f },
	{ "IAA Office", 113.568f, -619.001f, 206.25f },
	{ "Humane Labs", 3614.394f, 3744.803f, 28.9f},
	{ "Fort Zancudo Tower", -2358.132f, 3249.754f, 101.65f },
	{ "North Yankton", 3360.19, -4849.67, 111.8 },
	//{"Sandy Shores Airfield", 1741.3f, 3279.4f, 41.0f },
};
#pragma endregion

void ScriptMain()
{
	notifyAboveMap("RigidZ menu ~g~loaded");

	generate_config("save.ini");

	config cfg("save.ini");
	section* usersection = cfg.get_section("menudesign");

	if (usersection != NULL) 
	{
		GAMEPLAY::STRING_TO_INT(strdup(cfg.get_value("menudesign", "headbg").c_str()), &CurrentDesign);
		GAMEPLAY::STRING_TO_INT(strdup(cfg.get_value("menudesign", "currenttitlefont").c_str()), &CurrentTitleFont);
	}
	while (true)
	{
		Menu::UpdateMenu();
		if (IsKeyJustUp(main_key))
		{
			char saves[256];
			sprintf_s(saves, "[menudesign]\nheadbg = %i\ncurrenttitlefont = %i", CurrentDesign, CurrentTitleFont);

			std::ofstream ostrm;
			ostrm.open("save.ini");
			if (ostrm) {
				ostrm << saves;
			}

			GRAPHICS::GET_SCREEN_RESOLUTION(&x, &y);
			Menu::InitializeMenu(MainOptions);
		}
		
		WAIT(0);
	}
}

void generate_config(const std::string& filename) 
{
	if (!is_exists(filename))
	{
		std::ofstream ostrm;
		ostrm.open(filename);
		if (ostrm) {
			ostrm << "[menudesign]\nheadbg = 2\ncurrenttitlefont = 1";
		}
	}
}

inline bool is_exists(const std::string& name) 
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

namespace Menu
{
	#pragma region Main Menu Draw & Functions
	void MenuMainDraw()
	{

		// [Lines]
		for (int i = 0; i < MenuLines; i++)
		{
			MenuY = 95 + i * 27;
			Draw::Rectangle(MenuX / (float)x, MenuY / (float)y + (0.00278f), MenuWidth / (float)x, MenuHeight / (float)y, MenuColors[0][0], MenuColors[0][1], MenuColors[0][2], MenuColors[0][3]);
		}
		Draw::Rectangle(MenuX / (float)x, (95 + CurrentLine[CurrentMenu] * 27) / (float)y + (0.00278f), MenuWidth / (float)x, MenuHeight / (float)y, MenuColors[1][0], MenuColors[1][1], MenuColors[1][2], 150);

		// [Captions]
		if (CurrentDesign == 1)
			Draw::Rectangle(140 / (float)x, 50 / (float)y, 250 / (float)x, 60 / (float)y, MenuColors[1][0], MenuColors[1][1], MenuColors[1][2], MenuColors[1][3]);
		else if (CurrentDesign == 2)
			Draw::Sprite("shopui_title_gr_gunmod", "shopui_title_gr_gunmod", 165 / (float)x, 50 / (float)y, 289 / (float)x, 70 / (float)y, 0, 255, 255, 255, MenuColors[1][3]);
		else if (CurrentDesign == 3)
			Draw::Sprite("CommonMenu", "interaction_bgd", 165 / (float)x, 50 / (float)y, 290 / (float)x, 60 / (float)y, 0, 255, 255, 255, MenuColors[1][3]);

		if (CurrentTitleFont == 1)
			Draw::Text(MenuCaptions, 165 / (float)x, 40 / (float)y, MenuX / (float)x, (MenuWidth + 90) / (float)x, 0.65, 7, 0, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		else if (CurrentTitleFont == 2)
			Draw::Text(MenuCaptions, 165 / (float)x, 40 / (float)y, MenuX / (float)x, (MenuWidth + 90) / (float)x, 0.65, 1, 0, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		// [Navigation]
		if (timer == NULL)
			timer = GetTickCount();

		if (IsKeyDown(down_key))
		{
			if (CurrentLine[CurrentMenu] < MenuLines)
			{
				if (GetTickCount() > 100 + timer) 
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					CurrentLine[CurrentMenu]++;
					if (CurrentLine[CurrentMenu] == MenuLines)
						CurrentLine[CurrentMenu] = 0;
					timer = NULL;
				}
			}
		}
		else if (IsKeyDown(up_key))
		{
			if (CurrentLine[CurrentMenu] >= 0)
			{
				if (GetTickCount() > 100 + timer)
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					CurrentLine[CurrentMenu]--;
					if (CurrentLine[CurrentMenu] == -1)
						CurrentLine[CurrentMenu] = MenuLines - 1;
					timer = NULL;
				}
			}
		}
	}
	#pragma endregion

	void UpdateMenu()
	{
		#pragma region Updated features
		if (loopLock <= 8)
			loopLock++;

		if (featureNeverWanted)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::GET_PLAYER_INDEX(), 0, false);
			PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::GET_PLAYER_INDEX(), false);
		}
		if (featureExplosiveMelee)
		{
			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::GET_PLAYER_INDEX());
		}
		if (featureSuperJump)
		{
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::GET_PLAYER_INDEX());
		}
		if (featureInfinityAbility)
		{
			PLAYER::SPECIAL_ABILITY_FILL_METER(PLAYER::GET_PLAYER_INDEX(), true);
		}
		
		if (featureVehicleStickToGround)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()), false))
			{
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX())));
			}
		}
		if (featureVehicleRainbow)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()), false))
			{
				if (loopLock > 8)
				{
					VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX())), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 160), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 160));
					loopLock = 0;
				}
			}
		}

		if (featureWeaponInfinityAmmo)
		{
			Hash CurrentWeapon;
			Ped playerPed = PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX());
			if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &CurrentWeapon, 1))
			{
				if (WEAPON::IS_WEAPON_VALID(CurrentWeapon))
				{
					int maxAmmo;
					if (WEAPON::GET_MAX_AMMO(playerPed, CurrentWeapon, &maxAmmo))
					{
						WEAPON::SET_PED_AMMO(playerPed, CurrentWeapon, maxAmmo);

						maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, CurrentWeapon, 1);
						if (maxAmmo > 0)
							WEAPON::SET_AMMO_IN_CLIP(playerPed, CurrentWeapon, maxAmmo);
					}
				}
			}
		}
		if (featureWeaponExplosiveAmmo)
		{
			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER::GET_PLAYER_INDEX());
		}
		if (featureWeaponVehicleGun)
		{
			if (loopLock > 8)
			{
				Ped playerPed = PLAYER::PLAYER_PED_ID();
				if (PED::IS_PED_SHOOTING(playerPed))
				{
					Vector3 coords;
					if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &coords))
					{
						VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(Vehicles[GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, sizeof(Vehicles) / sizeof(Vehicles[0]))]), coords.x, coords.y, coords.z, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 360), true, false);
					}
					loopLock = 0;
				}
			}
			else
			{
				loopLock++;
			}
		}

		if (featureTimeFreeze)
		{
			TIME::SET_CLOCK_TIME(Time, 0, 0);
		}
		if (featureWeatherFreeze)
		{
			GAMEPLAY::SET_WEATHER_TYPE_NOW(Weathers[CurrentWeather]);
		}

		if (featureMiscChaosMode)
		{
			const int numElements = 15;
			const int arrSize = numElements * 2 + 2;
			Ped peds[arrSize];
			peds[0] = numElements;
			int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

			// Nearby Peds
			for (int i = 0; i < count; ++i)
			{
				int offsettedID = i * 2 + 2;
				if (ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]) && peds[offsettedID] != PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()))
				{
					ENTITY::SET_ENTITY_HAS_GRAVITY(peds[offsettedID], false);
					Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(peds[offsettedID]);
					velocity.z = 2.f;
					if (ENTITY::IS_ENTITY_A_PED(peds[offsettedID]) && !PED::IS_PED_RAGDOLL(peds[offsettedID]))
					{
						PED::SET_PED_TO_RAGDOLL(peds[offsettedID], 2000, 0, 2, false, false, false);
						velocity.z = 5.f;
						ENTITY::APPLY_FORCE_TO_ENTITY(peds[offsettedID], 1, 0, 0, ENTITY::IS_ENTITY_A_PED(peds[offsettedID]) ? 10.f : 5.f, 0, 0, 0, 1, 1, 1, 1, 1, 1);
					}
					ENTITY::SET_ENTITY_VELOCITY(peds[offsettedID], velocity.x, velocity.y, velocity.z);
				}
			}

			// Nearby Vehicles
			const int numElements2 = 15;
			const int arrSize2 = numElements2 * 2 + 2;
			Vehicle veh[arrSize2];
			veh[0] = numElements2;
			int count2 = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), veh);

			if (veh != NULL)
			{
				for (int i = 0; i < count2; i++)
				{
					int offsettedID = i * 2 + 2;
					if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]) && veh[offsettedID] != PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX())))
					{
						ENTITY::SET_ENTITY_HAS_GRAVITY(veh[offsettedID], false);
						Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(veh[offsettedID]);
						velocity.z = 2.f;
						ENTITY::SET_ENTITY_VELOCITY(veh[offsettedID], velocity.x, velocity.y, velocity.z);
						ENTITY::APPLY_FORCE_TO_ENTITY(veh[offsettedID], 1, 0, 0, ENTITY::IS_ENTITY_A_PED(veh[offsettedID]) ? 10.f : 5.f, 0, 0, 0, 1, 1, 1, 1, 1, 1);
					}
				}
			}
		}

		if (featureDropMoney)
		{
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()), true);

			OBJECT::CREATE_AMBIENT_PICKUP(0x711D02A4, pos.x + 0.5, pos.y + 0.5, pos.z, 0, MoneyDropAmount, 0x711D02A4, true, true);
		}

		if (featureMiscPedBox)
		{
			const int numElements = 15;
			const int arrSize = numElements * 2 + 2;
			Ped peds[arrSize];
			peds[0] = numElements;
			int count = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

			// Nearby Peds
			for (int i = 0; i < count; ++i)
			{
				int offsettedID = i * 2 + 2;
				if (ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]) && peds[offsettedID] != PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()))
				{
					char hpText[64];

					Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds[offsettedID], true);
					float sx;
					float sy;

					GRAPHICS::DRAW_LINE(pos.x + 1, pos.y, pos.z, pos.x - 1, pos.y, pos.z, 255, 0, 0, 255);
					GRAPHICS::DRAW_LINE(pos.x, pos.y + 1, pos.z, pos.x, pos.y - 1, pos.z, 255, 0, 0, 255);
					GRAPHICS::DRAW_LINE(pos.x, pos.y, pos.z + 1, pos.x, pos.y, pos.z - 1, 255, 0, 0, 255);

					GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(pos.x, pos.y, pos.z, &sx, &sy);

					sprintf_s(hpText, "Health: %i", ENTITY::GET_ENTITY_HEALTH(peds[offsettedID]));
					Draw::Text(hpText, sx, sy, NULL, NULL, 0.25, 0, NULL, 255, 255, 255, 200);
				}
			}
		}
		#pragma endregion
	}

	void InitializeMenu(Menus menu)
	{
		timer = NULL;
		CurrentMenu = menu;
		//notifyAboveMap((char*)CurrentMenu);
		AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);

		switch (menu)
		{

		case MainOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(7, "RigidZ", MainOptions);

				Menu::Category("Self Options", SelfOptions, 0);
				Menu::Category("Vehicle Options", VehicleOptions, 1);
				Menu::Category("Weapon Options", WeaponOptions, 2);
				Menu::Category("Weather/Time Options", TimeOptions, 3);
				Menu::Category("Teleport Options", TeleportOptions, 4);
				Menu::Category("Menu Options", MenuOptions, 5);
				Menu::Category("Misc", MiscOptions, 6);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case SelfOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(15, "Self", SelfOptions);

				Menu::ToggleFunction("GOD Mode", FEATURE_FUNC_TOG_GOD, &featureGOD, 0);
				Menu::ToggleFunction("Invisible", FEATURE_FUNC_TOG_VANISH, &featureVanish, 1);
				Menu::Toggle("Never wanted", &featureNeverWanted, 2);
				Menu::ToggleFunction("No Ragdoll", FEATURE_FUNC_TOG_NO_RAGDOLL, &featureNoRagdoll, 3);
				Menu::Toggle("Infinite Ability", &featureInfinityAbility, 4);
				Menu::Toggle("Super Jump", &featureSuperJump, 5);
				Menu::ToggleFunction("Fast Run", FEATURE_FUNC_TOG_FASTRUN, &featureFastRun, 6);
				Menu::Toggle("Explosive Melee", &featureExplosiveMelee, 7);
				Menu::ToggleFunction("Tiny Player", FEATURE_FUNC_TINY_PLAYER, &featureTinyPlayer, 8);
				Menu::Function("Fill Health", FEATURE_FUNC_FILL_HEALTH, 9);
				Menu::Function("Fill Armor", FEATURE_FUNC_FILL_ARMOR, 10);
				Menu::Function("Clear Wanted", FEATURE_FUNC_CLEAR_WANTED, 11);
				Menu::Function("Clear Blood", FEATURE_FUNC_CLEAR_BLOOD, 12);
				Menu::Category("Money Options", MoneyOptions, 13);
				Menu::Category("Informations", InformationOptions, 14);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}

			break;

		case MoneyOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(2, "Money", MoneyOptions);

				Menu::IntList("Amount", 100, 2000, MoneyDropAmount, 0);
				Menu::Toggle("Drop Money", &featureDropMoney, 1);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case InformationOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(3, "Informations", InformationOptions);

				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX()), true);

				sprintf_s(Name, "Name: %s", PLAYER::GET_PLAYER_NAME(PLAYER::GET_PLAYER_INDEX()));
				sprintf_s(Position, "Pos: %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
				sprintf_s(Angle, "Heading: %.3f", ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED(PLAYER::GET_PLAYER_INDEX())));

				Menu::Label(Name, 0);
				Menu::Label(Position, 1);
				Menu::Label(Angle, 2);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case VehicleOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(8, "Vehicle", VehicleOptions);

				Menu::Category("Spawn Vehicle", VehicleSpawnOptions, 0);
				Menu::ToggleFunction("GOD Mode", FEATURE_FUNC_TOG_VEH_GOD, &featureVehicleGOD, 1);
				Menu::ToggleFunction("Invisible", FEATURE_FUNC_TOG_VEH_VANISH, &featureVehicleVanish, 2);
				Menu::Toggle("Stick to Ground", &featureVehicleStickToGround, 3);
				Menu::Toggle("Rainbow Vehicle", &featureVehicleRainbow, 4);
				Menu::Function("Change Plate Text", FEATURE_FUNC_VEH_CHANGELICENSE, 5);
				Menu::Function("Repair", FEATURE_FUNC_VEH_REPAIR, 6);
				Menu::Function("Unflip", FEATURE_FUNC_VEH_UNFLIP, 7);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case VehicleSpawnOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(2, "Spawn Vehicle", VehicleSpawnOptions);

				Menu::CharList("Model", Vehicles, Vehicles, &CurrentModel, 400, 0);
				Menu::FunctionArgs("Spawn Vehicle", FEATURE_FUNC_VEH_SPAWN, Vehicles[CurrentModel], NULL, 1);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case WeaponOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(4, "Weapon", WeaponOptions);

				Menu::Toggle("Infinity Ammo", &featureWeaponInfinityAmmo, 0);
				Menu::Toggle("Explosive Ammo", &featureWeaponExplosiveAmmo, 1);
				//Menu::Toggle("Vehicle Gun", &featureWeaponVehicleGun, 2);
				Menu::Function("Give all Weapon", FEATURE_FUNC_WEAPON_GIVE_ALL, 2);
				Menu::Function("Remove all Weapon", FEATURE_FUNC_WEAPON_REMOVE_ALL, 3);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case TeleportOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(Teleports + 1, "Teleports", TeleportOptions);

				Menu::ToggleFunction("Load North Yankton", FEATURE_FUNC_ENABLE_YANKTON, &featureLoadNorthYankton, 0);
				for (int i = 0; i < Teleports; i++)
				{
					float TeleportCoords[] = { lines[i].x, lines[i].y, lines[i].z };
					Menu::FunctionArgs(lines[i].text, FEATURE_FUNC_TELEPORT, "", TeleportCoords, i + 1);
				}

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case TimeOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(4, "Weather/Time", TimeOptions);
				Menu::Toggle("Freeze Time", &featureTimeFreeze, 0);
				Menu::Toggle("Freeze Weather", &featureWeatherFreeze, 1);
				Menu::IntListFunction("Set Time", 0, 23, Time, FEATURE_FUNC_TIME_SET, 2);
				Menu::CharListFunction("Set Weather", WeatherNames, Weathers, &CurrentWeather, 6, FEATURE_FUNC_WEATHER_SET, 3);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case MenuOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(2, "Menu", MenuOptions);

				Menu::IntList("Title Design", 1, 3, CurrentDesign, 0);
				Menu::IntList("Title Font", 1, 2, CurrentTitleFont, 1);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case MiscOptions:
			while (true)
			{
				#pragma region BackKey

				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(8, "Misc", MiscOptions);

				Menu::ToggleFunction("Expanded Radar", FEATURE_FUNC_MISC_EXPANDEDRADAR, &featureMiscExpandedRadar, 0);
				Menu::ToggleFunction("Night Vision", FEATURE_FUNC_MISC_NIGHTVISION, &featureMiscNightVision, 1);
				Menu::ToggleFunction("Thermal Vision", FEATURE_FUNC_MISC_THERMALVISION, &featureMiscThermalVision, 2);
				Menu:ToggleFunction("Mobile Radio", FEATURE_FUNC_MISC_MOBILERADIO, &featureMiscMobileRadio, 3);
				Menu::Toggle("Chaos Mode", &featureMiscChaosMode, 4);
				Menu::Toggle("Ped ESP", &featureMiscPedBox, 5);
				Menu::Function("Unlock all Achievements", FEATURE_FUNC_MISC_ACHIEVEMENT_UNLOCK, 6);
				Menu::Category("Effects", EffectOptions, 7);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;

		case EffectOptions:
			while (true)
			{
				#pragma region BackKey
				Menu::MenuMainDraw();
				Menu::UpdateMenu();
				#pragma endregion

				Menu::SetValues(4, "Camera Effects", EffectOptions);

				Menu::ToggleFunctionArgs("ChopVision Effect", FEATURE_FUNC_CAM_EFFECT, &featureFuncEffectChopVision, "ChopVision", NULL, 0);
				Menu::ToggleFunctionArgs("Rampage Effect", FEATURE_FUNC_CAM_EFFECT, &featureFuncEffectRampage, "Rampage", NULL, 1);
				Menu::ToggleFunctionArgs("Tazed Effect", FEATURE_FUNC_CAM_EFFECT, &featureFuncEffectTazer, "Dont_tazeme_bro", NULL, 2);
				Menu::ToggleFunctionArgs("RaceTurbo Effect", FEATURE_FUNC_CAM_EFFECT, &featureFuncRaceTurbo, "RaceTurbo", NULL, 3);

				if (IsKeyJustUp(main_key) || IsKeyJustUp(back_key))
				{
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					break;
				}
				WAIT(0);
			}
			break;
		}
	}

	void SetValues(int linesC, char* MenuCaption, Menus Menu)
	{
		MenuLines = linesC;
		MenuCaptions = MenuCaption;	
		if (CurrentMenu != Menu)
			CurrentMenu = Menu;
	}

	#pragma region Line Types
	void Label(char* DisplayName, int Index)
	{
		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
	}

	void CharList(char* DisplayName, char* Names[], char* Datas[], int* CurrentData, int DataSize, int Index) // Data size required because sizeof() is return false data.
	{
		char Data[128];

		MenuY = 85 + Index * 27;
		sprintf_s(Data, "%s ~m~[%i/%i]", Names[*CurrentData], *CurrentData, DataSize);

		Draw::Text(DisplayName, (MenuX - 120) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		Draw::Text(Data, (MenuX + 95) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, (MenuWidth + 6) / (float)x, 0.35, 0, 2, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (CurrentLine[CurrentMenu] == Index)
		{
			if (GetTickCount() > 100 + timer)
			{
				if (IsKeyDown(left_key))
				{
					if (*CurrentData > 1)
					{
						*CurrentData = *CurrentData - 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
				else if (IsKeyDown(right_key))
				{
					if (*CurrentData < DataSize)
					{
						*CurrentData = *CurrentData + 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
			}
		}
	}

	void IntList(char* DisplayName, int MinValue, int MaxValue, int& ToModify, int Index)
	{
		char Data[128];
		sprintf_s(Data, "~g~[%i]", ToModify);

		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 120) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		Draw::Text(Data, (MenuX + 95) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, (MenuWidth + 6) / (float)x, 0.35, 0, 2, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (CurrentLine[CurrentMenu] == Index)
		{
			if (GetTickCount() > 100 + timer)
			{
				if (IsKeyDown(left_key))
				{
					if (ToModify > MinValue)
					{
						ToModify = ToModify - 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
				else if (IsKeyDown(right_key))
				{
					if (ToModify < MaxValue)
					{
						ToModify = ToModify + 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
			}
		}
	}

	void Category(char* DisplayName, Menus RedirectTo, int Index)
	{
		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.40, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		Draw::Text(">", (MenuX + 95) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, (MenuWidth + 14) / (float)x, 0.40, 0, 2, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (GetTickCount() > 100 + timer)
		{
			if (IsKeyDown(VK_NUMPAD5) && CurrentLine[CurrentMenu] == Index)
			{
				InitializeMenu(RedirectTo);
				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
				timer = NULL;
			}
		}
	}

	void Toggle(char* DisplayName, bool* Toggle, int Index)
	{
		MenuY = 85 + Index * 27;
		if (*Toggle)
			Draw::Sprite("timerbars", "circle_checkpoints", (MenuX + 134) / (float)x, (MenuY + 9) / (float)y + (0.00278f), 14 / (float)x, 14 / (float)y, 0, 102, 255, 102, 185);
		else
			Draw::Sprite("timerbars", "circle_checkpoints", (MenuX + 134) / (float)x, (MenuY + 9) / (float)y + (0.00278f), 14 / (float)x, 14 / (float)y, 0, 255, 51, 51, 185);

		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		//Draw::Text(GetOptionSwitch(Toggle), (MenuX + 95) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, (MenuWidth + 6) / (float)x, 0.35, 0, 2, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		if (GetTickCount() > 100 + timer)
		{
			if (IsKeyDown(VK_NUMPAD5) && CurrentLine[CurrentMenu] == Index)
			{
				*Toggle = !*Toggle;
				timer = NULL;
				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			}
		}
	}

	void IntListFunction(char* DisplayName, int MinValue, int MaxValue, int& ToModify, FEATURE_FUNCS features, int Index)
	{
		char Data[128];
		sprintf_s(Data, "~g~[%i]", ToModify);

		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		Draw::Text(Data, (MenuX + 80) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, (MenuWidth + 6) / (float)x, 0.35, 0, 2, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (CurrentLine[CurrentMenu] == Index)
		{
			if (GetTickCount() > 100 + timer)
			{
				if (IsKeyDown(left_key))
				{
					if (ToModify > MinValue)
					{
						ToModify = ToModify - 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
				else if (IsKeyDown(right_key))
				{
					if (ToModify < MaxValue)
					{
						ToModify = ToModify + 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
				else if (IsKeyDown(VK_NUMPAD5))
				{
					MenuFunctions(features, false, "", NULL, ToModify);
					timer = NULL;

					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
				}
			}
		}
	}

	void CharListFunction(char* DisplayName, char* Names[], char* Datas[], int* CurrentData, int DataSize, FEATURE_FUNCS features, int Index)
	{
		char Data[128];
		sprintf_s(Data, "~g~[%s]", Names[*CurrentData]);

		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		Draw::Text(Data, (MenuX + 80) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, (MenuWidth + 6) / (float)x, 0.35, 0, 2, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (CurrentLine[CurrentMenu] == Index)
		{
			if (GetTickCount() > 100 + timer)
			{
				if (IsKeyDown(left_key))
				{
					if (*CurrentData > 1)
					{
						*CurrentData = *CurrentData - 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
				else if (IsKeyDown(right_key))
				{
					if (*CurrentData < DataSize)
					{
						*CurrentData = *CurrentData + 1;
						timer = NULL;

						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					}
				}
				else if (IsKeyDown(VK_NUMPAD5))
				{
					MenuFunctions(features, false, Datas[*CurrentData], NULL, NULL);
					timer = NULL;

					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
				}
			}
		}
	}

	void Function(char* DisplayName, FEATURE_FUNCS features, int Index)
	{
		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (GetTickCount() > 100 + timer)
		{
			if (IsKeyDown(VK_NUMPAD5) && CurrentLine[CurrentMenu] == Index)
			{
				MenuFunctions(features, false, "", NULL, NULL);
				timer = NULL;
				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			}
		}
	}

	void FunctionArgs(char* DisplayName, FEATURE_FUNCS features, char* CharArg, float FloatArg[], int Index)
	{
		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);

		if (GetTickCount() > 100 + timer)
		{
			if (IsKeyDown(VK_NUMPAD5) && CurrentLine[CurrentMenu] == Index)
			{
				MenuFunctions(features, false, CharArg, FloatArg, NULL);
				timer = NULL;
				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			}
		}
	}

	void ToggleFunction(char* DisplayName, FEATURE_FUNCS features, bool* Toggle, int Index)
	{
		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		
		if (*Toggle)
			Draw::Sprite("timerbars", "circle_checkpoints", (MenuX + 134) / (float)x, (MenuY + 9) / (float)y + (0.00278f), 14 / (float)x, 14 / (float)y, 0, 102, 255, 102, 185);
		else
			Draw::Sprite("timerbars", "circle_checkpoints", (MenuX + 134) / (float)x, (MenuY + 9) / (float)y + (0.00278f), 14 / (float)x, 14 / (float)y, 0, 255, 51, 51, 185);

		if (GetTickCount() > 100 + timer)
		{
			if (IsKeyDown(VK_NUMPAD5) && CurrentLine[CurrentMenu] == Index)
			{
				*Toggle = !*Toggle;
				MenuFunctions(features, *Toggle, "", NULL, NULL);
				timer = NULL;
				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			}
		}
	}

	void ToggleFunctionArgs(char* DisplayName, FEATURE_FUNCS features, bool* Toggle, char* CharArg, float FloatArg[], int Index)
	{
		MenuY = 85 + Index * 27;
		Draw::Text(DisplayName, (MenuX - 140) / (float)x, MenuY / (float)y + (0.00278f), MenuX / (float)x, MenuWidth / (float)x, 0.35, 0, 1, MenuColors[2][0], MenuColors[2][1], MenuColors[2][2], MenuColors[2][3]);
		
		if (*Toggle)
			Draw::Sprite("timerbars", "circle_checkpoints", (MenuX + 110) / (float)x, (MenuY + 9) / (float)y + (0.00278f), 14 / (float)x, 14 / (float)y, 0, 102, 255, 102, 185);
		else
			Draw::Sprite("timerbars", "circle_checkpoints", (MenuX + 110) / (float)x, (MenuY + 9) / (float)y + (0.00278f), 14 / (float)x, 14 / (float)y, 0, 255, 51, 51, 185);

		if (GetTickCount() > 100 + timer)
		{
			if (IsKeyDown(VK_NUMPAD5) && CurrentLine[CurrentMenu] == Index)
			{
				*Toggle = !*Toggle;
				MenuFunctions(features, *Toggle, CharArg, FloatArg, NULL);
				timer = NULL;
				AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			}
		}
	}
	#pragma endregion
}