#ifdef _WIN32
#pragma unmanaged
#endif

#include "shader_gl.hpp"
#include <GL/glew.h>
#include <debug_print.h>

#ifdef CUSTOM_MALLOC
#include <custom_memory++.h>
#endif

static const GLenum enumToGLShaderTypes[] = {GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER};
static const GLenum enumToGLShaderParams[] = {GL_SHADER_TYPE,GL_DELETE_STATUS,GL_COMPILE_STATUS,GL_INFO_LOG_LENGTH,GL_SHADER_SOURCE_LENGTH};
static const GLenum enumToGLBlockParams[] = {GL_UNIFORM_BLOCK_BINDING,GL_UNIFORM_BLOCK_DATA_SIZE,GL_UNIFORM_BLOCK_NAME_LENGTH,GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER,GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER};
static const GLenum enumToGLProgramParams[] = {GL_DELETE_STATUS, GL_LINK_STATUS, GL_VALIDATE_STATUS, GL_INFO_LOG_LENGTH, GL_ATTACHED_SHADERS, GL_ACTIVE_ATTRIBUTES, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, GL_ACTIVE_UNIFORMS, GL_ACTIVE_UNIFORM_BLOCKS, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, GL_ACTIVE_UNIFORM_MAX_LENGTH, GL_PROGRAM_BINARY_LENGTH, GL_TRANSFORM_FEEDBACK_BUFFER_MODE, GL_TRANSFORM_FEEDBACK_VARYINGS, GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, GL_GEOMETRY_VERTICES_OUT, GL_GEOMETRY_INPUT_TYPE, GL_GEOMETRY_OUTPUT_TYPE, GL_UNIFORM_OFFSET};
#define GetGLShaderType(A) enumToGLShaderTypes[A]

//---------------------------------
//	Shader Object
//---------------------------------
CShader::CShader(Type type, const char** pSrcArray, unsigned int n)
{	
	GLint compStatus = GL_FALSE;	
	m_type = type;
	m_compiled = false;
	m_handle = glCreateShader(GetGLShaderType(m_type));
	if(m_handle != 0 && n > 0)
	{
		//supply the source
		glShaderSource(m_handle, n, pSrcArray, NULL);
		//compile the shaders
		glCompileShader(m_handle);		
		glGetShaderiv(m_handle,GL_COMPILE_STATUS, &compStatus);		
		if(compStatus != GL_TRUE)
		{
			int len = Query(LOG_LENGTH);
			char* pLog = new char[len];
			GetLog(len, pLog);
			d_printf("Compile Program Error:\n");
			d_printf(pLog);			
			delete[] pLog;
		}
		else
			m_compiled = true;
	}	
}

CShader::~CShader()
{	
	//http://www.opengl.org/wiki/GLAPI/glDeleteShader
	glDeleteShader(m_handle);
}

void CShader::SetSource(const char** pSrcArray, unsigned int n)
{
	GLint compStatus = GL_FALSE;
	if(m_handle != 0 && n > 0)
	{
		//supply the source
		glShaderSource(m_handle, n, pSrcArray, NULL);
		//compile the shaders
		glCompileShader(m_handle);		
		glGetShaderiv(m_handle,GL_COMPILE_STATUS, &compStatus);		
		if(compStatus != GL_TRUE)
		{
			int len = Query(LOG_LENGTH);
			char* pLog = new char[len];
			GetLog(len, pLog);
			d_printf("Compile Program Error:\n");
			d_printf(pLog);			
			delete[] pLog;
		}
		else
			m_compiled = true;
	}
}

int CShader::Query(const Param param)const
{
	GLint params;
	glGetShaderiv(m_handle, enumToGLShaderParams[param], &params);
	return params;
}

void CShader::GetSource(unsigned int bufSize, char* buf)const
{
	GLsizei len;
	glGetShaderSource(m_handle, bufSize, &len, buf);
}

void CShader::GetLog(unsigned int bufSize, char* buf)const
{
	GLsizei len;
	glGetShaderInfoLog(m_handle, bufSize, &len, buf);
}

//-------------------------------------------------
// Program (linked set of shader objects
//-------------------------------------------------

CShaderProgram::CShaderProgram() : m_handle(INVALID_HANDLE), m_initialised(false), m_linked(0), m_validate(0)
{
	
}

