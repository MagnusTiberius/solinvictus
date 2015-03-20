#ifndef _VEC2DFPP_H_
#define _VEC2DFPP_H_

#include "math.h"


// Data structure
typedef struct _Vec2df
{
	union
	{
		float data[2];
		struct
		{
			float x,y;
		};
	};	
	bool operator ==(const _Vec2df rhs)const
	{
		return (x==rhs.x && y==rhs.y);
	}
	/*
	_Vec2df operator =(const _Vec2df rhs)
	{
		x=rhs.x;
		y=rhs.y;
		return *this;
	}
	*/
}Vec2df;

class CVec2df : public _Vec2df
{
public:
	CVec2df(){	x = y = 0;	}
	CVec2df(float value){	x = y = value;	}
	CVec2df(float x,float y) 
	{
		this->x = x; this->y = y;
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

	// operators
	bool		operator==(const CVec2df& rhs) const;	

	// Addition
	CVec2df		operator+(const CVec2df& rhs) const;
	CVec2df&	operator+=(const CVec2df& rhs);
	
	// Subtraction
	CVec2df		operator-(const CVec2df& rhs) const;
	CVec2df		operator-() const;
	CVec2df&	operator-=(const CVec2df& rhs);

	// Multiplication
	CVec2df		operator*(const CVec2df& rhs) const;
	CVec2df		operator*(const float s) const;
	CVec2df&	operator*=(const float s);
	CVec2df&	operator*=(const CVec2df& rhs);

	// Division
	CVec2df		operator/(const CVec2df& rhs) const;
	CVec2df		operator/(const float s) const;
	CVec2df&	operator/=(const CVec2df& rhs);
	CVec2df&	operator/=(const float s);

	//Normalization
	CVec2df&	Normalize();
	CVec2df		GetNormalized() const;

	inline CVec2df		GetPerp()const
	{
		//clockwise winding
		//return CVec2df(-y,x);
		//anti-clockwise winding
		return CVec2df(y,-x);
	}

	// Misc
	float		Cross(const CVec2df& rhs) const;
	float		Dot(const CVec2df& rhs) const;
	float		Distance(const CVec2df& rhs) const;
	float		Mag(void) const;
	float		Mag2(void) const;
};

#include "vec2df_inl.h"

#endif _VEC2DFPP_H_