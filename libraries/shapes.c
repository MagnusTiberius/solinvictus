#include <math.h>
#include "shapes.h"

typedef struct
{
	float x,y,z;
}XYZ;

typedef struct
{
	XYZ p1, p2, p3;
}FACET3;

static void Normalise(XYZ*const p)
{
	float mag = (float)sqrt((p->x*p->x)+(p->y*p->y)+(p->z*p->z));
	if(mag>0)
	{
		p->x = p->x / mag;
		p->y = p->y / mag;
		p->z = p->z / mag;
	}
}


unsigned int GetCubeSize(void){
	return 36;
}
void CreateCube(float* pf){
	float pos[8][3] = {
		{-1.0f,	-1.0f,  1.0f},
		{-1.0f,	 1.0f,  1.0f},
		{ 1.0f,	 1.0f,  1.0f},
		{ 1.0f,	-1.0f,  1.0f},

		{-1.0f,	-1.0f, -1.0f},
		{-1.0f,	 1.0f, -1.0f},
		{ 1.0f,	 1.0f, -1.0f},
		{ 1.0f,	-1.0f, -1.0f},
	};
	//front face +z
	*pf++ = pos[0][0];	*pf++ = pos[0][1];	*pf++ = pos[0][2];
	*pf++ = pos[2][0];	*pf++ = pos[2][1];	*pf++ = pos[2][2];
	*pf++ = pos[1][0];	*pf++ = pos[1][1];	*pf++ = pos[1][2];

	*pf++ = pos[2][0];	*pf++ = pos[2][1];	*pf++ = pos[2][2];
	*pf++ = pos[0][0];	*pf++ = pos[0][1];	*pf++ = pos[0][2];
	*pf++ = pos[3][0];	*pf++ = pos[3][1];	*pf++ = pos[3][2];

	//left face -x
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = pos[4+1][0];	*pf++ = pos[4+1][1];	*pf++ = pos[4+1][2];

	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = pos[0][0];		*pf++ = pos[0][1];		*pf++ = pos[0][2];

	//back face -z
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = pos[4+1][0];	*pf++ = pos[4+1][1];	*pf++ = pos[4+1][2];

	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];

	//right face +x
	*pf++ = pos[3][0];		*pf++ = pos[3][1];		*pf++ = pos[3][2];
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = pos[2][0];		*pf++ = pos[2][1];		*pf++ = pos[2][2];

	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = pos[3][0];		*pf++ = pos[3][1];		*pf++ = pos[3][2];
	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];

	//top face +y
	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = pos[4+1][0];	*pf++ = pos[4+1][1];	*pf++ = pos[4+1][2];

	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = pos[2][0];		*pf++ = pos[2][1];		*pf++ = pos[2][2];

	//bottom face +y
	*pf++ = pos[0][0];		*pf++ = pos[0][1];		*pf++ = pos[0][2];
	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];
	*pf++ = pos[3][0];		*pf++ = pos[3][1];		*pf++ = pos[3][2];

	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];
	*pf++ = pos[0][0];		*pf++ = pos[0][1];		*pf++ = pos[0][2];	
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];	
}

unsigned int GetCubeNormalSize(void){
	return 36;
}

