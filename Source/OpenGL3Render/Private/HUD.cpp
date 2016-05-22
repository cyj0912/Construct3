#include "HUD.h"
#include <nanovg.h>
C3_NAMESPACE_BEGIN
extern struct NVGcontext* vg;

FHUD::FHUD()
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

void FHUD::Render()
{
	nvgFillColor(vg, nvgRGB(0, 0, 0));
	nvgFontSize(vg, 36);
	nvgFontFace(vg, "normal");
	nvgText(vg, 0, 50, "Health", nullptr);

	nvgBeginPath(vg);
	nvgRect(vg, 100, 23, Health * 10, 35);
	nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
	nvgFillColor(vg, nvgRGBA(255, 0, 0, 128));
	nvgFill(vg);

	nvgBeginPath(vg);
	nvgRect(vg, 100, 23, MaxHealth * 10, 35);
	nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
	nvgStroke(vg);
}
C3_NAMESPACE_END
