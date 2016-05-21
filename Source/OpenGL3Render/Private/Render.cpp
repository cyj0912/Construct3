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
FRenderModel* Mesh;
FRenderModel* MeshErr;
struct NVGcontext* vg;
int image;
FSceneGraph SG;
SGCamera* mainCam;
SGObject* obj;
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
	Shader3D->Load();

	FAutoRef<RMesh> rmesh = new RMesh("bunny.fbx");
	rmesh->LoadMesh();
	//Mesh = new FRenderModel(rmesh);
	//Mesh->Prepare();

	//rmesh = new RMesh("error.obj");
	//rmesh->LoadMesh();
	//MeshErr = new FRenderModel(rmesh);
	//MeshErr->Prepare();

    vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

	nvgCreateFont(vg, "normal", RFile::GetPhysicalPath("Roboto-Light.ttf").c_str());
	image = nvgCreateImage(vg, RFile::GetPhysicalPath("loading.png").c_str(), 0);

	mainCam = new SGCamera(1000, 1000);
	SG.SetActiveCamera(mainCam);
	SGObject* rootNode = new SGObject();
	SG.SetRootNode(rootNode);
	rootNode->Owner = &SG;
	rootNode->Parent = nullptr;

	obj = this->NewSGObject();
	obj->LoadModelFromResource(rmesh);
}

void FRender::RenderOneFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    nvgBeginFrame(vg, Width, Height, 1.0f);
    RenderSprite();
    nvgEndFrame(vg);

	if(Flags[(int)EFlag::ReloadShader])
	{
		Shader3D->Unload();
		Shader3D->Load();
        Flags[(int)EFlag::ReloadShader] = false;
	}
    if(Flags[(int)EFlag::SwitchNearFar])
    {
        bCloseUp = !bCloseUp;
        Flags[(int)EFlag::SwitchNearFar] = false;
    }
    Shader3D->Bind();
	obj->Move(RC.System->GetSystemClock()->GetDeltaTime(), 0.0f, 0.0f);
	//glm::mat4 matModel = glm::rotate(glm::mat4(1.0f),
	//								 RC.System->GetSystemClock()->GetTotalTime(), glm::vec3(0.0f, 1.0f, 0.0f));
	//matModel = glm::scale(matModel, glm::vec3(2.0f));
 //   //glm::mat4 matView = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f + RC.System->GetSystemClock()->GetTotalTime()));
	//glm::mat4 matView = glm::lookAt(glm::vec3(0.0f, 0.0f, bCloseUp ? 20.0f : 200.0f), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
 //   //float PixelsPerUnit = 100.0f;
 //   //glm::mat4 matProj = glm::ortho(-Width / 2.0f / PixelsPerUnit, Width / 2.0f / PixelsPerUnit,
 //   //                               -Height / 2.0f / PixelsPerUnit, Height / 2.0f / PixelsPerUnit);
	//glm::mat4 matProj = glm::perspective(90.0f / 180.0f * 3.141592654f, (float)Width / (float)Height, 0.1f, 1000.0f);
 //   glm::mat4 matMV = matView * matModel;
 //   glm::mat4 matMVP = matProj * matMV;
	//glm::mat3 matNormal = glm::inverseTranspose(glm::mat3(matMV));
	//Shader3D->Uniform(FShader::EUniformLocation::MV, value_ptr(matMV));
	//Shader3D->Uniform(FShader::EUniformLocation::MVP, value_ptr(matMVP));
	//Shader3D->Uniform(FShader::EUniformLocation::Normal, value_ptr(matNormal));
 //   float g = 25.0f;
 //   Shader3D->Uniform(FShader::EUniformLocation::Glossy, &g);

	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW); //Initial
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //Initial
 //   Mesh->Draw();

 //   float glossiness = 1.0f;
	//for(float disp = -20.0f; disp <= 20.0f; disp += 10.0f)
	//{
 //       if(disp == 0.0f)
 //       {
 //           glossiness *= 5.0f;
 //           continue;
 //       }
 //       glm::mat4 newMatModel = glm::translate(glm::mat4(), glm::vec3(disp, 0.0f, 0.0f)) * matModel;
	//	matMV = matView * newMatModel;
	//	matMVP = matProj * matView * newMatModel;
	//	matNormal = glm::inverseTranspose(glm::mat3(matMV));
	//	Shader3D->Uniform(FShader::EUniformLocation::MV, value_ptr(matMV));
	//	Shader3D->Uniform(FShader::EUniformLocation::MVP, value_ptr(matMVP));
	//	Shader3D->Uniform(FShader::EUniformLocation::Normal, value_ptr(matNormal));
 //       Shader3D->Uniform(FShader::EUniformLocation::Glossy, &glossiness);
	//	Mesh->Draw();
 //       glossiness *= 5.0f;
	//}
	mainCam->Resize(Width, Height);
	SG.Render();
	glDisable(GL_FRAMEBUFFER_SRGB);

    nvgBeginFrame(vg, Width, Height, 1.0f);
	for(auto cmd : CommandQueue2D)
	{
		cmd->Execute();
	}
	CommandQueue2D.clear();
    std::stringstream ss;
    ss << "SysClk: " << RC.System->GetSystemClock()->GetTotalTime() << "s";
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
C3_NAMESPACE_END