void CreateCubeNormal(float* pf){
	float pos[8][3] = {
		{-1.0f,	-1.0f,  1.0f},
		{-1.0f,	 1.0f,  1.0f},
		{ 1.0f,	 1.0f,  1.0f},
		{ 1.0f,	-1.0f,  1.0f},

		{-1.0f,	-1.0f, -1.0f},
		{-1.0f,	 1.0f, -1.0f},
		{ 1.0f,	 1.0f, -1.0f},
		{ 1.0f,	-1.0f, -1.0f},
	};
	//front face +z
	*pf++ = pos[0][0];	*pf++ = pos[0][1];	*pf++ = pos[0][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = 1.0f;
	*pf++ = pos[2][0];	*pf++ = pos[2][1];	*pf++ = pos[2][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = 1.0f;
	*pf++ = pos[1][0];	*pf++ = pos[1][1];	*pf++ = pos[1][2];	
	*pf++ = 0;	*pf++ = 0;	*pf++ = 1.0f;
	
	*pf++ = pos[2][0];	*pf++ = pos[2][1];	*pf++ = pos[2][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = 1.0f;
	*pf++ = pos[0][0];	*pf++ = pos[0][1];	*pf++ = pos[0][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = 1.0f;
	*pf++ = pos[3][0];	*pf++ = pos[3][1];	*pf++ = pos[3][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = 1.0f;

	//left face -x
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = -1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = -1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[4+1][0];	*pf++ = pos[4+1][1];	*pf++ = pos[4+1][2];
	*pf++ = -1.0f;	*pf++ = 0;	*pf++ = 0;

	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = -1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = -1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[0][0];		*pf++ = pos[0][1];		*pf++ = pos[0][2];
	*pf++ = -1.0f;	*pf++ = 0;	*pf++ = 0;

	//back face -z
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = -1.0f;
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = -1.0f;
	*pf++ = pos[4+1][0];	*pf++ = pos[4+1][1];	*pf++ = pos[4+1][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = -1.0f;

	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = -1.0f;
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = -1.0f;
	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];
	*pf++ = 0;	*pf++ = 0;	*pf++ = -1.0f;

	//right face +x
	*pf++ = pos[3][0];		*pf++ = pos[3][1];		*pf++ = pos[3][2];
	*pf++ = 1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = 1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[2][0];		*pf++ = pos[2][1];		*pf++ = pos[2][2];
	*pf++ = 1.0f;	*pf++ = 0;	*pf++ = 0;

	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = 1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[3][0];		*pf++ = pos[3][1];		*pf++ = pos[3][2];
	*pf++ = 1.0f;	*pf++ = 0;	*pf++ = 0;
	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];
	*pf++ = 1.0f;	*pf++ = 0;	*pf++ = 0;

	//top face +y
	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = 0;	*pf++ = 1.0f;	*pf++ = 0;
	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = 0;	*pf++ = 1.0f;	*pf++ = 0;
	*pf++ = pos[4+1][0];	*pf++ = pos[4+1][1];	*pf++ = pos[4+1][2];
	*pf++ = 0;	*pf++ = 1.0f;	*pf++ = 0;

	*pf++ = pos[4+2][0];	*pf++ = pos[4+2][1];	*pf++ = pos[4+2][2];
	*pf++ = 0;	*pf++ = 1.0f;	*pf++ = 0;
	*pf++ = pos[1][0];		*pf++ = pos[1][1];		*pf++ = pos[1][2];
	*pf++ = 0;	*pf++ = 1.0f;	*pf++ = 0;
	*pf++ = pos[2][0];		*pf++ = pos[2][1];		*pf++ = pos[2][2];
	*pf++ = 0;	*pf++ = 1.0f;	*pf++ = 0;

	//bottom face -y
	*pf++ = pos[0][0];		*pf++ = pos[0][1];		*pf++ = pos[0][2];
	*pf++ = 0;	*pf++ = -1.0f;	*pf++ = 0;
	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];
	*pf++ = 0;	*pf++ = -1.0f;	*pf++ = 0;
	*pf++ = pos[3][0];		*pf++ = pos[3][1];		*pf++ = pos[3][2];
	*pf++ = 0;	*pf++ = -1.0f;	*pf++ = 0;

	*pf++ = pos[4+3][0];	*pf++ = pos[4+3][1];	*pf++ = pos[4+3][2];
	*pf++ = 0;	*pf++ = -1.0f;	*pf++ = 0;
	*pf++ = pos[0][0];		*pf++ = pos[0][1];		*pf++ = pos[0][2];	
	*pf++ = 0;	*pf++ = -1.0f;	*pf++ = 0;
	*pf++ = pos[4+0][0];	*pf++ = pos[4+0][1];	*pf++ = pos[4+0][2];
	*pf++ = 0;	*pf++ = -1.0f;	*pf++ = 0;
}


unsigned int GetNSphereSize(int iterations){
	return (unsigned int)powl( 4.0, (long double)iterations )*8*3;
}

/*
   Create a triangular facet approximation to a sphere
   Return the number of facets created.
   The number of facets will be (4^iterations) * 8
*/
int CreateNSphere(float*const pf,int iterations)
{
   int i,it;
   float a;
   XYZ p[6] = {0,0,1,  0,0,-1,  -1,-1,0,  1,-1,0,  1,1,0, -1,1,0};
   XYZ pa,pb,pc;
   int nt = 0,ntold;
   FACET3 * const f = (FACET3*)pf;

   /* Create the level 0 object */
   a = (float)(1 / sqrt(2.0));
   for (i=0;i<6;i++) {
      p[i].x *= a;
      p[i].y *= a;
   }
   f[0].p1 = p[0]; f[0].p2 = p[3]; f[0].p3 = p[4];
   f[1].p1 = p[0]; f[1].p2 = p[4]; f[1].p3 = p[5];
   f[2].p1 = p[0]; f[2].p2 = p[5]; f[2].p3 = p[2];
   f[3].p1 = p[0]; f[3].p2 = p[2]; f[3].p3 = p[3];
   f[4].p1 = p[1]; f[4].p2 = p[4]; f[4].p3 = p[3];
   f[5].p1 = p[1]; f[5].p2 = p[5]; f[5].p3 = p[4];
   f[6].p1 = p[1]; f[6].p2 = p[2]; f[6].p3 = p[5];
   f[7].p1 = p[1]; f[7].p2 = p[3]; f[7].p3 = p[2];
   nt = 8;

   if (iterations < 1)
      return(nt);

   /* Bisect each edge and move to the surface of a unit sphere */
   for (it=0;it<iterations;it++) {
      ntold = nt;
      for (i=0;i<ntold;i++) {
         pa.x = (f[i].p1.x + f[i].p2.x) / 2;
         pa.y = (f[i].p1.y + f[i].p2.y) / 2;
         pa.z = (f[i].p1.z + f[i].p2.z) / 2;
         pb.x = (f[i].p2.x + f[i].p3.x) / 2;
         pb.y = (f[i].p2.y + f[i].p3.y) / 2;
         pb.z = (f[i].p2.z + f[i].p3.z) / 2;
         pc.x = (f[i].p3.x + f[i].p1.x) / 2;
         pc.y = (f[i].p3.y + f[i].p1.y) / 2;
         pc.z = (f[i].p3.z + f[i].p1.z) / 2;
         Normalise(&pa);
         Normalise(&pb);
         Normalise(&pc);
         f[nt].p1 = f[i].p1; f[nt].p2 = pa; f[nt].p3 = pc; nt++;
         f[nt].p1 = pa; f[nt].p2 = f[i].p2; f[nt].p3 = pb; nt++;
         f[nt].p1 = pb; f[nt].p2 = f[i].p3; f[nt].p3 = pc; nt++;
         f[i].p1 = pa;
         f[i].p2 = pb;
         f[i].p3 = pc;
      }
   }

   return(nt);
}

#define TWO_PI 3.14159265*2.0

unsigned int GetCylinderSize(int segments){
	return segments*4*3;
}

//4 triangles per segment
int CreateCylinder(float*const pf, unsigned int nSegments, float height, float radius)
{
	float lower = -height*0.5f;
	float upper = height*0.5f;
	float curPos[2] ={0,radius};
	float nextPos[2] ={0,radius};
	unsigned int segment=0;
	float* pVert = pf;
	double step = TWO_PI/nSegments;
	float sinStep = (float)sin(step);
	float cosStep = (float)cos(step);

	nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
	nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;

	for(segment=0;segment<nSegments;segment++)
	{		
		//-------------
		//lower triangle cap
		//center lower
		*pVert++ = 0.0f;
		*pVert++ = lower;
		*pVert++ = 0.0f;
		//outer lower
		*pVert++ = curPos[0];
		*pVert++ = lower;
		*pVert++ = curPos[1];
		//oute lower
		*pVert++ = nextPos[0];
		*pVert++ = lower;
		*pVert++ = nextPos[1];

		//-------------
		//outer edge triangles
		//outer lower
		*pVert++ = curPos[0];
		*pVert++ = lower;
		*pVert++ = curPos[1];		
		//outer upper
		*pVert++ = curPos[0];
		*pVert++ = upper;
		*pVert++ = curPos[1];
		//outer lower
		*pVert++ = nextPos[0];
		*pVert++ = lower;
		*pVert++ = nextPos[1];

		//outer lower
		*pVert++ = nextPos[0];
		*pVert++ = lower;
		*pVert++ = nextPos[1];
		//outer upper
		*pVert++ = curPos[0];
		*pVert++ = upper;
		*pVert++ = curPos[1];
		//outer upper
		*pVert++ = nextPos[0];
		*pVert++ = upper;
		*pVert++ = nextPos[1];		

		//-------------
		//upper triangle cap
		//center upper
		*pVert++ = 0.0f;
		*pVert++ = upper;
		*pVert++ = 0.0f;		
		//oute upper
		*pVert++ = nextPos[0];
		*pVert++ = upper;
		*pVert++ = nextPos[1];		
		//outer upper
		*pVert++ = curPos[0];
		*pVert++ = upper;
		*pVert++ = curPos[1];

		//rotate to next segment
		curPos[0] = nextPos[0];
		curPos[1] = nextPos[1];
		nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
		nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;
	}
	return 4*nSegments; //returns number of faces
}

unsigned int GetConeSize(int segments){
	return segments*4*3;
}
//2 triangles per segment
int CreateCone(float*const pf, unsigned int nSegments, float height, float radius)
{
	float lower = -height*0.5f;
	float upper = height*0.5f;
	float curPos[2] ={0,radius};
	float nextPos[2] ={0,radius};
	unsigned int segment=0;
	float* pVert = pf;
	double step = TWO_PI/nSegments;
	float sinStep = (float)sin(step);
	float cosStep = (float)cos(step);

	nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
	nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;

	for(segment=0;segment<nSegments;segment++)
	{		
		//-------------
		//lower triangle cap
		//center lower
		*pVert++ = 0.0f;
		*pVert++ = lower;
		*pVert++ = 0.0f;
		//outer lower
		*pVert++ = curPos[0];
		*pVert++ = lower;
		*pVert++ = curPos[1];
		//oute lower
		*pVert++ = nextPos[0];
		*pVert++ = lower;
		*pVert++ = nextPos[1];
				
		//-------------
		//upper triangle cap
		//center upper
		*pVert++ = 0.0f;
		*pVert++ = upper;
		*pVert++ = 0.0f;		
		//oute upper
		*pVert++ = nextPos[0];
		*pVert++ = lower;
		*pVert++ = nextPos[1];		
		//outer upper
		*pVert++ = curPos[0];
		*pVert++ = lower;
		*pVert++ = curPos[1];

		//rotate to next segment
		curPos[0] = nextPos[0];
		curPos[1] = nextPos[1];
		nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
		nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;
	}
	return 2*nSegments;
}

unsigned int GetTorusSize(int nTubeSegments, int nTorusSegments){
	return 2*nTubeSegments*nTorusSegments*3;
}

int CreateFrustum(float*const pf, float l, float r, float b, float t, float n, float f)
{
	int j=0;

	float proj[16]={
		//col 1
		(r-l)/(2*n),0,0,0,
		//col 2
		0,(t-b)/(2*n),0,0,
		//col 3
		0,0,0,-(f-n)/(2*f*n),
		//col4
		(r+l)/(2*n),(t+b)/(2*n),-1,	(f+n)/(2*f*n)
	};

	// Get the sides of the near plane.
    const float nLeft = n * (proj[2] - 1.0f) / proj[0];
    const float nRight = n * (1.0f + proj[2]) / proj[0];
    const float nTop = n * (1.0f + proj[6]) / proj[5];
    const float nBottom = n * (proj[6] - 1.0f) / proj[5];

    // Get the sides of the far plane.
    const float fLeft = f * (proj[2] - 1.0f) / proj[0];
    const float fRight = f * (1.0f + proj[2]) / proj[0];
    const float fTop = f * (1.0f + proj[6]) / proj[5];
    const float fBottom = f * (proj[6] - 1.0f) / proj[5];

	float tVerts[8][3]=	{
		{nLeft,nBottom,-n},	//0
		{nLeft,nTop,-n},	//1
		{nRight,nTop,-n},	//2
		{nRight,nBottom,-n},//3

		{fLeft,fBottom,-f},	//4
		{fLeft,fTop,-f},	//5
		{fRight,fTop,-f},	//6
		{fRight,fBottom,-f} //7
	};

	float* pVert = pf;
	
	//near face
	*pVert++ = tVerts[0][0];	*pVert++ = tVerts[0][1];	*pVert++ = tVerts[0][2];
	*pVert++ = tVerts[2][0];	*pVert++ = tVerts[2][1];	*pVert++ = tVerts[2][2];
	*pVert++ = tVerts[1][0];	*pVert++ = tVerts[1][1];	*pVert++ = tVerts[1][2];
	//
	*pVert++ = tVerts[2][0];	*pVert++ = tVerts[2][1];	*pVert++ = tVerts[2][2];
	*pVert++ = tVerts[0][0];	*pVert++ = tVerts[0][1];	*pVert++ = tVerts[0][2];
	*pVert++ = tVerts[3][0];	*pVert++ = tVerts[3][1];	*pVert++ = tVerts[3][2];

	//far face
	*pVert++ = tVerts[4][0];	*pVert++ = tVerts[4][1];	*pVert++ = tVerts[4][2];
	*pVert++ = tVerts[5][0];	*pVert++ = tVerts[5][1];	*pVert++ = tVerts[5][2];
	*pVert++ = tVerts[6][0];	*pVert++ = tVerts[6][1];	*pVert++ = tVerts[6][2];
	//
	*pVert++ = tVerts[6][0];	*pVert++ = tVerts[6][1];	*pVert++ = tVerts[6][2];
	*pVert++ = tVerts[7][0];	*pVert++ = tVerts[7][1];	*pVert++ = tVerts[7][2];
	*pVert++ = tVerts[4][0];	*pVert++ = tVerts[4][1];	*pVert++ = tVerts[4][2];

	//top face
	*pVert++ = tVerts[1][0];	*pVert++ = tVerts[1][1];	*pVert++ = tVerts[1][2];
	*pVert++ = tVerts[2][0];	*pVert++ = tVerts[2][1];	*pVert++ = tVerts[2][2];
	*pVert++ = tVerts[5][0];	*pVert++ = tVerts[5][1];	*pVert++ = tVerts[5][2];
	//
	*pVert++ = tVerts[5][0];	*pVert++ = tVerts[5][1];	*pVert++ = tVerts[5][2];
	*pVert++ = tVerts[2][0];	*pVert++ = tVerts[2][1];	*pVert++ = tVerts[2][2];
	*pVert++ = tVerts[6][0];	*pVert++ = tVerts[6][1];	*pVert++ = tVerts[6][2];

	//bottom face
	*pVert++ = tVerts[0][0];	*pVert++ = tVerts[0][1];	*pVert++ = tVerts[0][2];
	*pVert++ = tVerts[4][0];	*pVert++ = tVerts[4][1];	*pVert++ = tVerts[4][2];
	*pVert++ = tVerts[3][0];	*pVert++ = tVerts[3][1];	*pVert++ = tVerts[3][2];
	//
	*pVert++ = tVerts[4][0];	*pVert++ = tVerts[4][1];	*pVert++ = tVerts[4][2];
	*pVert++ = tVerts[7][0];	*pVert++ = tVerts[7][1];	*pVert++ = tVerts[7][2];
	*pVert++ = tVerts[3][0];	*pVert++ = tVerts[3][1];	*pVert++ = tVerts[3][2];

	//left face
	*pVert++ = tVerts[0][0];	*pVert++ = tVerts[0][1];	*pVert++ = tVerts[0][2];
	*pVert++ = tVerts[1][0];	*pVert++ = tVerts[1][1];	*pVert++ = tVerts[1][2];
	*pVert++ = tVerts[4][0];	*pVert++ = tVerts[4][1];	*pVert++ = tVerts[4][2];
	//
	*pVert++ = tVerts[4][0];	*pVert++ = tVerts[4][1];	*pVert++ = tVerts[4][2];
	*pVert++ = tVerts[1][0];	*pVert++ = tVerts[1][1];	*pVert++ = tVerts[1][2];
	*pVert++ = tVerts[5][0];	*pVert++ = tVerts[5][1];	*pVert++ = tVerts[5][2];

	//right face
	*pVert++ = tVerts[2][0];	*pVert++ = tVerts[2][1];	*pVert++ = tVerts[2][2];
	*pVert++ = tVerts[3][0];	*pVert++ = tVerts[3][1];	*pVert++ = tVerts[3][2];
	*pVert++ = tVerts[6][0];	*pVert++ = tVerts[6][1];	*pVert++ = tVerts[6][2];
	//
	*pVert++ = tVerts[6][0];	*pVert++ = tVerts[6][1];	*pVert++ = tVerts[6][2];
	*pVert++ = tVerts[3][0];	*pVert++ = tVerts[3][1];	*pVert++ = tVerts[3][2];
	*pVert++ = tVerts[7][0];	*pVert++ = tVerts[7][1];	*pVert++ = tVerts[7][2];

	return 12*3;
}

/*
Creates an open ended cylinder at the origin with radius=tubeRadius divided into tubeSegments parts
then rotates the vertices into the correct space of the torus

-the compact version combines both steps
- the easy to read version separates them out to make it easier to see what is happening

--
you need to allocate enough space for 

2 * nTubeSegments * nSegments * 3 * 3 floats

in float*const pf

where:
2 is the number of faces per torus segment
3 is the number of vertices per face
3 the number of floats per vertex
respectively

*/
int CreateTorus(float*const pf, unsigned int nSegments, float radius, unsigned int nTubeSegments, float tubeRadius)
{
	unsigned int segment=0, tubeSegment=0;
	float* pVert = pf;
	float* pVertStart = pf;

	//user for creating the radius of the donus
	float curPos[2] ={0,radius}; //xz
	float nextPos[2] ={0,radius};//xz

	//used in creating the Tube 
	float curTubePos[2]; //yz
	float nextTubePos[2];//yz

	double step = TWO_PI/nSegments;

	float sinStep = 0, cosStep = 0;
	float sinNextStep = 0, cosNextStep = 0;
	double curStep=0, nextStep=step;

	double step2 = TWO_PI/nTubeSegments;
	float sinStep2 = (float)sin(step2);
	float cosStep2 = (float)cos(step2);
	float tmp[2] = {0,0};

	for(segment=0;segment<nSegments;segment++)
	{	
		//positions around the doughnut
		sinStep = (float)sin(curStep);
		cosStep = (float)cos(curStep);
		sinNextStep = (float)sin(nextStep);
		cosNextStep = (float)cos(nextStep);

		curPos[0] = -radius*sinStep;
		curPos[1] = radius*cosStep;
		nextPos[0] = -radius*sinNextStep;
		nextPos[1] = radius*cosNextStep;

		//positions around the Tube
		curTubePos[0] = 0;	curTubePos[1] = tubeRadius;
		nextTubePos[0] = curTubePos[0]*cosStep2 - curTubePos[1]*sinStep2;
		nextTubePos[1] = curTubePos[0]*sinStep2 + curTubePos[1]*cosStep2;
		//*
		//Compact version		
		for(tubeSegment=0;tubeSegment<nTubeSegments;tubeSegment++)		
		{
			//outer edge triangles
			//inner
			*pVert++ = curPos[0] - (curTubePos[1]*sinStep);
			*pVert++ = curTubePos[0];
			*pVert++ = curPos[1] + (curTubePos[1]*cosStep);			
			//outer
			*pVert++ = nextPos[0] - (curTubePos[1]*sinNextStep);
			*pVert++ = curTubePos[0];
			*pVert++ = nextPos[1] + (curTubePos[1]*cosNextStep);
			//inner
			*pVert++ = curPos[0] - (nextTubePos[1]*sinStep);
			*pVert++ = nextTubePos[0];
			*pVert++ = curPos[1] + (nextTubePos[1]*cosStep);

			//outer
			*pVert++ = nextPos[0] - (nextTubePos[1]*sinNextStep);
			*pVert++ = nextTubePos[0];
			*pVert++ = nextPos[1] + (nextTubePos[1]*cosNextStep);
			//inner
			*pVert++ = curPos[0] - (nextTubePos[1]*sinStep);
			*pVert++ = nextTubePos[0];
			*pVert++ = curPos[1] + (nextTubePos[1]*cosStep);
			//outer
			*pVert++ = nextPos[0] - (curTubePos[1]*sinNextStep);
			*pVert++ = curTubePos[0];
			*pVert++ = nextPos[1] + (curTubePos[1]*cosNextStep);

			curTubePos[0] = nextTubePos[0];
			curTubePos[1] = nextTubePos[1];
			nextTubePos[0] = curTubePos[0]*cosStep2 - curTubePos[1]*sinStep2;
			nextTubePos[1] = curTubePos[0]*sinStep2 + curTubePos[1]*cosStep2;
		}
		/*/
		//easy to read version
		pVertStart = pVert;
		//Create a open tube at the origin, with radius tubeRadius
		//and the open ends lying on the X axis
		for(tubeSegment=0;tubeSegment<nTubeSegments;tubeSegment++)		
		{
			//outer edge triangles
			//inner
			*pVert++ = 0;
			*pVert++ = curTubePos[0];
			*pVert++ = curTubePos[1];			
			//outer
			*pVert++ = 0;
			*pVert++ = curTubePos[0];
			*pVert++ = curTubePos[1];
			//inner
			*pVert++ = 0;
			*pVert++ = nextTubePos[0];
			*pVert++ = nextTubePos[1];

			//outer
			*pVert++ = 0;
			*pVert++ = nextTubePos[0];
			*pVert++ = nextTubePos[1];
			//inner
			*pVert++ = 0;
			*pVert++ = nextTubePos[0];
			*pVert++ = nextTubePos[1];
			//outer
			*pVert++ = 0;
			*pVert++ = curTubePos[0];
			*pVert++ = curTubePos[1];

			curTubePos[0] = nextTubePos[0];
			curTubePos[1] = nextTubePos[1];
			nextTubePos[0] = curTubePos[0]*cosStep2 - curTubePos[1]*sinStep2;
			nextTubePos[1] = curTubePos[0]*sinStep2 + curTubePos[1]*cosStep2;
		}
		//rotate the created vertices into the correct position for the torus		
		for(tubeSegment=0;tubeSegment<nTubeSegments;tubeSegment++)
		{
			//inner
			tmp[0] = pVertStart[0];
			tmp[1] = pVertStart[2];
			pVertStart[0] = curPos[0] + (tmp[0]*cosStep) - (tmp[1]*sinStep);
			pVertStart[2] = curPos[1] + (tmp[0]*sinStep) + (tmp[1]*cosStep);

			//inner
			tmp[0] = pVertStart[3];
			tmp[1] = pVertStart[5];
			pVertStart[3] = nextPos[0] + (tmp[0]*cosNextStep) - (tmp[1]*sinNextStep);
			pVertStart[5] = nextPos[1] + (tmp[0]*sinNextStep) + (tmp[1]*cosNextStep);

			//outer
			tmp[0] = pVertStart[6];
			tmp[1] = pVertStart[8];
			pVertStart[6] = curPos[0] + (tmp[0]*cosStep) - (tmp[1]*sinStep);			
			pVertStart[8] = curPos[1] + (tmp[0]*sinStep) + (tmp[1]*cosStep);

			//outer lower
			tmp[0] = pVertStart[9];
			tmp[1] = pVertStart[11];
			pVertStart[9] = nextPos[0] + (tmp[0]*cosNextStep) - (tmp[1]*sinNextStep);
			pVertStart[11] = nextPos[1] + (tmp[0]*sinNextStep) + (tmp[1]*cosNextStep);

			//outer upper
			tmp[0] = pVertStart[12];
			tmp[1] = pVertStart[14];
			pVertStart[12] = curPos[0] + (tmp[0]*cosStep) - (tmp[1]*sinStep);
			pVertStart[14] = curPos[1] + (tmp[0]*sinStep) + (tmp[1]*cosStep);

			//outer upper
			tmp[0] = pVertStart[15];
			tmp[1] = pVertStart[17];
			pVertStart[15] = nextPos[0] + (tmp[0]*cosNextStep) - (tmp[1]*sinNextStep);
			pVertStart[17] = nextPos[1] + (tmp[0]*sinNextStep) + (tmp[1]*cosNextStep);			
			pVertStart+=18;
		}	
		//*/
		curStep=nextStep;
		nextStep=nextStep+step;
	}
	return 2*nTubeSegments*nSegments; //returns number of faces
}

int CreatePlane(float*const pf, float halfWidth, float halfDepth)
{
	float* pVert = pf;
	*pVert++ = -halfWidth;	*pVert++ = 0;	*pVert++ = -halfDepth;
	*pVert++ = -halfWidth;	*pVert++ = 0;	*pVert++ = halfDepth;
	*pVert++ = halfWidth;	*pVert++ = 0;	*pVert++ = -halfDepth;

	*pVert++ = halfWidth;	*pVert++ = 0;	*pVert++ = -halfDepth;	
	*pVert++ = -halfWidth;	*pVert++ = 0;	*pVert++ = halfDepth;
	*pVert++ = halfWidth;	*pVert++ = 0;	*pVert++ = halfDepth;
	return 2;
}


/*
Generates vertices for drawing a Torus, does not duplicate data 

--
you need to allocate enough space for 
nTubeSegments * nSegments * 3 floats
in float*const pf
where:
3 the number of floats per vertex

--
If you want to use an element buffer to render these the order of vertices is
Around the inner tube in segments 
so a possible elements array would go something like 

0,1,[nTubeSegments]					#triangle 0
[nTubeSegments],1,[nTubeSegments]+1 #triangle 1
....
with the last triangle being generated between 
[nTubeSegments*(nSegments-1)]
and the start at 0
*/

int CreateTorusVertices(float*const pf, unsigned int nSegments, float radius, unsigned int nTubeSegments, float tubeRadius)
{
	unsigned int segment=0, tubeSegment=0;
	float* pVert = pf;
	float* pVertStart = pf;

	//user for creating the radius of the donus
	float curPos[2] ={0,radius}; //xz
	float nextPos[2] ={0,radius};//xz

	//used in creating the Tube 
	float curTubePos[2]; //yz
	float nextTubePos[2];//yz

	double step = TWO_PI/nSegments;

	float sinStep = 0, cosStep = 0;
	float sinNextStep = 0, cosNextStep = 0;
	double curStep=0, nextStep=step;

	double step2 = TWO_PI/nTubeSegments;
	float sinStep2 = (float)sin(step2);
	float cosStep2 = (float)cos(step2);
	float tmp[2] = {0,0};

	for(segment=0;segment<nSegments;segment++)
	{	
		//positions around the doughnut
		sinStep = (float)sin(curStep);
		cosStep = (float)cos(curStep);
		sinNextStep = (float)sin(nextStep);
		cosNextStep = (float)cos(nextStep);

		curPos[0] = -radius*sinStep;
		curPos[1] = radius*cosStep;
		nextPos[0] = -radius*sinNextStep;
		nextPos[1] = radius*cosNextStep;

		//positions around the Tube
		curTubePos[0] = 0;	curTubePos[1] = tubeRadius;
		nextTubePos[0] = curTubePos[0]*cosStep2 - curTubePos[1]*sinStep2;
		nextTubePos[1] = curTubePos[0]*sinStep2 + curTubePos[1]*cosStep2;
		//*
		//Compact version		
		for(tubeSegment=0;tubeSegment<nTubeSegments;tubeSegment++)		
		{
			//outer edge triangles
			//inner
			*pVert++ = curPos[0] - (curTubePos[1]*sinStep);
			*pVert++ = curTubePos[0];
			*pVert++ = curPos[1] + (curTubePos[1]*cosStep);			
			//outer
			//*pVert++ = nextPos[0] - (curTubePos[1]*sinNextStep);
			//*pVert++ = curTubePos[0];
			//*pVert++ = nextPos[1] + (curTubePos[1]*cosNextStep);			

			curTubePos[0] = nextTubePos[0];
			curTubePos[1] = nextTubePos[1];
			nextTubePos[0] = curTubePos[0]*cosStep2 - curTubePos[1]*sinStep2;
			nextTubePos[1] = curTubePos[0]*sinStep2 + curTubePos[1]*cosStep2;
		}		
		curStep=nextStep;
		nextStep=nextStep+step;
	}
	return nTubeSegments*nSegments; //returns number of vertices
}

/*
vertex order 
-lower circle centre
-lower circle radius 
-upper circle centre
-upper circle radius 
*/
int CreateCylinderVertices(float*const pf, unsigned int nSegments, float height, float radius)
{
	float lower = -height*0.5f;
	float upper = height*0.5f;
	float curPos[2] ={0,radius};
	float nextPos[2] ={0,radius};
	unsigned int segment=0;
	float* pVertLower = pf;
	float* pVertUpper = pf+((nSegments+1)*3);
	double step = TWO_PI/nSegments;
	float sinStep = (float)sin(step);
	float cosStep = (float)cos(step);

	nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
	nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;

	//-------------
	//lower circle
	*pVertLower++ = 0.0f;
	*pVertLower++ = lower;
	*pVertLower++ = 0.0f;

	*pVertUpper++ = 0.0f;
	*pVertUpper++ = upper;
	*pVertUpper++ = 0.0f;

	for(segment=0;segment<nSegments;segment++)
	{		
		//lower
		*pVertLower++ = curPos[0];
		*pVertLower++ = lower;
		*pVertLower++ = curPos[1];

		//upper
		*pVertUpper++ = curPos[0];
		*pVertUpper++ = upper;
		*pVertUpper++ = curPos[1];

		//rotate to next segment
		curPos[0] = nextPos[0];
		curPos[1] = nextPos[1];
		nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
		nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;
	}
	return 2*(nSegments+1); //returns number of faces
}

/*
vertex order
top, 
bottom centre
bottom radius

requires space for nSegments+2 vertices
*/
int CreateConeVertices(float*const pf, unsigned int nSegments, float height, float radius)
{
	float lower = -height*0.5f;
	float upper = height*0.5f;
	float curPos[2] ={0,radius};
	float nextPos[2] ={0,radius};
	unsigned int segment=0;
	float* pVert = pf;
	double step = TWO_PI/nSegments;
	float sinStep = (float)sin(step);
	float cosStep = (float)cos(step);

	nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
	nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;

	*pVert++ = 0.0f;
	*pVert++ = upper;
	*pVert++ = 0.0f;

	*pVert++ = 0.0f;
	*pVert++ = lower;
	*pVert++ = 0.0f;

	for(segment=0;segment<nSegments;segment++)
	{		
		//outer lower
		*pVert++ = curPos[0];
		*pVert++ = lower;
		*pVert++ = curPos[1];

		//rotate to next segment
		curPos[0] = nextPos[0];
		curPos[1] = nextPos[1];
		nextPos[0] = curPos[0]*cosStep - curPos[1]*sinStep;
		nextPos[1] = curPos[0]*sinStep + curPos[1]*cosStep;
	}
	return nSegments+2;
}

int CreateFrustumVertices(float*const pf, float l, float r, float b, float t, float n, float f)
{
	int j=0;

	float proj[16]={
		//col 1
		(r-l)/(2*n),0,0,0,
		//col 2
		0,(t-b)/(2*n),0,0,
		//col 3
		0,0,0,-(f-n)/(2*f*n),
		//col4
		(r+l)/(2*n),(t+b)/(2*n),-1,	(f+n)/(2*f*n)
	};

	// Get the sides of the near plane.
    const float nLeft = n * (proj[2] - 1.0f) / proj[0];
    const float nRight = n * (1.0f + proj[2]) / proj[0];
    const float nTop = n * (1.0f + proj[6]) / proj[5];
    const float nBottom = n * (proj[6] - 1.0f) / proj[5];

    // Get the sides of the far plane.
    const float fLeft = f * (proj[2] - 1.0f) / proj[0];
    const float fRight = f * (1.0f + proj[2]) / proj[0];
    const float fTop = f * (1.0f + proj[6]) / proj[5];
    const float fBottom = f * (proj[6] - 1.0f) / proj[5];
	float* pVert = pf;

	*pVert++ = nLeft;	*pVert++ = nBottom;	*pVert++ = -n;
	*pVert++ = nLeft;	*pVert++ = nTop;	*pVert++ = -n;
	*pVert++ = nRight;	*pVert++ = nTop;	*pVert++ = -n;
	*pVert++ = nRight;	*pVert++ = nBottom;	*pVert++ = -n;


	*pVert++ = fLeft;	*pVert++ = fBottom;	*pVert++ = -f;
	*pVert++ = fLeft;	*pVert++ = fTop;	*pVert++ = -f;
	*pVert++ = fRight;	*pVert++ = fTop;	*pVert++ = -f;
	*pVert++ = fRight;	*pVert++ = fBottom;	*pVert++ = -f;

	return 4;
}