// RigidZ Menu 2017
// Created by: Taraack
// All rights reserved!

#include "drawings.h"
#include <math.h>

namespace Draw
{
	/// <summary>
	///	Draws a text. Need to be called inside a loop
	/// align = 0 center 1 left 2 right
	/// fonts = ...
	/// </summary>
	void Text(char* Text, float x, float y,float boxX, float boxY,float scale, int font, int align, int R, int G, int B, int A)
	{
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, scale);
		UI::SET_TEXT_COLOUR(R, G, B, A);
		if (align >= 0)
			UI::SET_TEXT_JUSTIFICATION(align);
		UI::SET_TEXT_OUTLINE();
		if (boxX != NULL || boxY != NULL)
			UI::SET_TEXT_WRAP(boxX, boxY);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
	}

	/// <summary>
	///	Draws a rectangle. Need to be called inside a loop
	/// </summary>
	void Rectangle(float x, float y, float sizeX, float sizeY, int R, int G, int B, int A)
	{
		GRAPHICS::DRAW_RECT(x, y, sizeX, sizeY, R, G, B, A);
	}

	void Sprite(char* TextureDict, char* Texture, float x, float y, float sizeX, float sizeY, float heading, int R, int G, int B, int A)
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(TextureDict, false);
		GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(TextureDict);
		GRAPHICS::DRAW_SPRITE(TextureDict, Texture, x, y, sizeX, sizeY, heading, R, G, B, A);
		//GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(TextureDict);
	}

	void DrawGlare(float posX, float posY, float sizeX, float sizeY, int R, int G, int B)
	{
		float gGlareDir;
			int gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");

			Vector3 rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);
			float dir = conv360(rot.z, 0, 360);
			if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5)
			{
				gGlareDir = dir;
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(gGlareHandle, "SET_DATA_SLOT");
				GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_FLOAT(gGlareDir);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			}
			GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, posX, posY, sizeX, sizeY, R, G, B, 255, 0);
			GRAPHICS::_SCREEN_DRAW_POSITION_END();
	}

	float conv360(float base, float min, float max) 
	{

		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;
		base -= round(base - min / fVar0) * fVar0;
		if (base < min) base += fVar0;
		return base;
	}
}