#include "Render.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Mesh.h"
#include <Log.h>
#include <File.h>
#include <System.h>
#include <sstream>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
C3_NAMESPACE_BEGIN

FShader* Shader2D;
FMesh* Mesh;
struct NVGcontext* vg;
int image;
FRender::FRender()
{
}

void FRender::Init()
{
    if(!gladLoadGL())
        throw 0;
	PrepareGL();
}

void FRender::Init(GLLOADADDRESS loader)
{
	if(!gladLoadGLLoader(loader))
        throw 0;
	PrepareGL();
}

void FRender::Shutdown()
{
}

void FRender::PrepareGL()
{
    const unsigned char* glVersion = glGetString(GL_VERSION);
    FLog::Debug(reinterpret_cast<const char*>(glVersion));
	glClearColor(0.899f, 0.96f, 1.0f, 1.0f);
	Shader2D = new FShader;
	Shader2D->Load();
	Mesh = new FMesh;
    Mesh->Prepare();
    glEnable(GL_CULL_FACE);
    vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

	nvgCreateFont(vg, "normal", FFile::GetPhysicalPath("Roboto-Light.ttf").c_str());
	image = nvgCreateImage(vg, FFile::GetPhysicalPath("loading.png").c_str(), 0);
}

void FRender::RenderOneFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    nvgBeginFrame(vg, Width, Height, 1.0f);
    
    RenderSprite(FSpriteDesc());

    /*
    NVGpaint bg;
    bg = nvgBoxGradient(vg, 300, 400, 200, 300, 3, 10, nvgRGBA(255, 255, 255, 200), nvgRGBA(32, 32, 32, 32));
    nvgBeginPath(vg);
    nvgRoundedRect(vg, 300, 400, 200, 300, 4);
    nvgFillPaint(vg, bg);
    nvgFill(vg);

    nvgBeginPath(vg);
    nvgRoundedRect(vg, 300, 400, 200, 300, 4-0.5f);
    nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 48));
    nvgStroke(vg);

	DrawControl(300, 300, 100, 100);
     */

	for(auto cmd : CommandQueue2D)
	{
		cmd->Execute();
	}
	CommandQueue2D.clear();

    std::stringstream ss;
    ss << RuntimeContext.System->GetSystemClock()->GetGameTime() << "s";
    nvgFillColor(vg, nvgRGB(0, 0, 0));
    nvgFontSize(vg, 36);
    nvgFontFace(vg, "normal");
    nvgText(vg, 0, 150, ss.str().c_str(), nullptr);

    nvgEndFrame(vg);

	/*
    Shader2D->Bind();
    glm::mat4 matModel = glm::mat4();
    glm::mat4 matView = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -0.5f));
    float PixelsPerUnit = 100.0f;
    glm::mat4 matProj = glm::ortho(-Width / 2.0f / PixelsPerUnit, Width / 2 / PixelsPerUnit,
                                   -Height / 2.0f / PixelsPerUnit, Height / 2.0f / PixelsPerUnit);
    glm::mat4 matMV = matModel * matView;
    glm::mat4 matMVP = matMV * matProj;
    GLint uMVPLoc = glGetUniformLocation(Shader2D->Program, "uMVP");
    glUniformMatrix4fv(uMVPLoc, 1, GL_FALSE, value_ptr(matMVP));
    Mesh->Draw();
    */
}

void FRender::RenderSprite(const FSpriteDesc& desc)
{
	NVGpaint bg = nvgImagePattern(vg, 0, 0, (float)Width, (float)Height, 0.0f, image, 1.0f);
	nvgBeginPath(vg);
	nvgRect(vg, 0, 0, (float)Width, (float)Height);
	nvgFillPaint(vg, bg);
	//nvgFillColor(vg, nvgRGBAf(1.0f, 1.0f, 1.0f, 1.0f));
	nvgFill(vg);
}

void FRender::Resize(int w, int h)
{
	Width = w;
	Height = h;
}

void FRender::DrawControl(float x, float y, float w, float h)
{
	nvgBeginPath(vg);
	nvgRect(vg, x, y, w, h);
	nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 255));
	nvgStroke(vg);
}

void FRender::RenderText(const char* text)
{
	nvgFillColor(vg, nvgRGB(0, 0, 0));
	nvgFontSize(vg, 36);
	nvgFontFace(vg, "normal");
	nvgText(vg, 0, 25, text, nullptr);
}

void FRender::Push2DCommand(ICommand* pCmd)
{
	CommandQueue2D.push_back(pCmd);
}

C3_NAMESPACE_END
