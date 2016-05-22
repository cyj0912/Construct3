#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
class FHUD
{
	int Health, MaxHealth;
public:
	FHUD();
	void SetHealth(int v);
	void SetMaxHealth(int m);
	void Render();
};
C3_NAMESPACE_END
