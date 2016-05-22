#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
typedef unsigned int GLuint;
class FRenderTarget
{
	enum {Color0, MAX};
	GLuint FB, Tex[MAX], RB;
public:
	void Init();
	void Reinit();
	void Bind();
	bool Ready();
	void BindPostprocessTexture();
	static void BindDefault();
};
C3_NAMESPACE_END
