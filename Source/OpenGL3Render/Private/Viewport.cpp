#include "Viewport.h"
#include <glad/glad.h>
#include "Render.h"
C3_NAMESPACE_BEGIN
void FRenderTarget::Init()
{
	glGenTextures(MAX, Tex);
	glBindTexture(GL_TEXTURE_2D, Tex[Color0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RC.Render->GetWidth(), RC.Render->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenRenderbuffers(MAX, &RB);
	glBindRenderbuffer(GL_RENDERBUFFER, RB);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, RC.Render->GetWidth(), RC.Render->GetHeight());

	glGenFramebuffers(1, &FB);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FB);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Tex[Color0], 0);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RB);
}

void FRenderTarget::Reinit()
{
	glDeleteTextures(MAX, Tex);
	glDeleteRenderbuffers(1, &RB);
	glDeleteFramebuffers(1, &FB);

	glGenTextures(MAX, Tex);
	glBindTexture(GL_TEXTURE_2D, Tex[Color0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RC.Render->GetWidth(), RC.Render->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenRenderbuffers(MAX, &RB);
	glBindRenderbuffer(GL_RENDERBUFFER, RB);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, RC.Render->GetWidth(), RC.Render->GetHeight());

	glGenFramebuffers(1, &FB);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FB);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Tex[Color0], 0);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RB);
}

void FRenderTarget::Bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FB);
}

bool FRenderTarget::Ready()
{
	Bind();
	GLenum ret = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	return ret == GL_FRAMEBUFFER_COMPLETE;
}

void FRenderTarget::BindPostprocessTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Tex[Color0]);
}

void FRenderTarget::BindDefault()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
C3_NAMESPACE_END
