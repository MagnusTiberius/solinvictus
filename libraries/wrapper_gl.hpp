#ifndef _WRENDER_HPP_
#define _WRENDER_HPP_

#include <string>

namespace WRender
{
enum Cull
{
	FRONT_FACE,
	BACK_FACE,
};

typedef unsigned int Mask;
#define COLOR_BIT 0x1
#define DEPTH_BIT 0x2
#define STENCIL_BIT 0x4

//BUFFER_ACCESS
#define BUF_READ		0x01
#define BUF_WRITE		0x02
#define BUF_INVALIDATE	0x04
#define BUF_FLUSH		0x08
#define BUF_UNSYNC		0x10


enum Buffer //Graphics Buffer?
{
	ELEMENTS=0, //check indices against glBuffers in the cpp file :)
	ARRAY,
	TEXTURE,
	FEEDBACK,
	UNIFORM
};

//should probably also check the 
//STEAM and COPY variables
//see how much they change performance
enum BufferUse //Graphics Buffer?
{
	STATIC=0, //check indices against glBuffers in the cpp file :)
	DYNAMIC
};

enum SteamType
{
	CHAR = 0,
	UCHAR,
	SHORT,
	INT,
	FLOAT
};

struct VertexAttribute
{
	unsigned int	vbo;	// if 0 use the currently bound VBO
	unsigned int	idx;	// could probably be a char?

	unsigned int	size;	// usually 3 or 4
	SteamType		type;	//also a char?
	unsigned int	normalized; //0 false, 1 true //could be a char?
	unsigned int	stride;		
	unsigned int	offset;
	unsigned int	divisor; //for instancing
	void Set(unsigned int	vbo, unsigned int	idx, unsigned int	size, 
			SteamType	type, unsigned int	normalized,	unsigned int stride, 
			unsigned int offset , unsigned int	divisor)
	{
		this->vbo = vbo;
		this->idx = idx;
		this->size = size;
		this->type = type;
		this->normalized = normalized;
		this->stride = stride;
		this->offset = offset;
		this->divisor = divisor;
	}
};

enum DrawMode
{
	POINTS = 0,
	TRIANGLES,
	TRIANGLE_STRIP,
	LINES,
	LINESTRIP
};

enum ElementType
{
	U_BYTE = 0,
	U_SHORT,
	U_INT
};
/*
enum AttachmentType
{
	RBO_CLR,
	TEX_CLR,
	RBO_DEPTH,
	TEX_DEPTH,
};*/

namespace Texture
{
	enum Type
	{
		//Order is Important
		TEX_1D = 0, 
		TEX_1D_ARRAY, 
		TEX_2D, 
		TEX_2D_ARRAY, 
		TEX_2D_MULTISAMPLE,
		TEX_2D_MULTISAMPLE_ARRAY,
		TEX_RECTANGLE, 
		TEX_CUBE_MAP,
		TEX_CUBE_MAP_POSITIVE_X,
		TEX_CUBE_MAP_POSITIVE_Y,
		TEX_CUBE_MAP_POSITIVE_Z,
		TEX_CUBE_MAP_NEGATIVE_X,
		TEX_CUBE_MAP_NEGATIVE_Y,
		TEX_CUBE_MAP_NEGATIVE_Z,
		TEX_3D,
		TEX_BUFFER,
	};
	#define IS_1D_TEX(TYP) ((TYP<=Texture::TEX_1D_ARRAY)? true: false)
	#define IS_2D_TEX(TYP) ((TYP>=Texture::TEX_2D && TYP<Texture::TEX_CUBE_MAP)? true: false)
	#define IS_CUBE_TEX(TYP) ((TYP>=Texture::TEX_CUBE_MAP && TYP<Texture::TEX_3D)? true: false)
	#define IS_3D_TEX(TYP) ((TYP==Texture::TEX_3D)? true: false)
	#define IS_TEX_BUFFER(TYP) ((TYP==Texture::TEX_BUFFER)? true: false)

