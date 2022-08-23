#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

/*
[------------------------------------------------]
		  Copyright(C) 2022  JTB Games
[------------------------------------------------]
*/

struct MiniEngine;
struct SMALL_RECT;
//Create a MiniEngine instance
struct MiniEngine MiniEngine_Create(LPCWSTR name, int screen_width, int screen_height, int (*update)(struct MiniEngine*));
//Start running a MiniEngine instance
int MiniEngine_Run(struct MiniEngine* engine);
//Clear the screen buffer
void MiniEngine_Render_Clear(struct MiniEngine* engine, char c);
//Draw pixel to screen buffer
void MiniEngine_Render_Pixel(struct MiniEngine* engine, int x, int y, char c);
#include"Engine.c"