CShaderProgram::~CShaderProgram()
{
	CleanUp();		
}

void CShaderProgram::CleanUp(void)
{
	//http://www.opengl.org/wiki/GLAPI/glDeleteProgram
	if (glIsProgram (m_handle))
		glDeleteProgram (m_handle);
}

void CShaderProgram::Initialise()
{
	CreateHandle();		
	m_initialised = true; //kind of redundant
}

CShaderProgram::Handle CShaderProgram::CreateHandle()
{
	if(!HasHandle())
		m_handle = glCreateProgram();
	return m_handle;
}

void CShaderProgram::AddShader(const CShader*  shader)
{
	if(m_handle != 0)
	{
		if(shader->Compiled())
			glAttachShader(m_handle,shader->GetHandle());
		else
		{	//should I just compile for them? seems trivial
			d_printf("compile shader before adding:\n");
		}
	}
}

void CShaderProgram::Link(void)
{
	//http://www.opengl.org/sdk/docs/man4/xhtml/glLinkProgram.xml
	glLinkProgram(m_handle);//try and link the program
	//glGetProgramiv(m_handle, GL_LINK_STATUS, &m_linked); //check linked status
	m_linked = GetProgramInfo(LINK_STATUS);
	if(m_linked != GL_TRUE)
	{
		GLchar error[2056];
		GLsizei length = 0;
		glGetProgramInfoLog(m_handle,2056, &length, error);
		d_printf("Link Program Error:\n");
		d_printf(error);
	}
	glValidateProgram(m_handle); //validate the program
	//glGetProgramiv (m_handle, GL_VALIDATE_STATUS, &m_validate); //check linked status
	m_validate = GetProgramInfo(VALIDATE_STATUS);
	if(m_validate != GL_TRUE)
	{
		GLchar error[2056];
		GLsizei length = 0;
		glGetProgramInfoLog(m_handle,2056,&length, error);
		d_printf("INVALID Program Error:\n");
		d_printf(error);
	}	
}

int CShaderProgram::GetProgramInfo(const Param param)
{
	if(!IsInitialised())
		return 0;

	int info = 0;		
	glGetProgramiv(m_handle,enumToGLProgramParams[param],&info);
	return info;
	
}

//before linking
//This seems to take precedence over anything set in the fragment shader via
//layout(location = n) 
bool CShaderProgram::SetMRTOutputLocation(const char* name, unsigned int mrtNo)
{
	glBindFragDataLocation(m_handle, mrtNo, name);
	return true;
}

int CShaderProgram::GetMRTOutputLocation(const char* name)
{
	return glGetFragDataLocation (m_handle, name);
}


void CShaderProgram::SetAttributeLocation(unsigned int attrNum, const char* name)
{
	glBindAttribLocation(m_handle, attrNum, name);
}

unsigned int CShaderProgram::GetAttributeLocation(const char* name)
{
	return glGetAttribLocation(m_handle, name);
}

void CShaderProgram::RecordOutput(const char** pOP, RecordMode rm)
{
	int mode;
	if(rm == INTERLEAVED){
		mode = GL_INTERLEAVED_ATTRIBS;
	}else{
		mode = GL_SEPARATE_ATTRIBS;
	}

	int count = 0;
	const char**pCnt = pOP;
	while(pCnt)
	{
		if(*pCnt == NULL)
			break;
		count++;
		pCnt++;
		//safety fallback
		if(count > 100)
			return;
	}
	glTransformFeedbackVaryings(m_handle, count, pOP, mode);
	Link();
}

int CShaderProgram::GetUniformLocation(const char* name)
{
	if(!IsInitialised() || !IsLinked())
		return INVALID_UNIFORM_HANDLE;
	return glGetUniformLocation(m_handle,name);
}

int CShaderProgram::GetUniformIndex(const char* name)
{
	if(!IsInitialised() || !IsLinked())
		return INVALID_UNIFORM_INDEX;

	unsigned int idx;
	glGetUniformIndices(m_handle, 1, &name, &idx);
	return int(idx);
}

int CShaderProgram::GetUniformInfo(const Param b,const int count, unsigned int const * const pIndices, int* const pOffsets)
{
	glGetActiveUniformsiv(m_handle, count, pIndices, enumToGLProgramParams[b], pOffsets );
	return 0;
}

