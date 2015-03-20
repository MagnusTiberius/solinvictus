#ifndef _MATRIX33PP_H_
#define _MATRIX33PP_H_

#define P_I (3.14159265f)
#define TO_RAD (P_I/180.0f)

#include "vec3df++.h"
#include "matrix44++.h"

static float Determinant3f(const float m[16])
{
	return   m[0]*(m[4]*m[8] - m[5]*m[7])
			-m[3]*(m[1]*m[8] - m[2]*m[7])
			+m[6]*(m[1]*m[5] - m[2]*m[4]);
}

static bool GenerateInverseMatrix3f(float i[9], const float m[9])
{
	float x=Determinant3f(m);
	if (x==0) return false;
	float invdev = 1.0f/x;
	i[0] =  (m[4]*m[8] - m[7]*m[5]) * invdev;
	i[1] = -(m[1]*m[8] - m[7]*m[2]) * invdev;
	i[2] =  (m[1]*m[5] - m[4]*m[2]) * invdev;

	i[3] = -(m[3]*m[8] - m[6]*m[5]) * invdev;
	i[4] =  (m[0]*m[8] - m[6]*m[2]) * invdev;
	i[5] = -(m[0]*m[5] - m[3]*m[2]) * invdev;

	i[6] =  (m[3]*m[7] - m[6]*m[4]) * invdev;
	i[7] = -(m[0]*m[7] - m[6]*m[1]) * invdev;
	i[8] =  (m[0]*m[4] - m[3]*m[1]) * invdev;
	return true;
}
//COLUMN MAJOR
typedef struct _Matrix33
{
	/**
	in memory this should look like 
	[x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z]
	[0  ,1  ,2  ,3  ,4  ,5  ,6  ,7  ,8]
	if you are accessing the vector classes
	*/
	union
	{
		float data[9];
		struct
		{
			float array[3][3];
		};
		struct
		{
			CVec3df x,y,z;
		};

	};	
	bool operator ==(const _Matrix33& rhs)const
	{
		return (data[0]==rhs.data[0] && data[2]==rhs.data[2] && data[3]==rhs.data[3] &&
				data[4]==rhs.data[4] && data[5]==rhs.data[5] && data[6]==rhs.data[6] &&
				data[7]==rhs.data[7] && data[8]==rhs.data[8]);
	}
}Matrix33;

class CMatrix33 : public Matrix33
{
public : 
	enum VEC
	{
		COL_X,COL_Y,COL_Z,
		ROW_X,ROW_Y,ROW_Z,
	};
	
	// Initialisation
	CMatrix33( const bool bIdentity = true)
	{
		if ( bIdentity ) Identity();
	}
	CMatrix33(Vec3df& x,Vec3df& y,Vec3df& z)
	{
		this->x = x;		this->y = y;		this->z = z;

	}
	/*CMatrix33(CVec3df& x,CVec3df& y,CVec3df& z)
	{
		this->x = x;		this->y = y;		this->z = z;
	}
	*/
	void Identity( );

	// Accessors unchecked!
	inline const float& operator() ( int col, int row) const
	{		return this->data[(col*3)+row];	}
	inline float& operator() ( int col, int row)
	{		return this->data[(col*3)+row];	}

	inline const float& operator() ( int item) const
	{		return this->data[item];	}
	inline float& operator() ( int item)
	{		return this->data[item];	}
	inline const float& operator[] ( int item) const 
	{		return this->data[item];	}
	inline float& operator[] ( int item)
	{		return this->data[item];	}

	// Multiplication
	CMatrix33	operator*(const CMatrix33 &rhs) const;
	CMatrix33&	operator*=(const CMatrix33 &rhs);
	CMatrix33&	operator*(const float&rhs) const;
	CMatrix33&	operator*=(const float&rhs);

	// Concatenate 2 matrices with the * operator
	CMatrix33& operator=(const CMatrix44& rhs)
	{
		data[0]  = rhs.data[0]; 		
		data[1]  = rhs.data[1];		
		data[2]  = rhs.data[2];

		data[3]  = rhs.data[4];
		data[4]  = rhs.data[5];		
		data[5]  = rhs.data[6];

		data[6]  = rhs.data[8];
		data[7]  = rhs.data[9];
		data[8]  = rhs.data[10];
		return *this;
	}

	// Use a matrix to transform a 3D point with the * operator
	inline CVec3df operator* (const Vec3df &Point ) const
	{
		float x = Point.x*data[0] + Point.y*data[3] + Point.z*data[6];
		float y = Point.x*data[1] + Point.y*data[4] + Point.z*data[7];
		float z = Point.x*data[2] + Point.y*data[5] + Point.z*data[8]; 
		return CVec3df( x, y, z );
	}

