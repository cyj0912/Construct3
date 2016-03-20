//Main game loop
#pragma once
#include <functional>
#include <vector>

#include "renderer/Camera.hpp"
#include "renderer/Renderable.hpp"
#include "State.hpp"
#include "Scene.hpp"

namespace mf {
//Game constants
float cyclesPerMS;
float msPerTick = 1000.f / 30.f;

void CursorTick();
void PathPenTick();

struct GameState : public State {
	static uint64 timeCounterMS;	//Total ms elapsed since start of game
	Renderable tempRenderTest;
	
	std::vector<std::function<void()>> DrawCallList;
	int bgimage;

	void Init() {
		camera.mScale = 10.0f;  //Screen width is 10 meters for now
		camera.Init(glm::mat3(1.0f/camera.mScale, 0.0f, 0.0f,
							  0.0f, 1.0f/camera.mScale * win.aspectRatio, 0.0f,
							  0.0f, 0.0f, 1.0f));
		renderer.Init();

		bgimage = nvgCreateImage(GNvg, "assets/sprites/map.tga", 0);
	}
	
	void Update(float timeCounterMS) {
		//TODO: Handle controls
		//TODO: Adjust camera
		Scene::UpdateAllScenes();
		CursorTick();
		PathPenTick();
	}
	
	void Render(float timeCounterMS, float delta) {
		nvgBeginFrame(GNvg, win.xResPx, win.yResPx, win.aspectRatio);
		NVGpaint p = nvgImagePattern(GNvg, 0.f, 0.f, 1550.0f, 900.0f, 0.f, bgimage, 1.0f);
		nvgBeginPath(GNvg);
		nvgRect(GNvg, 0, 0, 1920, 1080);
		nvgFillPaint(GNvg, p);
		nvgFill(GNvg);
		for (auto call : DrawCallList)
		{
			call();
		}
		nvgEndFrame(GNvg);
		//camera.Draw(tempRenderTest);
	}	
} game;

uint64 GameState::timeCounterMS;

unsigned long long GetTimeCounterMS()
{
	return game.timeCounterMS;
}

std::vector<std::function<void()>>& GetDrawCallList()
{
	return game.DrawCallList;
}

}
