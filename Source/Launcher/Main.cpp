#include <Core.h>
#include <SDL2/SDL.h>
#if C3_OS == C3_OS_WINDOWS_NT
#include <Windows.h>
#endif
#include <System.h>
#include <Render.h>
#include <Engine.h>
#include <functional>
#include <sstream>

using namespace c3;

int main(int argc, char *argv[])
{
#if C3_OS == C3_OS_WINDOWS_NT
	SetProcessDPIAware();
#endif
	RC.Construct();
	RC.System->Init();
#if C3_OS == C3_OS_WINDOWS_NT
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	char path_utf8[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);
	size_t len;
	wcstombs_s(&len, path_utf8, path, MAX_PATH);
	std::string reconPath;
	std::string p(path_utf8);
	std::stringstream ss(p);
	std::string item;
	while(getline(ss, item, '\\'))
	{
		reconPath += item;
		reconPath += '\\';
		struct stat buffer;
		if (stat((reconPath + "Data").c_str(), &buffer) == 0) break;
	}
	RC.System->SetRootDirectory(reconPath.c_str());
#else
	RC.System->SetRootDirectory("/Volumes/XE/construct3");
#endif
	SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(window);
	SDL_Event e;
	FRender render;
	RC.Render = &render;
	render.Init();
	render.Resize(1280, 720);
	RC.Engine = new FEngine;
    RC.Engine->Test();
	std::string mousePosStr;
	for (SDL_PollEvent(&e); e.type != SDL_QUIT; SDL_PollEvent(&e))
	{
		std::stringstream ss;
		if(e.type == SDL_MOUSEMOTION)
		{
			ss << "X:" << e.motion.x << " " << "Y:" << e.motion.y;
			ss << " XRel:" << e.motion.xrel << " YRel:" << e.motion.yrel;
			mousePosStr = ss.str();
		}
		if(e.type == SDL_KEYDOWN)
		{
			if(e.key.keysym.sym == SDLK_SPACE)
				RC.System->GetSystemClock()->SwitchPause();
		}
        RC.Engine->Update();
		std::function<void()> f = std::bind(&FRender::RenderText, &render, mousePosStr);
		FCallablePtrCommand<std::function<void()>> cmd = FCallablePtrCommand<std::function<void()>>(f);
		render.Push2DCommand(&cmd);
		render.RenderOneFrame();
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