	//http://www.opengl.org/wiki/Image_Format#Texture_and_Renderbuffer
	enum Format
	{
		//Order is important
		DEPTH_COMPONENT=0,
		DEPTH_COMPONENT16, 
		DEPTH_COMPONENT24, 
		DEPTH_COMPONENT32, 
		DEPTH_COMPONENT32F,
		DEPTH_STENCIL,
		DEPTH24_STENCIL8, 
		DEPTH32F_STENCIL8,
		//
		RGBA8, RG8, R8,
		RGBA16, RG16, R16,
		RGBA16F, RG16F, R16F,
		RGBA32F, RG32F, R32F,
		RGBA8I, RG8I, R8I,
		RGBA16I, RG16I, R16I,
		RGBA32I, RG32I, R32I,
		RGBA8UI, RG8UI, R8UI,
		RGBA16UI, RG16UI, R16UI,
		RGBA32UI, RG32UI, R32UI,
		RGB10_A2,R11F_G11F_B10F,SRGB8_ALPHA8,

		//TEX ONLY FORMATS (maybe can't be used in RBO)
		RGB8, RGB16,  
		RGBA8_SNORM, RG8_SNORM, R8_SNORM,
		RGBA16_SNORM, RGB16_SNORM, RG16_SNORM, R16_SNORM,
		RGB16F, RGB32F,
		RGB8I, RGB16I, RGB32I,
		RGB8UI, RGB16UI, RGB32UI,
	};
	#define IS_DEPTH_TEXTURE(FMT) (FMT<Texture::DEPTH_STENCIL)? true: false
	#define IS_COLOR_TEXTURE(FMT) (FMT>=Texture::RGBA8)? true: false
	#define IS_DEPTH_STENCIL_TEXTURE(FMT) (FMT>=Texture::DEPTH_STENCIL && FMT<=Texture::DEPTH32F_STENCIL8)? true: false
	//#define IS_STENCIL_TEXTURE(FMT) (FMT<=Texture::DEPTH32F_STENCIL8)? true: false

	enum Unit
	{
		UNIT_0 = 0,
		UNIT_1,
		UNIT_2,
		UNIT_3,
		UNIT_4,
		UNIT_5,
		UNIT_6,
		UNIT_7,
		UNIT_8,
		UNIT_9,
		UNIT_10,
		UNIT_11,
		UNIT_12,
		UNIT_13,
		UNIT_14,
		UNIT_15,
		UNIT_MAX = UNIT_15,
		UNIT_INVALID = -1
	};

	enum ParamName
	{
		BASE_LEVEL = 0, 
		BORDER_COLOR, 
		COMPARE_FUNC, 
		COMPARE_MODE, 
		LOD_BIAS, 
		MIN_FILTER, 
		MAG_FILTER, 
		MIN_LOD, 
		MAX_LOD, 
		MAX_LEVEL, 
		SWIZZLE_R, 
		SWIZZLE_G, 
		SWIZZLE_B, 
		SWIZZLE_A, 
		SWIZZLE_RGBA, 
		WRAP_S, 
		WRAP_T, 
		WRAP_R
	};

	//http://www.opengl.org/sdk/docs/man4/xhtml/glTexParameter.xml
	//http://www.opengl.org/wiki/Texture#Filtering
	enum Param
	{
		//for COMPARE_FUNC
		LEQUAL = 0,
		GEQUAL,
		LESS,
		GREATER,
		EQUAL,
		NOTEQUAL,
		ALWAYS,	
		NEVER,
		//for COMPARE_MODE
		COMPARE_REF_TO_TEXTURE,
		NONE,
		// for MIN_FILTER
		NEAREST,	//also for MAG_FILTER
		LINEAR,		//also for MAG_FILTER
		NEAREST_MIPMAP_NEAREST, // for mipmap stuff see link to filtering
		LINEAR_MIPMAP_NEAREST, //bilinear
		NEAREST_MIPMAP_LINEAR, //bilinear between mipmap levels
		LINEAR_MIPMAP_LINEAR, //trilinear
		//for the SWIZZLE_*
		RED, 
		GREEN, 
		BLUE, 
		ALPHA, 
		ZERO,
		//FOR WRAP_*
		CLAMP_TO_EDGE, 
		CLAMP_TO_BORDER, 
		MIRRORED_REPEAT, 
		REPEAT
	};

	enum Mipmap
	{
		GEN_MIPMAP,
		DONT_GEN_MIPMAP
	};

	struct SDescriptor
	{
		Type			type;
		Format			fmt;
		unsigned int	w, h, d;
		unsigned int	nSamples;
		Mipmap			genMipMap;
	};

	struct SObject
	{
		unsigned int	handle; //0 = invalid 
		SDescriptor		descriptor;
	};

	struct SParam
	{
		ParamName	name;
		Param		param;
		//float		data;
	};
}

/*
Pixel data sent to OpenGL "server"

*/
namespace Pixel
{
	//http://www.opengl.org/wiki/GLAPI/glTexImage2D#Description
	//see "format"

