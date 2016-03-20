#pragma once
#include "Movable.hpp"
#include <functional>
#include "ComponentId.hpp"

namespace mf {

std::vector<std::function<void()>>& GetDrawCallList();

int PlayerImage = -1;

class Drawable {
public:
	virtual void GetComponent(int cid, void** returnPtr) = 0;

	virtual void AddToDrawList()
	{
		GetDrawCallList().push_back(std::bind(&Drawable::Render, this));
	}

	virtual void Render()
	{
		Movable* mov = nullptr;
		this->GetComponent(MF_MOVABLE, (void**)&mov);
		glm::vec2 ScreenPos = camera.WorldToScreen(mov->Position);
		nvgSave(GNvg);
		nvgBeginPath(GNvg);
		nvgRect(GNvg, ScreenPos.x - 10, ScreenPos.y - 10, 20, 20);
		nvgFillColor(GNvg, nvgRGB(255, 200, 150));
		nvgFill(GNvg);
		nvgRestore(GNvg);

		nvgSave(GNvg);
		nvgBeginPath(GNvg);
		if(PlayerImage == -1)
			PlayerImage = nvgCreateImage(GNvg, "assets/sprites/Untitled.png", 0);
		int x, y;
		nvgImageSize(GNvg, PlayerImage, &x, &y);
		NVGpaint p = nvgImagePattern(GNvg, 1.f, 1.f, 70.f, 70.f, 0.f, PlayerImage, 1.0f);
		nvgRect(GNvg, ScreenPos.x, ScreenPos.y, 100, 100);
		nvgFillPaint(GNvg, p);
		nvgFill(GNvg);

		nvgRestore(GNvg);
	}
};

}
