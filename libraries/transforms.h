#ifdef _WIN32
#pragma unmanaged
#endif
#include "matrix_stack.h"

#ifndef _TRANSFORMS_H_
#define _TRANSFORMS_H_

class Transform
{
private:
	CMatrixStack m_transformStack;
public:
	Transform(unsigned int depth);
	Transform(void);
	virtual ~Transform();
	void ResizeStack(unsigned int depth);

	void Push();
	void Pop();
	CMatrix44 GetCurrentMatrix();
	
	void Identity(void);
	void Translate(const float x,const float y,const float z);
	void Translate(const Vec3df& vec);
	void Scale(const float x,const float y,const float z);
	void ApplyTransform(const CMatrix44& mtx);	
	
	static void CreateProjectionMatrix(Matrix44& mat, float l,float r,float b,float t,float n,float f);
	static void CreateInverseProjectionMatrix(Matrix44& mat, float l,float r,float b,float t,float n,float f);
	static void CreateOrthoMatrix(Matrix44& mat, float l,float r,float b,float t,float n,float f);
};

#endif //_TRANSFORMS_H_