	// and rhs to this matrix
	inline void operator+= (const CMatrix33 &rhs )
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
	}

	// Rotate the *this matrix fDegrees counter-clockwise around a single axis( either x, y, or z )
	void Rotate( float fDegrees, int x, int y, int z )
	{
		CMatrix33 Temp;
		if (x == 1) Temp.RotX( fDegrees );
		if (y == 1) Temp.RotY( fDegrees );
		if (z == 1) Temp.RotZ( fDegrees );
		*this = Temp * (*this);
	}

	void Scale( float sx, float sy, float sz )
	{
		int x;
		for (x = 0; x <  3; x++) data[x]*=sx;
		for (x = 3; x <  6; x++) data[x]*=sy;
		for (x = 6; x <  9; x++) data[x]*=sz;
	}	

	//OpenGL is Coloumn-Major:
	//  |  X   Y   Z   T
 	// x| m0  m4  m8  m12 
	// y| m1  m5  m9  m13
	// z| m2  m6  m10 m14
	// t| m3  m7  m11 m15
	CVec3df  GetVec( VEC vec)
	{
		switch (vec)
		{
		default:
		case COL_X:
			return CVec3df( data[0], data[1], data[2] );
			break;
		case COL_Y:
			return CVec3df( data[3], data[4], data[5] );
			break;
		case COL_Z:
			return CVec3df( data[6], data[7], data[8] );
			break;
		case ROW_X:
			return CVec3df( data[0], data[3], data[6] );
			break;
		case ROW_Y:
			return CVec3df( data[1], data[4], data[7] );
			break;
		case ROW_Z:
			return CVec3df( data[2], data[5], data[8] );
			break;
		}
	}
	
	// Create a rotation matrix for a counter-clockwise rotation of fDegrees around an arbitrary axis(x, y, z)
	void RotateMatrix( float fDegrees, float x, float y, float z)
	{
		Identity();
		float cosA = cosf(fDegrees*TO_RAD);
		float sinA = sinf(fDegrees*TO_RAD);

		float m = 1.0f - cosA;
		data[0] = cosA + x*x*m;
		data[4] = cosA + y*y*m;
		data[8] = cosA + z*z*m;

		float tmp1 = x*y*m;
		float tmp2 = z*sinA;
		data[3] = tmp1 + tmp2;
		data[1] = tmp1 - tmp2;

		tmp1 = x*z*m;
		tmp2 = y*sinA;
		data[6] = tmp1 - tmp2;
		data[2] = tmp1 + tmp2;

		tmp1 = y*z*m;
		tmp2 = x*sinA;
		data[7] = tmp1 + tmp2;
		data[5] = tmp1 - tmp2;
	}

	// Transpose
	CMatrix33 Transpose( )
	{
		CMatrix33 R( 0 );
		R.data[0]  = data[0]; 		R.data[1]  = data[3];		R.data[2]  = data[6];
		R.data[3]  = data[1];		R.data[4]  = data[4];		R.data[5]  = data[7];
		R.data[6]  = data[2];		R.data[7]  = data[5];		R.data[8]  = data[8];
		return R;
	}	

	inline CMatrix33 Invert()
	{
		CMatrix33 R(0);
		GenerateInverseMatrix3f(R.data,data);
		return R;
	}

private:
	// helpers for Rotate
	void RotX(float angle)
	{  
		data[4]  = cosf(angle*TO_RAD);
		data[5]  = sinf(angle*TO_RAD);
		data[7]  = -sinf(angle*TO_RAD);
		data[8]  = cosf(angle*TO_RAD);
	}

	void RotY(float angle)
	{
		data[0]  =  cosf(angle*TO_RAD);
		data[2]  =  -sinf(angle*TO_RAD);
		data[6]  =  sinf(angle*TO_RAD);
		data[8]  =  cosf(angle*TO_RAD);    
	}

	void RotZ(float angle)
	{
		data[0] =  cosf(angle*TO_RAD);
		data[1] =  sinf(angle*TO_RAD);
		data[3] =  -sinf(angle*TO_RAD);
		data[4] =  cosf(angle*TO_RAD);
	}
};

inline CMatrix33 operator*(const float s, CMatrix33& rhs)
{
	return CMatrix33(rhs.x*s,rhs.y*s,rhs.z*s);
}

#include "matrix33_inl.h"

#endif _MATRIX33PP_H_