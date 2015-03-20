#include <math.h>
#include "shapes_util.h"
#include "shapes.h"
#include "wrapper_gl.hpp"


Shape CreateShapeCube( unsigned int pos_bind, unsigned int clr_bind ){
	Shape shape = {SHAPE_CUBE, 0, 0, 0};

	shape.n_vertices = GetCubeSize();
	unsigned int nCubeFloats = ( shape.n_vertices + 1 )*3;
	float* pCubeVertices = ( float* ) malloc ( sizeof( float ) * nCubeFloats );	

	pCubeVertices[0] = 1.0f;
	pCubeVertices[1] = 0.0f;
	pCubeVertices[2] = 0.0f;
	CreateCube( pCubeVertices + 3 );	

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer( WRender::ARRAY, WRender::STATIC, sizeof(float) * nCubeFloats, pCubeVertices );
	
	WRender::VertexAttribute vaSphere[2] = {
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0,				1},
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3,	0},		
	};		

	WRender::BindVertexArrayObject( shape.vao );
	WRender::SetAttributeFormat( vaSphere, 2, 0);

	free( pCubeVertices );

	return shape;
}

Shape CreateShapeCubeNormals(unsigned int pos_bind, unsigned int clr_bind, unsigned int nrm_bind ){
	Shape shape = {SHAPE_CUBE, 0, 0, 0};

	shape.n_vertices = GetCubeNormalSize();
	unsigned int nCubeFloats = ( shape.n_vertices*2 + 1 )*3;
	float* pCubeVertices = ( float* ) malloc ( sizeof( float ) * nCubeFloats );	

	pCubeVertices[0] = 1.0f;
	pCubeVertices[1] = 0.0f;
	pCubeVertices[2] = 0.0f;
	CreateCubeNormal( pCubeVertices + 3 );	

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer( WRender::ARRAY, WRender::STATIC, sizeof(float) * nCubeFloats, pCubeVertices );
	
	WRender::VertexAttribute vaSphere[3] = {
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0,				1},
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*6, sizeof(float)*3,	0},		
		{shape.ab, nrm_bind, 3, WRender::FLOAT, 0, sizeof(float)*6, sizeof(float)*6,	0},		
	};		

	WRender::BindVertexArrayObject( shape.vao );
	WRender::SetAttributeFormat( vaSphere, 3, 0);

	free( pCubeVertices );

	return shape;
}

Shape CreateShapeSphere( unsigned int pos_bind, unsigned int clr_bind ){
	Shape shape = {SHAPE_SPHERE, 0, 0, 0};

	unsigned int iterations = 4;
	shape.n_vertices = GetNSphereSize(iterations);
	unsigned int nSphereFloats = ( shape.n_vertices + 1 )*3;
	float* pSphereVertices = ( float* ) malloc ( sizeof( float ) * nSphereFloats );	

	pSphereVertices[0] = 1.0f;
	pSphereVertices[1] = 0.0f;
	pSphereVertices[2] = 0.0f;
	CreateNSphere( pSphereVertices + 3, iterations );	

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer( WRender::ARRAY, WRender::STATIC, sizeof(float) * nSphereFloats, pSphereVertices );
	
	WRender::VertexAttribute vaSphere[2] = {
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0,				1},
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3,	0},		
	};		

	WRender::BindVertexArrayObject( shape.vao );
	WRender::SetAttributeFormat( vaSphere, 2, 0);

	free( pSphereVertices );

	return shape;
}

Shape CreateShapeSphereNormals(unsigned int pos_bind, unsigned int clr_bind, unsigned int nrm_bind){
	Shape shape = {SHAPE_SPHERE, 0, 0, 0};

	unsigned int iterations = 4;
	shape.n_vertices = GetNSphereSize(iterations);
	unsigned int nSphereFloats = ( shape.n_vertices*2 + 1 )*3;
	float* pSphereVertices = ( float* ) malloc ( sizeof( float ) * nSphereFloats );	
	memset(pSphereVertices, 0, sizeof( float ) * nSphereFloats);

	pSphereVertices[0] = 1.0f;
	pSphereVertices[1] = 0.0f;
	pSphereVertices[2] = 0.0f;
	CreateNSphere( pSphereVertices + 3, iterations );	

	//create normals
	float *pVerts = pSphereVertices + 3;
	float *pNorms = pSphereVertices + (shape.n_vertices+1)*3;
	float x,y,z,l;
	for(unsigned int i=0; i<shape.n_vertices; i++){
	//for(unsigned int i=0; i<10; i++){
		x = pVerts[0];	y = pVerts[1];	z = pVerts[2];
		l = sqrt(x*x + y*y + z*z);
		pNorms[0] = x/l; pNorms[1] = y/l; pNorms[2] = z/l;
		//advance
		pVerts += 3;
		pNorms += 3;		
	}

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer( WRender::ARRAY, WRender::STATIC, sizeof(float) * nSphereFloats, pSphereVertices );
	
	WRender::VertexAttribute vaSphere[3] = {
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0,				1},
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3,	0},		
		{shape.ab, nrm_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3*(shape.n_vertices+1),	0},		
	};		

	WRender::BindVertexArrayObject( shape.vao );
	WRender::SetAttributeFormat( vaSphere, 3, 0);

	free( pSphereVertices );

	return shape;
}

