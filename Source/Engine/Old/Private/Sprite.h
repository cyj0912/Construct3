#pragma once
#include "Component.h"
#include <string>
C3_NAMESPACE_BEGIN
class CSprite : public CBaseComponent
{
public:
    CSprite();
	void SetImage(const std::string& imageName);
	void UpdateScreenPosition();
	void Draw();
protected:
	std::string Image;
};
C3_NAMESPACE_END
