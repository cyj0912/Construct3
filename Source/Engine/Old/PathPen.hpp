#pragma once

#include "ComponentId.hpp"
#include "Entity.hpp"
#include "Drawable.hpp"
#include "Cursor.hpp"

namespace mf {

class PathPen : public Entity, public Drawable, public InputEventListener {
public:
	void OnEvent(int e) override
	{
		if(e == ENTER_PEN_EDIT_MODE)
		{
			EdgePainter = WallEdgePainter();
		}
		else if(e == SAVE_PEN)
		{
			InvisibleWall* wall = (InvisibleWall*)CreateEntity("InvisibleWall");
			wall->ChainDef = EdgePainter.ToString();
			wall->ShapeType = "EdgeChain";
			wall->InitPhysicsBody();
			Scenes[0]->Entities.push_back(wall);
		}
		else if(e == DROP_A_POINT)
		{
			glm::vec2 worldPoint = camera.ScreenToWorld(cursor.X, cursor.Y);
			EdgePainter.AppendPoint(worldPoint.x, worldPoint.y);
		}
	}

	PathPen()
	{
		GlobalInputHandler.Listeners.push_back(this);
	}

	~PathPen()
	{
		GlobalInputHandler.EraseFromListener(this);
	}

	void GetComponent(int cid, void** returnPtr) override
	{
        Entity::GetComponent(cid, returnPtr);
		if (*returnPtr != nullptr)
			return;
		if (cid == MF_DRAWABLE)
			*returnPtr = static_cast<Drawable*>(this);
	}

	void AddToDrawList() override
	{
		GetDrawCallList().push_back(std::bind(&PathPen::Render, this));
	}

	void Render() override
	{
		nvgBeginPath(GNvg);
		if (EdgePainter.Points.size() >= 4)
		{
			glm::vec2 temp = camera.WorldToScreen(glm::vec2(EdgePainter.Points[0], EdgePainter.Points[1]));
			nvgMoveTo(GNvg, temp[0], temp[1]);
			for (int i = 2; i < EdgePainter.Points.size(); i += 2)
			{
				temp = camera.WorldToScreen(glm::vec2(EdgePainter.Points[i], EdgePainter.Points[i + 1]));
				nvgLineTo(GNvg, temp[0], temp[1]);
			}
		}
		nvgStrokeColor(GNvg, nvgRGB(255, 255, 255));
		nvgStrokeWidth(GNvg, 5);
		nvgStroke(GNvg);
	}

	void Tick() override
	{
		AddToDrawList();
	}

	WallEdgePainter EdgePainter;
} pathpen;

void PathPenTick()
{
	pathpen.Tick();
}

}
