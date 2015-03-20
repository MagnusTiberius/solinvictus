#ifndef _SHADER_GL_HPP_
#define _SHADER_GL_HPP_

/**
CShader
shader object
*/
class CShader
{
public:
	typedef unsigned int Handle;
	static const Handle INVALID_HANDLE = 0;
	enum Type
	{
		VERT = 0,
		CTRL,
		EVAL,
		GEOM,
		FRAG,		
		INVALID = -1,
	};
	enum Param
	{
		TYPE,
		DELETE_STATUS,
		COMPILE_STATUS,
		LOG_LENGTH,
		SOURCE_LENGTH
	};
protected:
	Type			m_type;
	unsigned int	m_handle;
	bool			m_compiled;
public:
	CShader(Type type, const char** pSrcArray, unsigned int n);	
	virtual ~CShader();	
	//accessors
	void SetSource(const char** pSrcArray, unsigned int n);
	bool Compiled()const{return m_compiled;}
	Type GetShaderType(void)const{return m_type;}
	const Handle GetHandle(void) const { return m_handle; }
	int Query(const Param param)const;
	void GetSource(unsigned int bufSize, char* buf)const;
	void GetLog(unsigned int bufSize, char* buf)const;
};

//
//	CShaderProgram
//	 shader program (usually vertex/fragment pair) 
//
class CShaderProgram
{
public:
	typedef unsigned int Handle;
	static const Handle INVALID_HANDLE = 0;
	typedef int UniformHandle;	
	static const UniformHandle INVALID_UNIFORM_HANDLE = -1;
	static const int INVALID_UNIFORM_INDEX = -1;

	enum UniformType
	{
		BOOL,
		TEXTURE,
		INT,
		INT_2,
		INT_3,
		INT_4,
		FLOAT,
		FLOAT_2,
		FLOAT_3,
		FLOAT_4,
		FLOAT_9,
		FLOAT_16
	};

	enum Param
	{
		DELETE_STATUS, 
		LINK_STATUS, 
		VALIDATE_STATUS, 
		INFO_LOG_LENGTH, 
		ATTACHED_SHADERS, 
		ACTIVE_ATTRIBUTES, 
		ACTIVE_ATTRIBUTE_MAX_LENGTH, 
		ACTIVE_UNIFORMS, 
		ACTIVE_UNIFORM_BLOCKS, 
		ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, 
		ACTIVE_UNIFORM_MAX_LENGTH, 
		PROGRAM_BINARY_LENGTH, 
		TRANSFORM_FEEDBACK_BUFFER_MODE, 
		TRANSFORM_FEEDBACK_VARYINGS, 
		TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, 
		GEOMETRY_VERTICES_OUT, 
		GEOMETRY_INPUT_TYPE, 
		GEOMETRY_OUTPUT_TYPE,
		UNIFORM_OFFSET
	};

	enum BlockParam
	{
		BINDING=0,
		SIZE,
		NAME_LENGTH,
		BLK_ACTIVE_UNIFORMS,
		BLK_ACTIVE_UNIFORMS_INDICES,
		REFERENCED_BY_VERT_SHADER,
		REFERENCED_BY_FRAG_SHADER,
		REFERENCED_BY_GEOM_SHADER
	};

	enum RecordMode
	{
		INTERLEAVED,
		SEPARATE			
	};

protected:
	bool	m_initialised;
	int		m_linked;
	int		m_validate;
	Handle	m_handle;
	Handle	CreateHandle(void);
public:		
	CShaderProgram();
	CShaderProgram(const CShaderProgram*);
	virtual ~CShaderProgram();

	void Initialise(void);
	void AddShader(const CShader*  pShader);
	void RecordOutput(const char**, RecordMode);
	void Link(void);
	int GetProgramInfo(const Param);

	bool SetMRTOutputLocation(const char* name, unsigned int mrtNo);
	int GetMRTOutputLocation(const char* name);
	void SetAttributeLocation(unsigned int attrNum, const char* name);
	unsigned int GetAttributeLocation(const char* name);

