#include "HUD.h"
#include "Model.h"
#include "Render.h"
#include "SceneGraph.h"
#include <Engine/Public/Engine.h>
#include <nanovg.h>
C3_NAMESPACE_BEGIN
extern struct NVGcontext* vg;

FHUD::FHUD() : Temp(nullptr)
{
	Health = 100;
	MaxHealth = 100;
}

void FHUD::SetHealth(int v)
{
	Health = v;
}

void FHUD::SetMaxHealth(int m)
{
	MaxHealth = m;
}
SGObject* ttttt;
void FHUD::Render(int w, int h)
{
	if(!Temp)
	{
		ttttt = RC.Render->NewSGObject();
		ttttt->LoadModelFromResource(RC.Engine->EnemyMesh1);
		ttttt->SetScale(glm::vec3(1.2f));
		ttttt->SetVisible(false);
	}
	if(Health <= 0)
	{
		nvgBeginPath(vg);
		nvgRect(vg, 0, 0, (float)w, (float)h);
		nvgFillColor(vg, nvgRGBA(255, 0, 0, 200));
		nvgFill(vg);
		ttttt->SetVisible(true);
	}
	else
	{
		ttttt->SetVisible(false);
		nvgFillColor(vg, nvgRGB(0, 0, 0));
		nvgFontSize(vg, 36);
		nvgFontFace(vg, "normal");
		nvgText(vg, 0, 50, "Health", nullptr);

		nvgBeginPath(vg);
		nvgRect(vg, 100, 23, (float)Health * 10, 35);
		nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
		nvgFillColor(vg, nvgRGBA(255, 0, 0, 128));
		nvgFill(vg);

		nvgBeginPath(vg);
		nvgRect(vg, 100, 23, (float)MaxHealth * 10, 35);
		nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
		nvgStroke(vg);
	}
}
C3_NAMESPACE_END
