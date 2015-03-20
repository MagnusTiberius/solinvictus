#ifdef _WIN32
#pragma unmanaged
#endif

#include "matrix_stack.h"

CMatrixStack::CMatrixStack(unsigned int size)
{
	m_pStack = 0;
	m_index = 0;
	m_size = 0;	
	m_granularity = size;
}

CMatrixStack::~CMatrixStack()
{
	if(m_pStack)
		delete [] m_pStack;
}

/*
TODO
COPY OLD DATA BEFORE RESIZING
*/
void CMatrixStack::Resize(unsigned int size)
{
	if(m_pStack)
		delete [] m_pStack;	

	m_size = size;
	if (size > 0){
		m_pStack = new CMatrix44[m_size];
		m_pStack[0].Identity();
	}
	else
		m_pStack = 0;
}

void CMatrixStack::Push(void)
{
	if(m_index+1 >= m_size || m_pStack == 0){
		Resize(m_size + m_granularity);
	}
	if(m_index+1 < m_size){
		m_pStack[ m_index+1 ] = m_pStack[ m_index ];
		m_index++;
	}
}

void CMatrixStack::Pop(void)
{
	if(m_index > 0)
		m_index -= 1;
}

CMatrix44* CMatrixStack::TopOfStack(void)
{
	if(m_pStack == 0){
		Resize(m_size + m_granularity);
	}

	return &m_pStack[m_index];
}

