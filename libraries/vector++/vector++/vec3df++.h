#ifndef _VEC3DFPP_H_
#define _VEC3DFPP_H_

#include "math.h"
#include "vec2df++.h"

//----------------------------------------------------------------
// Vector Data Structure

typedef struct _Vec3df
{
	union
	{
		float data[3];
		struct
		{
			float x,y,z;
		};

	};	
	bool operator ==(const _Vec3df rhs)const
	{
		return (x==rhs.x && y==rhs.y && z==rhs.z);
	}

	_Vec3df operator +(const _Vec3df& rhs)const
	{
		_Vec3df tmp;
		tmp.x = x + rhs.x;
		tmp.y = y + rhs.y;
		tmp.z = z + rhs.z;
		return tmp;
	}

	_Vec3df operator *(const float& f)const
	{
		_Vec3df tmp;
		tmp.x = x * f;
		tmp.y = y * f;
		tmp.z = z * f;
		return tmp;
	}
}Vec3df;

//----------------------------------------------------------------
// Vector Class 
class CVec3df : public Vec3df
{
public:
	CVec3df()	
	{	
		x = y = z = 0.0f;	
	}

	CVec3df(float value)
	{
		x = y = z = value;
	}

	CVec3df(const Vec2df& value)
	{
		x = value.x;
		y = value.y;
		z = 0.0f;
	}

	CVec3df(const Vec3df& value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
	}

	CVec3df(float x,float y,float z)
	{
		this->x = x; this->y = y; this->z = z;
	}

	// accessors unchecked!
	inline float& operator[](const int i)
	{	return this->data[i];	}
	inline const float& operator[](const int i) const
	{	return this->data[i];	}

	inline float& operator()(const int i)
	{	return this->data[i];	}
	inline const float& operator()(const int i) const
	{	return this->data[i];	}

	//---operators---
	CVec3df&	operator=(const Vec3df& rhs);	
	bool		operator==(const CVec3df& rhs) const;	

	// Addition
	CVec3df		operator+(const CVec3df& rhs) const;
	CVec3df&	operator+=(const CVec3df& rhs);	

	// Subtraction
	CVec3df		operator-(const CVec3df& rhs) const;
	CVec3df		operator-() const;
	CVec3df&	operator-=(const CVec3df& rhs);

	// Multiplication
	CVec3df		operator*(const CVec3df& rhs) const;
	CVec3df		operator*(const float s) const;
	CVec3df&	operator*=(const CVec3df& rhs);
	CVec3df&	operator*=(const float s);
	CVec3df&	operator*=(const float m[9]);
	
	// Division
	CVec3df		operator/(const CVec3df& rhs) const;
	CVec3df		operator/(const float s) const;
	CVec3df&	operator/=(const float s);
	CVec3df&	operator/=(CVec3df& rhs);

	// Normals
	CVec3df&	Normalize();
	CVec3df		GetNormalized() const;	

	// Quaternions
	//CVec3df		operator=(const CQuat& rhs);


	// Misc
	float		Dot(const CVec3df& rhs)		const;
	CVec3df		Cross(const CVec3df& rhs)		const;
	float		Distance(const CVec3df& rhs)	const;

	//Magnitude and Magnitude Squared
	float		Mag(void) const{	return (float)sqrt((x*x)+(y*y)+(z*z));	}
	float		Mag2(void) const{	return (x*x)+(y*y)+(z*z); }
};

#include "vec3df_inl.h"

#endif