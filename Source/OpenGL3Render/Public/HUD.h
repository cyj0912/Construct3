#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
class FRenderModel;
class FHUD
{
	int Health, MaxHealth;
	FRenderModel* Temp;
public:
	FHUD();
	void SetHealth(int v);
	void SetMaxHealth(int m);
	void Render(int w, int h);
};
C3_NAMESPACE_END