Shape CreateShapeCylinder(unsigned int pos_bind, unsigned int clr_bind){
	Shape shape = {SHAPE_CYLINDER, 0, 0, 0};
	unsigned int segments = 20;
	shape.n_vertices = GetCylinderSize(segments);
	int nCylinderFloats = (shape.n_vertices+1)*3;
	float* pCylinderVertices = new float[nCylinderFloats];

	pCylinderVertices[0] = 1.0f;
	pCylinderVertices[1] = 0.0f;
	pCylinderVertices[2] = 0.0f;
	CreateCylinder(pCylinderVertices + 3, segments, 1.0f, 1.0f);	

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer(WRender::ARRAY, WRender::STATIC, sizeof(float)*nCylinderFloats, pCylinderVertices);	

	WRender::BindVertexArrayObject( shape.vao );
	WRender::VertexAttribute vaCylinder[2] = {
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3,	0},
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0,					1},
	};
	WRender::SetAttributeFormat( vaCylinder, 2, 0);
	delete[] pCylinderVertices;

	return shape;
}

Shape CreateShapeCone(unsigned int pos_bind, unsigned int clr_bind){
	Shape shape = {SHAPE_CONE, 0, 0, 0};
	unsigned int coneSegments = 20;	
	shape.n_vertices = GetConeSize(coneSegments);
	int nConeFloats = (shape.n_vertices+1)*3;
	float * pConeVertices = new float[nConeFloats];

	pConeVertices[0] = 1.0f;
	pConeVertices[1] = 0.0f;
	pConeVertices[2] = 0.0f;
	CreateCone(pConeVertices + 3, coneSegments, 5.0f, 1.0f);

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer(WRender::ARRAY, WRender::STATIC, sizeof(float)*nConeFloats, pConeVertices);	

	WRender::BindVertexArrayObject( shape.vao );
	WRender::VertexAttribute vaCone[2] = {
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3,	0},
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0,					1},
	};
	WRender::SetAttributeFormat( vaCone, 2, 0);
	delete[] pConeVertices;
	return shape;
}

Shape CreateShapeTorus(unsigned int pos_bind, unsigned int clr_bind){
	Shape shape = {SHAPE_TORUS, 0, 0, 0};
	unsigned int torusSegments = 20;
	unsigned int torusTubeSegments = 10;
	float radius = 1.0f;
	float tube_radius = 0.4f;
	shape.n_vertices = GetTorusSize(torusTubeSegments, torusSegments);

	int nTorusFloats = (shape.n_vertices+1)*3;
	float* pTorusVertices = new float[nTorusFloats];

	pTorusVertices[0] = 1.0f;
	pTorusVertices[1] = 0.0f;
	pTorusVertices[2] = 0.0f;
	CreateTorus(pTorusVertices + 3, torusSegments, radius, torusTubeSegments, tube_radius);	

	shape.vao = WRender::CreateVertexArrayObject();
	shape.ab = WRender::CreateBuffer(WRender::ARRAY, WRender::STATIC, sizeof(float)*nTorusFloats, pTorusVertices);	

	WRender::BindVertexArrayObject(shape.vao);
	WRender::VertexAttribute vaTorus[2] = {
		{shape.ab, pos_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, sizeof(float)*3, 0},
		{shape.ab, clr_bind, 3, WRender::FLOAT, 0, sizeof(float)*3, 0, 1},
	};
	WRender::SetAttributeFormat( vaTorus, 2, 0);
	delete[] pTorusVertices;

	return shape;
}

Shape CreateShapeFrustum(unsigned int pos_bind, unsigned int clr_bind){
	Shape shape;
	return shape;
}


Shape CreateShapePlane(unsigned int pos_bind, unsigned int clr_bind){
	Shape shape;
	return shape;
}

void DrawShape(Shape shape){

	WRender::BindVertexArrayObject(shape.vao);

	switch(shape.type){
	case SHAPE_SPHERE:
	case SHAPE_CYLINDER:
	case SHAPE_CONE:
	case SHAPE_TORUS:
	case SHAPE_CUBE:
		WRender::DrawArray(WRender::TRIANGLES, shape.n_vertices, 0);
		break;
	default:
		return;
	}	
}

void DestroyShape(Shape shape){
	WRender::DeleteBuffer(shape.ab);
	WRender::DeleteBuffer(shape.vao);	
}