int CShaderProgram::GetUniformNameByIndex(const int index, char* buffer, const unsigned int bufSize)
{
	int strLength = 0;
	glGetActiveUniformName(m_handle, unsigned int(index), bufSize, &strLength, buffer);
	return strLength;
}


int CShaderProgram::GetUniformBlockAlignment(void)
{
	int align = 0;
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,&align);
	return align;
}

int CShaderProgram::GetUniformBlockLocation(const char* name)
{
	if(!IsInitialised() || !IsLinked())
		return INVALID_UNIFORM_HANDLE;
	return glGetUniformBlockIndex(m_handle, name);	
}

void CShaderProgram::BindUniformBlock(const int loc, const int binding)
{
	glUniformBlockBinding(m_handle, loc, binding);
}

int CShaderProgram::GetUniformBlockBinding(const int loc)
{
	return GetUniformBlockInfo(loc, BINDING);	
}


int CShaderProgram::GetUniformBlockSize(const int loc)
{
	return GetUniformBlockInfo(loc, SIZE);	
}

int CShaderProgram::GetUniformBlockInfo(const int loc, const BlockParam param, int* pData)
{
	if(!IsInitialised() || !IsLinked())
		return 0;

	if(pData == NULL)
	{
		int size = 0;		
		glGetActiveUniformBlockiv(m_handle,loc,enumToGLBlockParams[param],&size);
		return size;
	}
	else
	{
		glGetActiveUniformBlockiv(m_handle,loc,enumToGLBlockParams[param],pData);
		return *pData;
	}
}

void CShaderProgram::Start(void) const
{
	glUseProgram(m_handle);	
}

void CShaderProgram::Stop()const
{
	//glUseProgram (0); //redundant? no default shader?
}

//--------------------------------------------
void CShaderProgram::SetBool(const char* name, const bool set)const
{
	glUniform1i(glGetUniformLocation(m_handle,name), set);
}

void CShaderProgram::SetTextureUnit(const char* name, const unsigned int texUnit)const
{
	glUniform1i(glGetUniformLocation(m_handle, name), texUnit);	
}

void CShaderProgram::SetFloat(const char* name, const float value)const
{
	glUniform1f(glGetUniformLocation(m_handle, name), value);	
}

void CShaderProgram::SetVec2(const char* name, const float* const vec)const
{
	glUniform2fv(glGetUniformLocation(m_handle, name), 1, vec);	
}

void CShaderProgram::SetVec3(const char* name, const float* const vec)const
{
	glUniform3fv(glGetUniformLocation(m_handle, name), 1, vec);		
}

void CShaderProgram::SetVec4(const char* name, const float* const vec)const
{
	glUniform4fv(glGetUniformLocation(m_handle, name), 1, vec);
}

void CShaderProgram::SetMtx33(const char* name, const float* const mtx)const
{
	glUniformMatrix3fv(glGetUniformLocation(m_handle, name), 1, GL_FALSE, mtx);		
}

void CShaderProgram::SetMtx44(const char* name, const float* const mtx)const
{
	glUniformMatrix4fv(glGetUniformLocation(m_handle, name), 1, GL_FALSE, mtx);		
}

void CShaderProgram::SetBool(int loc, const bool set)const
{
	glUniform1i(loc, set);
}

void CShaderProgram::SetTextureUnit(int loc, const unsigned int texUnit)const
{
	glUniform1i(loc, texUnit);	
}

void CShaderProgram::SetFloat(int loc, const float* value)const
{
	glUniform1f(loc, *value);	
}

void CShaderProgram::SetVec2(int loc, const float* const vec)const
{
	glUniform2fv(loc, 1, vec);	
}

void CShaderProgram::SetVec3(int loc, const float* const vec)const
{
	glUniform3fv(loc, 1, vec);		
}

void CShaderProgram::SetVec4(int loc, const float* const vec)const
{
	glUniform4fv(loc, 1, vec);
}

void CShaderProgram::SetMtx33(int loc, const float* const mtx)const
{
	glUniformMatrix3fv(loc, 1, GL_FALSE, mtx);		
}

void CShaderProgram::SetMtx44(int loc, const float* const mtx)const
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, mtx);		
}

