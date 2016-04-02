#pragma once
#include <Core.h>
#include <Command.h>
#include <vector>
C3_NAMESPACE_BEGIN
typedef void* (*GLLOADADDRESS)(const char *name);

struct FSpriteDesc
{
	
};

class FShader;
class FRenderMesh;

class IRender
{
public:
	virtual void Init() = 0;
	virtual void Init(GLLOADADDRESS loader) = 0;
	virtual void Shutdown() = 0;
	virtual void PrepareGL() = 0;
	virtual void RenderOneFrame() = 0;
	virtual void RenderSprite(const FSpriteDesc& desc) = 0;
	virtual void Resize(int w, int h) = 0;
	virtual void DrawControl(float x, float y, float w, float h) = 0;
};

class FRender : public IRender
{
public:
    FRender();
    void Init() override;
	void Init(GLLOADADDRESS loader) override;
	void Shutdown() override;
	void PrepareGL() override;
    void RenderOneFrame() override;
	void RenderSprite(const FSpriteDesc& desc) override;
	void Resize(int w, int h) override;
	void DrawControl(float x, float y, float w, float h) override;
	void RenderText(const char* text);
	void Push2DCommand(ICommand* pCmd);
	void RenderModel(FShader* shader, FRenderMesh* mesh, float* transformMat4);

private:
	int Width, Height;
	std::vector<ICommand*> CommandQueue2D;
};
C3_NAMESPACE_END
