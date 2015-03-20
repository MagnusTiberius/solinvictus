#ifndef WINDOW_GL_H_
#define WINDOW_GL_H_

extern int DefineAndSetPixelFormat(PIXELFORMATDESCRIPTOR* pfd, HDC hdc, const int clrBits, const int dphBits, const int stnBits);
extern HGLRC CreateOpenGLContext(HDC hdc, const unsigned int mjr, const unsigned int mnr);
extern int GetMultisampledFormat(HDC hdc, const CPlatform::MultiSample ms, const int clrBits, const int dphBits, const int stnBits);

#endif// WINDOW_GL_H_