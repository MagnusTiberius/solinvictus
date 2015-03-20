#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "vec3df++.h"

const float TO_HALF_RAD = 3.14159265f / 360.0f;

struct Quat
{
	union
	{
		float data[4];
		struct
		{
			float x,y,z,w;
		};
	};
};

class CQuat : public Quat
{
public:

	CQuat()
	{x=0; y=0; z=0; w=1;}

	CQuat(float fx, float fy, float fz, float fw)
	{x=fx; y=fy; z=fz; w=fw;}

	CQuat(CVec3df vec)
	{x=vec.x; y=vec.y; z=vec.z; w=0;}
	
	CQuat(float angle, const CVec3df& axis)
	{
		SetAxis( angle, axis.x, axis.y, axis.z );
	}

	// No rotation
	void Reset()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1.0f;
	}

	// Set Quat from axis-angle
	void SetAxis( float degrees, float fX, float fY, float fZ )
	{
		float HalfAngle = degrees * TO_HALF_RAD; // Get half angle in radians from angle in degrees
		float sinA = (float)sin( HalfAngle ) ;
		w = (float)cos( HalfAngle );
		x = fX * sinA;
		y = fY * sinA;
		z = fZ * sinA;
	}

	CQuat Invert( ) const
	{
		return CQuat( -x, -y, -z, w );
	}

	CQuat Negate( ) const{ return CQuat( -x, -y, -z, -w );}

	// Note that order matters with concatenating Quaternion rotations
	inline CQuat operator* (const CQuat &rhs) const
	{
		CQuat r;
		r.w = w*rhs.w - x*rhs.x  -  y*rhs.y  -  z*rhs.z;
		r.x = w*rhs.x + x*rhs.w  +  y*rhs.z  -  z*rhs.y;
		r.y = w*rhs.y + y*rhs.w  +  z*rhs.x  -  x*rhs.z;
		r.z = w*rhs.z + z*rhs.w  +  x*rhs.y  -  y*rhs.x;
		return r;
	}

	// Note that order matters with concatenating Quaternion rotations
	inline CQuat operator*= (const CQuat &rhs)
	{
		*this = *this*rhs;
		return *this;
	}

	//set the w component of rhs to 0
	inline CQuat operator* (const CVec3df &rhs) const
	{
		CQuat r;
		r.w = -x*rhs.x-  y*rhs.y  -  z*rhs.z;
		r.x = w*rhs.x +  y*rhs.z  -  z*rhs.y;
		r.y = w*rhs.y +  z*rhs.x  -  x*rhs.z;
		r.z = w*rhs.z +  x*rhs.y  -  y*rhs.x;
		return r;
	}
	
	// You could add an epsilon to this equality test if needed
	inline bool operator== ( const CQuat &b ) const
	{
		return (x == b.x && y == b.y && z == b.z && w == b.w);
	}

	int IsIdentity( ) const
	{
		return (x == 0.0f && y == 0.0f && z == 0.0f && w==1.0f);
	}

	// Can be used the determine Quaternion neighbourhood
	float Dot( const CQuat& a ) const
	{
		return x * a.x + y * a.y + z * a.z + w * a.w;
	}

	// Scalar multiplication
	CQuat operator*( float s ) const
	{
		return CQuat(x * s, y * s, z * s, w * s );
	}

	// Addition
	CQuat operator+ ( const CQuat& b ) const
	{
		return CQuat( x + b.x, y + b.y, z + b.z, w + b.w );
	}

	// ------------------------------------
	// Simple Euler Angle to Quaternion conversion, this could be made faster
	// ------------------------------------
	void FromEuler( float rx, float ry, float rz )
	{
		CQuat qx(-rx, CVec3df( 1, 0, 0 ) );
		CQuat qy(-ry, CVec3df( 0, 1, 0 ) );
		CQuat qz(-rz, CVec3df( 0, 0, 1 ) );
		qz = qy * qz;
		*this = qx * qz;
	}

	// ------------------------------------
	// Quaternions store scale as well as rotation, but usually we just want rotation, so we can normalize.
	// ------------------------------------
	int Normalize( )
	{
		float lengthSq = x * x + y * y + z * z + w * w;

		if (lengthSq == 0.0 ) return -1;
		if (lengthSq != 1.0 )
			{
			float scale = ( 1.0f / sqrtf( lengthSq ) );
			x *= scale;
			y *= scale;
			z *= scale;
			w *= scale;
			return 1;
			}
		return 0;
	}

	// ------------------------------------
	// Creates a value for this Quaternion from spherical linear interpolation
	// t is the interpolation value from 0 to 1
	// ------------------------------------
	void Slerp(const CQuat& a, const CQuat& b, float t)
	{
	  float w1, w2;

	  float cosTheta = a.Dot(b);
	  float theta    = (float)acos(cosTheta);
	  float sinTheta = (float)sin(theta);

	  if( sinTheta > 0.001f )
	  {
		w1 = float( sin( (1.0f-t)*theta ) / sinTheta);
		w2 = float( sin( t*theta) / sinTheta);
	  } else {
		// CQuat a ~= CQuat b
		w1 = 1.0f - t;
		w2 = t;
	  }

	  *this = a*w1 + b*w2;
	}

	// ------------------------------------
	// linearly interpolate each component, then normalize the Quaternion
	// Unlike spherical interpolation, this does not rotate at a constant velocity,
	// although that's not necessarily a bad thing
	// ------------------------------------
	void NLerp( const CQuat& a, const CQuat& b, float w2)
	{
	float w1 = 1.0f - w2;

	*this = a*w1 + b*w2;
	Normalize();
	}

	// ------------------------------------
	// Set a 4x4 matrix with the rotation of this Quaternion
	// ------------------------------------
	void inline ToMatrix( float mf[16] ) const
	{
		float x2 = 2.0f * x,  y2 = 2.0f * y,  z2 = 2.0f * z;

		float xy = x2 * y,  xz = x2 * z;
		float yy = y2 * y,  yw = y2 * w;
		float zw = z2 * w,  zz = z2 * z;

		mf[ 0] = 1.0f - ( yy + zz );
		mf[ 4] = ( xy - zw );
		mf[ 8] = ( xz + yw );
		mf[12] = 0.0f;

		float xx = x2 * x,  xw = x2 * w,  yz = y2 * z;

		mf[ 1] = ( xy +  zw );
		mf[ 5] = 1.0f - ( xx + zz );
		mf[ 9] = ( yz - xw );
		mf[13] = 0.0f;

		mf[ 2] = ( xz - yw );
		mf[ 6] = ( yz + xw );
		mf[10] = 1.0f - ( xx + yy );  
		mf[14] = 0.0f;  

		mf[ 3] = 0.0f;  
		mf[ 7] = 0.0f;   
		mf[11] = 0.0f;   
		mf[15] = 1.0f;
	}

	// ------------------------------------
	// Set a 3x3 matrix with the rotation of this Quaternion
	// ------------------------------------
	void inline ToMatrix33( float mf[9] ) const
	{
		float x2 = 2.0f * x,  y2 = 2.0f * y,  z2 = 2.0f * z;

		float xy = x2 * y,  xz = x2 * z;
		float yy = y2 * y,  yw = y2 * w;
		float zw = z2 * w,  zz = z2 * z;

		mf[ 0] = 1.0f - ( yy + zz );
		mf[ 3] = ( xy - zw );
		mf[ 6] = ( xz + yw );		

		float xx = x2 * x,  xw = x2 * w,  yz = y2 * z;

		mf[ 1] = ( xy +  zw );
		mf[ 4] = 1.0f - ( xx + zz );
		mf[ 7] = ( yz - xw );		

		mf[ 2] = ( xz - yw );
		mf[ 5] = ( yz + xw );
		mf[ 8] = 1.0f - ( xx + yy );  		
	}

	// ------------------------------------
	// Set this Quat to aim the Z-Axis along the vector from P1 to P2
	// ------------------------------------
	void AimZAxis( const CVec3df& P1, const CVec3df& P2 )
	{
		CVec3df vAim = P2 - P1;
		vAim.Normalize();

		x = vAim.y;
		y = -vAim.x;
		z = 0.0f;
		w = 1.0f + vAim.z;

		if (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f) 
			*this = CQuat( 0, 1, 0, 0 ); // If we can't normalize it, just set it
		else
			Normalize();
	}
};

inline CQuat operator*(const CVec3df& lhs, CQuat& rhs)
{
	CQuat temp(lhs);
	return temp*rhs;
}


#endif _QUATERNION_H_