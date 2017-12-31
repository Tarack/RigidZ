#pragma once

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"
#include "..\..\inc\enums.h"

#include "..\..\inc\main.h"

#include "functions.h"

#include <string>
#include <ctime>
#include <fstream>
#include <iostream>

void ScriptMain();

enum Menus
{
	MainOptions,
	SelfOptions,
	VehicleOptions,
	VehicleSpawnOptions,
	WeaponOptions,
	WeatherOptions,
	TimeOptions,
	TeleportOptions,
	InformationOptions,
	MiscOptions,
	MoneyOptions,
	EffectOptions,
	MenuOptions,
};

void generate_config(const std::string& filename);
inline bool is_exists(const std::string& name);
namespace Menu
{
	void MenuMainDraw();
	void InitializeMenu(Menus menu);
	void SetValues(int linesC, char* MenuCaption, Menus Menu);
	void UpdateMenu();
	void Category(char* DisplayName, Menus RedirectTo, int Index);
	void Toggle(char* DisplayName, bool* Toggle, int Index);
	void Function(char* DisplayName, FEATURE_FUNCS features, int Index);
	void ToggleFunction(char* DisplayName, FEATURE_FUNCS features, bool* Toggle, int Index);
	void FunctionArgs(char* DisplayName, FEATURE_FUNCS features, char* CharArg, float FloatArg[], int Index);
	void ToggleFunctionArgs(char* DisplayName, FEATURE_FUNCS features, bool* Toggle, char* CharArg, float FloatArg[], int Index);
	void Label(char* DisplayName, int Index);
	void CharList(char* DisplayName, char* Names[], char* Datas[], int* CurrentData, int DataSize, int Index);
	void IntListFunction(char* DisplayName, int MinValue, int MaxValue, int& ToModify, FEATURE_FUNCS features, int Index);
	void CharListFunction(char* DisplayName, char* Names[], char* Datas[], int* CurrentData, int DataSize, FEATURE_FUNCS features, int Index);
	void IntList(char* DisplayName, int MinValue, int MaxValue, int& ToModify, int Index);
}