#pragma once

#ifndef _CRAYAPP_HPP_
#define _CRAYAPP_HPP_

#include "Types.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

class RayTracer;

class RayApp {

private:
	bool    Running;
	uint64	Frame;

	TTF_Font* Font;
	SDL_Window*   MainWindow;
	SDL_Renderer* MainRenderer;
	SDL_Surface*  RaySurface;
	SDL_Surface*  MainSurface;
	SDL_Surface*  DebugSurface;
	SDL_Texture*  RayTexture;
	SDL_Texture*  DebugTexture;

	SDL_Rect RayRect;
	SDL_Rect DebugRect;

	uint08 comp = 4;
	uint32 w = 800;
	uint32 h = 400;
	uint32 ti = (h * w) * comp;

	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* CreateRaySurface();
	SDL_Surface* RenderText(const char* string, SDL_Color color);

	RayTracer* m_rayTracer;	
public:
	RayApp();

	int32 Execute();

public:
	bool Init();

	void Event(SDL_Event* Event);

	void Loop();

	void Render();

	void Cleanup();

	void RayTrace();

	void ClearTrace();
};

#endif