/*
//-----------------------------------------------------------

bool CShaderProgramGL::SetTextureUnit(UniformHandle handle, const unsigned int& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;

#ifdef CHECK_WITH_OLD_VALUE
	//compare data here!
	if(m_attribute[handle].data.int1 == data)
		return true;

	m_attribute[handle].data.int1 = data;
	glUniform1i(m_attribute[handle].location, m_attribute[handle].data.int1);	
#else
	glUniform1i(m_attribute[handle].location, data);	
#endif
	return true;
}
bool CShaderProgramGL::SetBool(UniformHandle handle, const bool& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
	//if(m_attribute[handle].data.int1 == data)
	//	return true;
#ifdef CHECK_WITH_OLD_VALUE
	m_attribute[handle].data.int1 = data;
	glUniform1i(m_attribute[handle].location, m_attribute[handle].data.int1);	
#else
	glUniform1i(m_attribute[handle].location, data);		
#endif
	return true;
}
bool CShaderProgramGL::SetFloat(UniformHandle handle, const float& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
#ifdef CHECK_WITH_OLD_VALUE
	if(m_attribute[handle].data.float1 == data)
		return true;
	
	m_attribute[handle].data.float1 = data;
	glUniform1f(m_attribute[handle].location, m_attribute[handle].data.float1);	
#else
	glUniform1f(m_attribute[handle].location, data);	
#endif
	return true;
}
bool CShaderProgramGL::SetVec2(UniformHandle handle, const Vec2df& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
#ifdef CHECK_WITH_OLD_VALUE
	if(m_attribute[handle].data.float2== data)
		return true;

	m_attribute[handle].data.float2 = data;
	glUniform2fv(m_attribute[handle].location, 1, m_attribute[handle].data.float2.data);	
#else
	glUniform2fv(m_attribute[handle].location, 1, data.data);	
#endif
	return true;
}
bool CShaderProgramGL::SetVec3(UniformHandle handle, const Vec3df& data)
{

	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
#ifdef CHECK_WITH_OLD_VALUE
	if(m_attribute[handle].data.float3 == data)
		return true;

	m_attribute[handle].data.float3 = data;
	glUniform3fv(m_attribute[handle].location, 1, m_attribute[handle].data.float3.data);	
#else
	glUniform3fv(m_attribute[handle].location, 1, data.data);	
#endif
	return true;
}
bool CShaderProgramGL::SetVec4(UniformHandle handle, const Vec4df& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
#ifdef CHECK_WITH_OLD_VALUE
	if(m_attribute[handle].data.float4 == data)
		return true;

	m_attribute[handle].data.float4 = data;
	glUniform4fv(m_attribute[handle].location, 1, m_attribute[handle].data.float4.data);	
#else
	glUniform4fv(m_attribute[handle].location, 1, data.data);	
#endif
	return true;
}
bool CShaderProgramGL::SetMtx33(UniformHandle handle, const Matrix33& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
#ifdef CHECK_WITH_OLD_VALUE
	if(m_attribute[handle].data.float9 == data)
		return true;
	
	m_attribute[handle].data.float9 = data;
	glUniformMatrix3fv(m_attribute[handle].location, 1, GL_FALSE, m_attribute[handle].data.float9.data);
#else
	glUniformMatrix3fv(m_attribute[handle].location, 1, GL_FALSE, data.data);
#endif
	
	return true;
}

bool CShaderProgramGL::SetMtx44(UniformHandle handle, const Matrix44& data)
{
	if(handle == INVALID_UNIFORM_HANDLE)
		return false;
	//compare data here!
#ifdef CHECK_WITH_OLD_VALUE
	if(m_attribute[handle].data.float16 == data)
		return true;
	m_attribute[handle].data.float16 = data;
	glUniformMatrix4fv(m_attribute[handle].location, 1, GL_FALSE, m_attribute[handle].data.float16.data);
#else
	glUniformMatrix4fv(m_attribute[handle].location, 1, GL_FALSE, data.data);
#endif
	return true;
}

CShaderProgramGL::CShaderProgramGL() : m_numAttributes(0)
{
	
}

void CShaderProgramGL::Cleanup(void)
{
	if (glIsProgram (m_handle))
		glDeleteProgram (m_handle);
    
	m_handle = INVALID_HANDLE;
}

CShaderProgramGL::~CShaderProgramGL()
{
	
}
*/

