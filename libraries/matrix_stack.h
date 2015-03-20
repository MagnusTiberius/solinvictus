#ifdef _WIN32
#pragma unmanaged
#endif

#ifndef _MATRIX_STACK_H_
#define _MATRIX_STACK_H_

#include "vector++/vector++/matrix44++.h"
#include "vector++/vector++/matrix33++.h"

class CMatrixStack
{
private:
	unsigned int	m_index;
	unsigned int	m_granularity;
	unsigned int	m_size;
	CMatrix44*		m_pStack;
public:
	CMatrixStack(unsigned int size = 0);
	virtual ~CMatrixStack();
	void Resize(unsigned int size);

	void Push(void);
	void Pop(void); 
	CMatrix44* TopOfStack(void);
};

#endif _MATRIX_STACK_H_