	enum Format
	{
		 RED = 0, 
		 RG, 
		 RGB, 
		 BGR, 
		 RGBA,
		 BGRA,
		 DEPTH_COMPONENT,
		 DEPTH_STENCIL
	};

	enum Type
	{
		UCHAR = 0, 
		CHAR, 
		USHORT, 
		SHORT, 
		UINT, 
		INT,
		HALF_FLOAT,
		FLOAT, 
		UBYTE_3_3_2, 
		UBYTE_2_3_3_REV, 
		USHORT_5_6_5, 
		USHORT_5_6_5_REV, 
		USHORT_4_4_4_4, 
		USHORT_4_4_4_4_REV, 
		USHORT_5_5_5_1, 
		USHORT_1_5_5_5_REV, 
		UINT_8_8_8_8, 
		UINT_8_8_8_8_REV, 
		UINT_10_10_10_2,
		UINT_2_10_10_10_REV,
		UINT_24_8,
		UINT_32_8,
	};

	struct Data
	{
		Format	fmt;
		Type	type;
		int		level;
		void*	pData;
	};

}

/*
part of a framebuffer

*/
namespace RenderBuffer //changes here must be reflected int enumToGLTextureFormats
{
	//http://www.opengl.org/wiki/Image_Format#Texture_and_Renderbuffer
	enum Format
	{
		//Order Is Important
		DEPTH_COMPONENT=0,
		DEPTH_COMPONENT16, 
		DEPTH_COMPONENT24, 
		DEPTH_COMPONENT32, 
		DEPTH_COMPONENT32F,
		DEPTH_STENCIL,
		DEPTH24_STENCIL8, 
		DEPTH32F_STENCIL8,

		RGBA8, RG8, R8,
		RGBA16, RG16, R16,
		RGBA16F, RG16F, R16F,
		RGBA32F, RG32F, R32F,
		RGBA8I, RG8I, R8I,
		RGBA16I, RG16I, R16I,
		RGBA32I, RG32I, R32I,
		RGBA8UI, RG8UI, R8UI,
		RGBA16UI, RG16UI, R16UI,
		RGBA32UI, RG32UI, R32UI,
		RGB10_A2,R11F_G11F_B10F,SRGB8_ALPHA8
	};

	#define IS_DEPTH_RENDERBUFFER(FMT) (FMT<RenderBuffer::DEPTH24_STENCIL8)? true: false
	#define IS_COLOR_RENDERBUFFER(FMT) (FMT>=RenderBuffer::RGBA8)? true: false
	//#define IS_STENCIL_TEXTURE(FMT) (FMT<=RenderBuffer::DEPTH32F_STENCIL8)? true: false
	#define IS_DEPTH_STENCIL_RENDERBUFFER(FMT) (FMT==RenderBuffer::DEPTH24_STENCIL8 || FMT==RenderBuffer::DEPTH32F_STENCIL8)? true: false

	struct SDescriptor
	{
		Format			fmt;
		unsigned int	w, h;
		unsigned int	nSamples;		
	};

	struct SObject
	{
		unsigned int	handle;
		SDescriptor		descriptor;
	};
}

enum AttachmentTarget
{
	ATT_CLR0 = 0,
	ATT_CLR1,
	ATT_CLR2,
	ATT_CLR3,
	ATT_CLR4,
	ATT_CLR5,
	ATT_CLR6,
	ATT_CLR7,
	ATT_DEPTH,
	ATT_STENCIL,
	ATT_DEPTH_AND_STENCIL,
	ATT_MAX,
	ATT_CLR_MAX = ATT_CLR7
};

struct SAttachment
{
	enum
	{
		RenderBuffer,
		Texture
	} type;
	bool active;
	union
	{
		RenderBuffer::SObject r;
		Texture::SObject t;
	};
};

/*

*/
namespace FrameBuffer
{
	enum Type
	{
		DRAW = 0,
		READ,
		BOTH
	};

	enum BlitFilter
	{
		NEAREST=0,
		LINEAR
	};

