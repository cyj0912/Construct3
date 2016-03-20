#include <Core.h>
#if C3_OS == C3_OS_WINDOWS_NT
#include <SDL.h>
#include <Windows.h>
#else
#include <SDL2/SDL.h>
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
	RuntimeContext.Construct();
	RuntimeContext.System->Init();
	RuntimeContext.System->SetRootDirectory("E:/Dev/construct3");
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(window);
	SDL_Event e;
	FRender render;
	RuntimeContext.Render = &render;
	render.Init();
	render.Resize(1280, 720);
	RuntimeContext.Engine = new FEngine;
    RuntimeContext.Engine->Test();
    uint64_t timeLast = SDL_GetPerformanceCounter();
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
				RuntimeContext.System->GetSystemClock()->SwitchPause();
		}
        uint64_t timeCurr = SDL_GetPerformanceCounter();
        RuntimeContext.Engine->Update();
		std::function<void()> f = std::bind(&FRender::RenderText, &render, mousePosStr.c_str());
		FCallablePtrCommand<std::function<void()>> cmd = FCallablePtrCommand<std::function<void()>>(&f);
		render.Push2DCommand(&cmd);
		render.RenderOneFrame();
		SDL_GL_SwapWindow(window);
        timeLast = timeCurr;
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
