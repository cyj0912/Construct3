#include <Core.h>
#include <Mesh.h>
#include <File.h>
#include "Model.h"
#include "Render.h"
#include "Shader.h"
#include "SceneGraph.h"

//Standard Library and Thridparty
#include <sstream>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

C3_NAMESPACE_BEGIN

FShader* Shader3D;
FShader* ShaderPost;
FRenderModel* Mesh;
FRenderModel* MeshErr;
struct NVGcontext* vg;
int image;
FSceneGraph SG;
SGCamera* MainCam;
FRender::FRender() : bCloseUp(true)
{
	memset(Flags, 0, sizeof(Flags));
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
	Shader3D = new FShader;
	Shader3D->Load("brdf");
	ShaderPost = new FShader;
	ShaderPost->Load("post");

	//Mesh = new FRenderModel(rmesh);
	//Mesh->Prepare();

	//rmesh = new RMesh("error.obj");
	//rmesh->LoadMesh();
	//MeshErr = new FRenderModel(rmesh);
	//MeshErr->Prepare();

    vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

	nvgCreateFont(vg, "normal", RFile::GetPhysicalPath("Roboto-Light.ttf").c_str());
	image = nvgCreateImage(vg, RFile::GetPhysicalPath("loading.png").c_str(), 0);

	MainCam = new SGCamera(1920, 1080);
	SG.SetActiveCamera(MainCam);
	SGObject* rootNode = new SGObject();
	SG.SetRootNode(rootNode);
	rootNode->Owner = &SG;
	rootNode->Parent = nullptr;

	MainRT.Init();

	float Vertices[] = { 1.0f, 1.0f,
		-1.0f, 1.0f,
		1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		-1.0f, -1.0f };
	glGenVertexArrays(1, &QuadVAO);
	glBindVertexArray(QuadVAO);
	glGenBuffers(1, &QuadVert);
	glBindBuffer(GL_ARRAY_BUFFER, QuadVert);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
	glEnableVertexAttribArray(0);
}

void FRender::RenderOneFrame()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    nvgBeginFrame(vg, Width, Height, 1.0f);
    RenderSprite();
	Hud.Render(Width, Height);
    nvgEndFrame(vg);

	if(Flags[(int)EFlag::ReloadShader])
	{
		Shader3D->Unload();
		Shader3D->Load("brdf");
		ShaderPost->Unload();
		ShaderPost->Load("post");
        Flags[(int)EFlag::ReloadShader] = false;
	}
    if(Flags[(int)EFlag::SwitchNearFar])
    {
        bCloseUp = !bCloseUp;
        Flags[(int)EFlag::SwitchNearFar] = false;
    }
    Shader3D->Bind();
	MainRT.Bind();
	if (!MainRT.Ready())
		throw "Renderbuffer error";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW); //Initial
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //Initial
	MainCam->Resize(Width, Height);
	SG.Render();

	MainRT.BindDefault();
	ShaderPost->Bind();
	MainRT.BindPostprocessTexture();
	glBindVertexArray(QuadVAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_FRAMEBUFFER_SRGB);

    nvgBeginFrame(vg, Width, Height, 1.0f);
	for(auto cmd : CommandQueue2D)
	{
		cmd->Execute();
	}
	CommandQueue2D.clear();
    std::stringstream ss;
    ss << "Time: " << RC.System->GetSystemClock()->GetTotalTime() << "s";
    nvgFillColor(vg, nvgRGB(0, 0, 0));
    nvgFontSize(vg, 36);
    nvgFontFace(vg, "normal");
    nvgText(vg, 0, 150, ss.str().c_str(), nullptr);
    nvgEndFrame(vg);
}

void FRender::RenderSprite()
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
	if (GetMainCamera())
		GetMainCamera()->Resize(Width, Height);
	MainRT.Reinit();
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
    shader->Bind();
    shader->Uniform(FShader::EUniformLocation::MVP, transformMat4);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW); //Initial
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //Initial
    mesh->Draw();
}

SGObject* FRender::NewSGObject()
{
	SGObject* o = new SGObject;
	o->Owner = &SG;
	o->Parent = SG.GetRootNode();
	SG.GetRootNode()->Children.push_back(o);
	return o;
}

SGCamera* FRender::GetMainCamera()
{
	return MainCam;
}

int FRender::GetWidth()
{
	return Width;
}

int FRender::GetHeight()
{
	return Height;
}
C3_NAMESPACE_END