	struct SObject
	{
		//static const int MAX_ATTACH = 8; //BAD, get this from GL_MAX_DRAW_BUFFERS instead
		bool			initialised;
		unsigned int	handle;		//frame buffer object handle		
		SAttachment		attachment[ATT_CLR_MAX+1];
		SAttachment		depth_attachment;
		SAttachment		stencil_attachment;
		SAttachment		depth_stencil_attachment;
	};
}

/*
SRC is what it is fragment
DST is whats's in frame buffer
*/
namespace Blend{
	enum Func{
		ADD,
		SUBTRACT,
		REVERSE_SUBTRACT,
		MIN,
		MAX
	};

	enum Param{
		ZERO,
		ONE,
		SRC_COLOR,
		ONE_MINUS_SRC_COLOR,
		DST_COLOR,
		ONE_MINUS_DST_COLOR,
		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA,
		DST_ALPHA,
		ONE_MINUS_DST_ALPHA,
		CONSTANT_COLOR,
		ONE_MINUS_CONSTANT_COLOR,
		CONSTANT_ALPHA,
		ONE_MINUS_CONSTANT_ALPHA,
		SRC_ALPHA_SATURATE,
		SRC1_COLOR,
		ONE_MINUS_SRC1_COLOR,
		SRC1_ALPHA,
		ONE_MINUS_SRC1_ALPHA,
	};
}

enum DepthFunc
{
	NEVER,
	LESS,
	EQUAL,
	LEQUAL,
	GREATER,
	NOTEQUAL,
	GEQUAL,
	ALWAYS
};

enum DrawBuffer
{
	DB_NONE = 0,
	DB_FRONT_LEFT,	
	DB_FRONT_RIGHT,
	DB_BACK_LEFT,	
	DB_BACK_RIGHT,
	DB_FRONT,
	DB_BACK,
	DB_LEFT,
	DB_RIGHT,
	DB_FRONT_AND_BACK,
};

enum DrawBuffers
{
	DBS_NONE = 0,
	DBS_FRONT_LEFT,
	DBS_FRONT_RIGHT,
	DBS_BACK_LEFT,
	DBS_BACK_RIGHT,
	DBS_CLR_ATT_0,
	DBS_CLR_ATT_1,
	DBS_CLR_ATT_2,
	DBS_CLR_ATT_3,
	DBS_CLR_ATT_4,
	DBS_CLR_ATT_5,
	DBS_CLR_ATT_6,
	DBS_CLR_ATT_7
};

//-------------------------------------------------
// Textures
//-------------------------------------------------
void ActiveTexture(Texture::Unit);
void BindTexture(Texture::SObject tx);
void BindTexture(Texture::SObject tx, Texture::Unit);
void CopyFrameRGBToTexture(unsigned int, unsigned int);
void CopyFrameDepthToTexture(unsigned int, unsigned int);

bool CreateBaseTexture(Texture::SObject&, const Texture::SDescriptor&);
bool CreateBaseTextureData(Texture::SObject&, const Texture::SDescriptor&, Pixel::Data& data);
bool CreateTextureData(Texture::SObject&, const Texture::SDescriptor&, const Pixel::Data& data);
void GenerateTextureMipMap(Texture::SObject&);
void UpdateTextureData(const Texture::SObject&, const Pixel::Data& data);
void SetTextureParams(const Texture::SObject&, Texture::SParam* param, unsigned int count);
void AttachTextureToBuffer(const Texture::SObject&, const unsigned int& bufID, const Texture::Format&);
void DeleteTexture(Texture::SObject);

//-------------------------------------------------
// Vertex Array Objetcs
//-------------------------------------------------
unsigned int	CreateVertexArrayObject(void);
void			DeleteVertexArrayObject(unsigned int);
void			BindVertexArrayObject(unsigned int);
void			UnbindVertexArrayObject(void); //needed?
void			SetAttributeFormat( const VertexAttribute* pAttr, unsigned int numAttr, unsigned int v_offset);

//-------------------------------------------------
// Transform Feedback objects
//-------------------------------------------------
unsigned int	CreateTransformFeedback( void );
void			DeleteTransformFeedback( unsigned int );
void			BindTransformFeedback(const unsigned int );
void			UnbindTransformFeedback(void);
void			DrawTransformFeedback(const DrawMode mode, const unsigned int xbo);

//-------------------------------------------------
// BUFFERS
//-------------------------------------------------
//create/destroy various buffers
unsigned int 	CreateBuffer(Buffer type);	
unsigned int 	CreateBuffer(Buffer type, BufferUse, unsigned int size, const void* pData);
void 			DeleteBuffer(unsigned int bufferID);

void			BindBuffer(Buffer type, unsigned int);
unsigned int	GetCurrentBuffer(Buffer type);
void*			MapBuffer(Buffer type, int id, int offset, int size, int access);
void*			MapBoundBuffer(Buffer type, int offset, int size, int access);	
void			UnmapBuffer(Buffer type);	
void			UnbindBuffer(Buffer type);	

void			BindBufferToIndex(Buffer type, unsigned int id, unsigned int idx);

void			InitBuffer(Buffer type, BufferUse, unsigned int id, unsigned int size, const void* pData);
void			UpdateBuffer(Buffer type, BufferUse, unsigned int id, unsigned int size, const void * pData, unsigned int offset);
void		 	UpdateBoundBuffer(Buffer type, BufferUse, unsigned int size, const void * pData, unsigned int offset);

void			FillArrayBufferFromFrameBuffer(unsigned int id, int x, int y, int w, int h,  Pixel::Format);
void			FillTextureFromArrayBuffer(unsigned int id, unsigned int texID, int x, int y, int w, int h,  Pixel::Format);

//-------------------------------------------------
// Drawing
//-------------------------------------------------
void Draw(const DrawMode mode, const ElementType elm, const unsigned int nIndices, const unsigned int i_offset);
void DrawArray(const DrawMode mode, const unsigned int count, const unsigned int offset);
void DrawInstanced(const DrawMode mode, const ElementType elm, const unsigned int nIndices, const unsigned int i_offset, unsigned int n);
void DrawArrayInstanced(const DrawMode mode, const unsigned int count, const unsigned int offset, const unsigned int n);

//-------------------------------------------------
// Transform Feedback
//-------------------------------------------------
void BeginTransformFeedback( DrawMode mode );
void EndTransformFeedback( void );

//-------------------------------------------------
// Frame Buffers
//-------------------------------------------------
void CreateFrameBuffer(FrameBuffer::SObject& fbo);
void DeleteFrameBuffer(FrameBuffer::SObject& fbo);
void CreateRenderBuffer(RenderBuffer::SObject& rbo, const RenderBuffer::SDescriptor& desc);
void DeleteRenderBuffer(RenderBuffer::SObject& rbo);
void AddRenderBuffer(FrameBuffer::SObject& fbo, const RenderBuffer::SObject& rbo, const AttachmentTarget idx);
void AddTextureRenderBuffer(FrameBuffer::SObject& fbo, const Texture::SObject& to, const AttachmentTarget idx, int mipmaplevel);
void InactivateColorAttachment(FrameBuffer::SObject& fbo, AttachmentTarget idx);
void RemoveColorAttachment(FrameBuffer::SObject& fbo, AttachmentTarget idx);
void RemoveDepthAttachment(FrameBuffer::SObject& fbo);
void RemoveStencilAttachment(FrameBuffer::SObject& fbo);
void RemoveDepthStencilAttachment(FrameBuffer::SObject& fbo);

void CheckFrameBuffer(FrameBuffer::SObject& fbo);
void BindFrameBuffer(const FrameBuffer::Type type, const FrameBuffer::SObject& fbo);
void UnbindFrameBuffer(const FrameBuffer::Type type);
void BlitFrameBuffer(int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH, Mask mask, FrameBuffer::BlitFilter filter);
unsigned int GetMaxFrameBuffers(void);

void SetDrawBuffer(const DrawBuffer);
void SetDrawBuffers(const unsigned int n, const DrawBuffers * const);

//-------------------------------------------------	
void ClearScreenBuffer(Mask mask);
void SetupViewport(unsigned int startX, unsigned int startY, unsigned int width, unsigned int height);
void UseScissor(bool );
void SetupScissor(unsigned int startX, unsigned int startY, unsigned int width, unsigned int height);

//-------------------------------------------------
//Blend Functinons
void EnableBlend(const bool enable);
void SetBlendEquations(const Blend::Func clr, const Blend::Func alpha);
void SetBlendParams(const Blend::Param src_clr, const Blend::Param dst_clr, const Blend::Param src_alpha, const Blend::Param dst_alpha);

//-------------------------------------------------
//various render modes
void Flush(void);
void Finish(void);

//OpenGL's default front face is CCW
void EnableCulling(bool);
void CullMode(const Cull&);	
void SetClearColour(const float r, const float g, const float b, const float a);

void EnableDepthTest(const bool);
void EnableDepthWriting(const bool);
void SetDepthFunction(const DepthFunc);
}

#endif _WRENDER_HPP_