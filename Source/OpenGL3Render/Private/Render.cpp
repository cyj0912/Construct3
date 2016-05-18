#include "Render.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Model.h"
#include <Resource/Public/Mesh.h>
#include <Log.h>
#include <File.h>
#include <System.h>
#include <sstream>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>
C3_NAMESPACE_BEGIN

FShader* Shader2D;
FRenderModel* Mesh;
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
	//glClearColor(0.899f, 0.96f, 1.0f, 1.0f);
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	Shader2D = new FShader;
	Shader2D->Load();

	FAutoRefPtr<RMesh> rmesh = new RMesh("error.obj");
	rmesh->LoadMesh();
	Mesh = new FRenderModel(rmesh);
    Mesh->Prepare();
    glEnable(GL_CULL_FACE);
	//glDisable(GL_CULL_FACE);
    vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

	nvgCreateFont(vg, "normal", RFile::GetPhysicalPath("Roboto-Light.ttf").c_str());
	image = nvgCreateImage(vg, RFile::GetPhysicalPath("loading.png").c_str(), 0);
}

void FRender::RenderOneFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    nvgBeginFrame(vg, Width, Height, 1.0f);
    RenderSprite(FSpriteDesc());
    nvgEndFrame(vg);

    Shader2D->Bind();
	glm::mat4 matModel = glm::rotate(glm::mat4(1.0f), RC.System->GetSystemClock()->GetGameTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 matView = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f + RC.System->GetSystemClock()->GetGameTime()));
	glm::mat4 matView = glm::lookAt(glm::vec3(0, 0, 10.0f), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
    //float PixelsPerUnit = 100.0f;
    //glm::mat4 matProj = glm::ortho(-Width / 2.0f / PixelsPerUnit, Width / 2.0f / PixelsPerUnit,
    //                               -Height / 2.0f / PixelsPerUnit, Height / 2.0f / PixelsPerUnit);
	glm::mat4 matProj = glm::perspective(1.5f, (float)Width / (float)Height, 0.1f, 100.0f);
    glm::mat4 matMV = matView * matModel;
    glm::mat4 matMVP = matProj * matMV;
    GLint uMVPLoc = glGetUniformLocation(Shader2D->Program, "uMVP");
    glUniformMatrix4fv(uMVPLoc, 1, GL_FALSE, value_ptr(matMVP));
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW); //Initial
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //Initial
    Mesh->Draw();

    matModel = glm::translate(glm::mat4(), glm::vec3(-5.0f, 2.0f, 5.0f));
    matMVP = matProj * matView * matModel;
    uMVPLoc = glGetUniformLocation(Shader2D->Program, "uMVP");
    glUniformMatrix4fv(uMVPLoc, 1, GL_FALSE, value_ptr(matMVP));
    Mesh->Draw();

    nvgBeginFrame(vg, Width, Height, 1.0f);
	for(auto cmd : CommandQueue2D)
	{
		cmd->Execute();
	}
	CommandQueue2D.clear();
    std::stringstream ss;
    ss << "SysClk: " << RC.System->GetSystemClock()->GetGameTime() << "s";
    nvgFillColor(vg, nvgRGB(0, 0, 0));
    nvgFontSize(vg, 36);
    nvgFontFace(vg, "normal");
    nvgText(vg, 0, 150, ss.str().c_str(), nullptr);
    nvgEndFrame(vg);
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

void FRender::RenderText(std::string text)
{
	nvgFillColor(vg, nvgRGB(0, 0, 0));
	nvgFontSize(vg, 36);
	nvgFontFace(vg, "normal");
	nvgText(vg, 0, 25, text.c_str(), nullptr);
}

void FRender::Push2DCommand(ICommand* pCmd)
{
	CommandQueue2D.push_back(pCmd);
}

void FRender::RenderModel(FShader* shader, FRenderModel* mesh, float* transformMat4)
{
    Shader2D->Bind();
    GLint uMVPLoc = glGetUniformLocation(Shader2D->Program, "uMVP");
    glUniformMatrix4fv(uMVPLoc, 1, GL_FALSE, transformMat4);
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    Mesh->Draw();
}
C3_NAMESPACE_END
