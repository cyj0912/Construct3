#pragma once
#include <functional>
#include <vector>
#include "Entity.hpp"
#include "Drawable.hpp"

namespace mf {

std::vector<std::function<void()>>& GetDrawCallList();

class Cursor : public Entity, public Drawable {
public:
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
		GetDrawCallList().push_back(std::bind(&Cursor::Render, this));
	}

	void Render() override
	{
		nvgSave(GNvg);
		nvgBeginPath(GNvg);
		nvgRect(GNvg, 100, 100, 200, 200);
		nvgFillColor(GNvg, nvgRGBA(100, 200, 200, 100));
		nvgFill(GNvg);
		nvgRestore(GNvg);
	}

	void Tick() override
	{
		AddToDrawList();
	}

	int X, Y;
} cursor;

void CursorTick()
{
	cursor.Tick();
}

void CursorSet(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
}

}
