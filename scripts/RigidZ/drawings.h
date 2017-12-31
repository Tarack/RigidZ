// RigidZ Menu 2017
// Created by: Taraack
// All rights reserved!

#pragma once
#include "..\..\inc\natives.h"

namespace Draw
{
	/// <summary>
	///	Draws a text. Need to be called inside a loop
	/// align = 0 center 1 left 2 right
	/// fonts = ...
	/// </summary>
	void Text(char* Text, float x, float y, float boxX, float boxY, float scale, int font, int align, int R, int G, int B, int A);

	/// <summary>
	///	Draws a rectangle. Need to be called inside a loop
	/// </summary>
	void Rectangle(float x, float y, float sizeX, float sizeY, int R, int G, int B, int A);

	/// <summary>
	/// Draws the menu glare effect to the screen [Scaleform Movie]
	/// </summary>
	void DrawGlare(float posX, float posY, float sizeX, float sizeY, int R, int G, int B);

	void Sprite(char* TextureDict, char* Texture, float x, float y, float sizeX, float sizeY, float heading, int R, int G, int B, int A);

	float conv360(float base, float min, float max);
}