	int GetUniformLocation(const char*);
	int GetUniformIndex(const char*);
	int GetUniformNameByIndex(const int, char*, const unsigned int);
	int GetUniformInfo(const Param b,const int count, unsigned int const * const pIndices, int * const pOffsets);
		//GetUniformInfo(const Param b,const int count, unsigned int const * const pIndices, int* const pOffsets)

	static int GetUniformBlockAlignment(void);
	int GetUniformBlockLocation(const char*);
	void BindUniformBlock(const int, const int);
	int GetUniformBlockBinding(const int);
	int GetUniformBlockSize(const int);
	int GetUniformBlockInfo(const int , const BlockParam , int* pData = 0);

	void Start(void)const;
	void Stop(void)const;
	void CleanUp(void);

	inline Handle GetHandle(void)const{return m_handle;}
	bool IsInitialised(void)const{return m_initialised;}
	bool IsLinked(void)const{return m_linked==1;}
	bool HasHandle(void)const{return (m_handle != INVALID_HANDLE);}

	//Remember that only active shaders can have their uniforms changed
	//call start before trying to change any of these
	// (maybe add a debug mode that checks the currently bound program
	//  against this' one)
	//Set constant/uniform variables
	void SetTextureUnit(const char*, const unsigned int)const;
	void SetBool(const char*, const bool)const;
	void SetFloat(const char* varName, const float)const;
	void SetVec2(const char* varName, const float* const)const;
	void SetVec3(const char* varName, const float* const)const;
	void SetVec4(const char* varName, const float* const)const;
	void SetMtx33(const char* varName, const float* const)const;
	void SetMtx44(const char* varName, const float* const)const;

	//already have the location
	void SetTextureUnit(int, const unsigned int)const;
	void SetBool(int, const bool)const;
	void SetFloat(int varName, const float* const value)const;
	void SetVec2(int varName, const float* const)const;
	void SetVec3(int varName, const float* const)const;
	void SetVec4(int varName, const float* const)const;
	void SetMtx33(int varName, const float* const)const;
	void SetMtx44(int varName, const float* const)const;	
};
/*
//
//	CShaderManager
//	 Interface for creating shaders	 
//
class CShaderManager
{
public:
typedef int Handle;	
static const Handle INVALID_HANDLE = -1;

protected:
bool			m_initialised;
void	CreateHandle() {};
public:

CShaderManager();
~CShaderManager();

void		Initialise(const char * common, const char * vert, const char * frag){};		
Handle		CreateShaderProgram(void)=0;
bool				IsInitialised(void){return m_initialised;}

//virtual members
void InitialiseShaderProgram(Handle program, const char * vert_src, const char * geo_src, const char * frag_src)=0;	

CShaderProgram::Handle GetShaderProgramHandle(const Handle)=0;
CShaderProgram& GetShaderProgram(const Handle)=0;
CShaderProgram::UniformHandle CreateUniformHandle(const char* , CShaderProgram::UniformType)=0;

void SetActiveShader(Handle)=0;
Handle GetActiveShader(void)const=0;
void StopShading(void)=0;	

bool SetTextureUnit(const CShaderProgram::UniformHandle&, const unsigned int&)=0;
bool SetBool(const CShaderProgram::UniformHandle&, const bool&)=0;
bool SetFloat(const CShaderProgram::UniformHandle&, const float&)=0;
bool SetVec2(const CShaderProgram::UniformHandle&, const Vec2df&)=0;	
bool SetVec3(const CShaderProgram::UniformHandle&, const Vec3df&)=0;	
bool SetVec4(const CShaderProgram::UniformHandle&, const Vec4df&)=0;
bool SetMtx33(const CShaderProgram::UniformHandle&, const Matrix33&)=0;
bool SetMtx44(const CShaderProgram::UniformHandle&, const Matrix44&)=0;	
};

*/
#endif _SHADER_GL_H_