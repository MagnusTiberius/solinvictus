#ifndef _SHAPES_UTIL_H_
#define _SHAPES_UTIL_H_

typedef enum{
	SHAPE_SPHERE = 0,
	SHAPE_CYLINDER,
	SHAPE_CONE,
	SHAPE_TORUS,
	SHAPE_FRUSTUM,
	SHAPE_PLANE,
	SHAPE_CUBE,
}ShapeType;

 typedef struct{
	ShapeType type;
	unsigned int vao, ab, n_vertices;
}Shape;

extern Shape CreateShapeCube(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern Shape CreateShapeCubeNormals(unsigned int pos_bind = 0, unsigned int clr_bind = 1, unsigned int nrm_bind = 2);
extern Shape CreateShapeSphere(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern Shape CreateShapeSphereNormals(unsigned int pos_bind = 0, unsigned int clr_bind = 1, unsigned int nrm_bind = 2);
extern Shape CreateShapeCylinder(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern Shape CreateShapeCone(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern Shape CreateShapeTorus(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern Shape CreateShapeFrustum(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern Shape CreateShapePlane(unsigned int pos_bind = 0, unsigned int clr_bind = 1);
extern void DrawShape(Shape shape);
extern void DestroyShape(Shape shape);

#endif _SHAPES_UTIL_H_