#ifndef _SHAPES_H_
#define _SHAPES_H_

 #ifdef __cplusplus
 extern "C" {
 #endif

//generates vertices for shapes that can be rendered by calling glDrawArray
//don't require element arrays

extern unsigned int GetCubeSize(void);
extern void CreateCube(float* pf);

extern unsigned int GetCubeNormalSize(void);
extern void CreateCubeNormal(float* pf);

extern unsigned int GetNSphereSize(int iterations);
extern int CreateNSphere(float*const pf,int iterations);

extern unsigned int GetCylinderSize(int iterations);
extern int CreateCylinder(float*const pf, unsigned int nSegments, float height, float radius);

extern unsigned int GetConeSize(int nSegments);
extern int CreateCone(float*const pf, unsigned int nSegments, float height, float radius);

extern unsigned int GetTorusSize(int nTubeSegments, int nTorusSegments);
extern int CreateTorus(float*const pf, unsigned int nSegments, float radius, unsigned int nTubeSegments, float tubeRadius);

extern int CreateFrustum(float*const pf, float l, float r, float b, float t, float n, float f);
extern int CreatePlane(float*const pf, float halfWidth, float halfDepth);

//there functions created the vertices, no duplicated data like in the above, however 
//you'll need an element array to render them as triangles correctly
extern int CreateCylinderVertices(float*const pf, unsigned int nSegments, float height, float radius);
extern int CreateConeVertices(float*const pf, unsigned int nSegments, float height, float radius);
extern int CreateTorusVertices(float*const pf, unsigned int nSegments, float radius, unsigned int nTubeSegments, float tubeRadius);

 #ifdef __cplusplus
 }
 #endif


#endif _SHAPES_H_