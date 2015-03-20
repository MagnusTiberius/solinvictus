#ifndef _VEC2DIPP_H_
#define _VEC2DIPP_H_

#include "math.h"


// Data structure
typedef struct _Vec2di
{
	union
	{
		int data[2];
		struct
		{
			int x,y;
		};
		struct
		{
			int width, height;
		};
	};	
}Vec2di;

class CVec2di : public Vec2di
{
public:
	CVec2di(){	x = y = 0;	}

	CVec2di(int x,int y) 
	{
		this->x = x; this->y = y;
	}

	// accessors unchecked!
	inline int& operator[](const int i)
	{	return this->data[i];	}
	inline const int& operator[](const int i) const
	{	return this->data[i];	}

	inline int& operator()(const int i)
	{	return this->data[i];	}
	inline const int& operator()(const int i) const
	{	return this->data[i];	}

	// operators
	bool		operator==(const CVec2di& rhs) const;	

	// Addition
	CVec2di		operator+(const CVec2di& rhs) const;
	CVec2di&	operator+=(const CVec2di& rhs);
	
	// Subtraction
	CVec2di		operator-(const CVec2di& rhs) const;
	CVec2di		operator-() const;
	CVec2di&	operator-=(const CVec2di& rhs);

	// Multiplication
	CVec2di		operator*(const CVec2di& rhs) const;
	CVec2di		operator*(const int s) const;
	CVec2di&	operator*=(const int s);
	CVec2di&	operator*=(const CVec2di& rhs);

	// Division
	CVec2di		operator/(const CVec2di& rhs) const;
	CVec2di		operator/(const int s) const;
	CVec2di&	operator/=(const CVec2di& rhs);
	CVec2di&	operator/=(const int s);

	//Normalization
	//CVec2di&	Normalize();
	//CVec2di		GetNormalized();

	// Misc
	int		Dot(const CVec2di& rhs) const;
	int		Distance(const CVec2di& rhs) const;
	int		Mag(void) const;
	int		Mag2(void) const;
};

#include "vec2di_inl.h"

#endif _VEC2DIPP_H_