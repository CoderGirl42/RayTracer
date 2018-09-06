

#include <thread>
#include <iostream>

#include "RayApp.hpp"
#include "RayTracer.hpp"
#include "Stopwatch.hpp"

#include "SDL_surface.h"
#include "SDL_ttf.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

RayApp::RayApp() 
{
	MainWindow = nullptr;
	MainRenderer = nullptr;
	m_rayTracer = nullptr;
	Running = true;
}

int32 RayApp::Execute()
{
	if (Init() == false)
	{
		return -1;
	}

	SDL_Event e;

	while (Running)
	{
		while (SDL_PollEvent(&e))
		{
			Event(&e);
		}

		Loop();
		Render();
	}

	Cleanup();

	return 0;
}


bool RayApp::Init() 
{
	std::cout.imbue(std::locale(""));

	Frame = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		return false;
	}

	MainWindow = SDL_CreateWindow("Sugar Ray Charles", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (MainWindow == NULL)
	{
		return false;
	}

	MainRenderer = SDL_CreateRenderer(MainWindow, -1, 0);

	if (TTF_Init() == -1) 
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	Font = TTF_OpenFont("C:\\Users\\maris\\Documents\\Visual Studio 2017\\Projects\\RayCharles\\Debug\\VeraMono.ttf", 12);
	TTF_SetFontKerning(Font, 1);
	TTF_SetFontHinting(Font, TTF_HINTING_MONO);

	RayRect.x = 0;
	RayRect.y = 0;
	RayRect.w = w;
	RayRect.h = h;

	m_rayTracer = new RayTracer(nullptr, h, w, SurfaceFormat::COLOR_FORMAT_RGBA32);

	RaySurface = CreateRaySurface();

	return true;
}

void RayApp::Event(SDL_Event* Event)
{
	if(Event->type == SDL_QUIT) 
	{
		m_rayTracer->Stop();
        Running = false;
    }

	if (Event->type == SDL_KEYUP)
	{
		switch (Event->key.keysym.sym) {
		case SDLK_r:
			RayTrace();
			break;
		case SDLK_c:
			ClearTrace();
			break;
		case SDLK_f:
			m_rayTracer->Fill(128, 30, 55, 255);
		default:
			break;
		}
	}
}

void RayApp::Loop()
{
	Frame++;
}

void RayApp::Render()
{	
	static uint64 totalTime;
	static uint64 elapsedTime;
	
	int32 textWidth;
	int32 textHeight;
	uint08 bufsize = 100;
	char* buffer = new char[bufsize];
	Stopwatch* timer = new Stopwatch();

	TTF_SizeText(Font, buffer, &textWidth, &textHeight);
	DebugRect.w = textWidth;
	DebugRect.h = textHeight;

	SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);

	sprintf_s(buffer, bufsize, "Frame: %6lld Frametime: %3d (ms) / %6.2f (s), FPS: %6.2f", Frame, long(elapsedTime), float(elapsedTime) / 1000.00f, Frame / (totalTime / 1000.00f));
	DebugSurface = RenderText(buffer, White);
	
	//if (!m_rayTracer->IsTracing())
	//	m_rayTracer->Start();

	RayTexture = SDL_CreateTextureFromSurface(MainRenderer, RaySurface);
	DebugTexture = SDL_CreateTextureFromSurface(MainRenderer, DebugSurface);

	SDL_RenderClear(MainRenderer);
	SDL_RenderCopyEx(MainRenderer, RayTexture, NULL, NULL, /*&RayRect,*/ NULL, NULL, (SDL_RendererFlip)(SDL_FLIP_VERTICAL));
	SDL_RenderCopy(MainRenderer, DebugTexture, NULL, &DebugRect);
	SDL_RenderPresent(MainRenderer);
	
	if (DebugSurface != NULL)
		SDL_FreeSurface(DebugSurface);
	if (RayTexture != NULL)
		SDL_DestroyTexture(RayTexture);
	if (DebugTexture != NULL)
		SDL_DestroyTexture(DebugTexture);

	delete buffer;

	elapsedTime = timer->elapsed().count();
	totalTime += elapsedTime;
}

void RayApp::Cleanup()
{
	if (RaySurface != NULL)
		SDL_FreeSurface(RaySurface);

	//if(MainSurface != NULL)
	//	SDL_FreeSurface(MainSurface);

	TTF_CloseFont(Font);

	TTF_Quit();
	SDL_Quit();
}

void RayApp::ClearTrace()
{
	std::thread t(&RayTracer::Clear, m_rayTracer);
	t.detach();
}

void RayApp::RayTrace()
{
	std::thread t(&RayTracer::Start, m_rayTracer);
	t.detach();
}

SDL_Surface* RayApp::RenderText(const char* string, SDL_Color color)
{
	SDL_Surface* temp = NULL;

	temp = TTF_RenderText_Shaded(Font, string, color, { 0, 0, 0, }); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	return temp;
}

SDL_Surface* RayApp::CreateRaySurface()
{
	// This example shows how to create a SDL_Surface* with the data loaded
	// from an image file with stb_image.h (https://github.com/nothings/stb/)

	// the color format you request stb_image to output,
	// use STBI_rgb if you don't want/need the alpha channel
	int req_format = STBI_rgb_alpha;

	int depth, pitch;
	Uint32 pixel_format;
	if (req_format == STBI_rgb) 
	{
		depth = 24;
		pitch = 3 * w; // 3 bytes per pixel * pixels per row
		pixel_format = SDL_PIXELFORMAT_RGB24;
	}
	else 
	{ // STBI_rgb_alpha (RGBA)
		depth = 32;
		pitch = 4 * w;
		pixel_format = SDL_PIXELFORMAT_RGBA32;
	}

	SDL_Surface* temp = SDL_CreateRGBSurfaceWithFormatFrom((void*)m_rayTracer->GetSurface(), w, h, depth, pitch, pixel_format);

	if (temp == NULL)
	{
		SDL_Log("Creating surface failed: %s", SDL_GetError());
	}

	return temp;
}







