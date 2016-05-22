#pragma once
#include <Core.h>
#include <IRender.h>
#include <vector>
#include "HUD.h"
C3_NAMESPACE_BEGIN

class FShader;
class FRenderModel;

class FRender : public IRender
{
public:
    FRender();
    void Init() override;
	void Init(GLLOADADDRESS loader) override;
	void Shutdown() override;
	void PrepareGL() override;
    void RenderOneFrame() override;
	void RenderSprite() override;
	void Resize(int w, int h) override;
	void DrawControl(float x, float y, float w, float h) override;
	void RenderText(std::string text);
	void Push2DCommand(ICommand* pCmd);
	void RenderModel(FShader* shader, FRenderModel* mesh, float* transformMat4);
	void SetFlag(EFlag flag, bool value) override
	{
        Flags[(int)flag] = true;
	}
	SGObject* NewSGObject() override;
	SGCamera* GetMainCamera() override;
	FHUD* GetHUD() override
	{
		return &Hud;
	}

private:
	int Width, Height;
	std::vector<ICommand*> CommandQueue2D;
	bool Flags[(int)EFlag::NUMBEROFFLAGS];
	bool bCloseUp;
	FHUD Hud;
};
C3_NAMESPACE_END
