#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
class SGObject;
class FHUD
{
	int Health, MaxHealth;
	SGObject* Temp;
public:
	FHUD();
	void SetHealth(int v);
	void SetMaxHealth(int m);
	void Render(int w, int h);
};
C3_NAMESPACE_END
