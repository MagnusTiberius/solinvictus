#ifdef _VEC2DIPP_H_


inline bool CVec2di::operator==(const CVec2di& rhs) const
{
	if(x == rhs.x && y == rhs.y)
		return true;	
	return false;		
}

// Addition
inline CVec2di CVec2di::operator+(const CVec2di& rhs) const
{
	return CVec2di(x+rhs.x,y+rhs.y);
}
inline CVec2di& CVec2di::operator+=(const CVec2di& rhs)
{
	*this = *this + rhs;
	return *this;
}

// Subtractioon
inline CVec2di CVec2di::operator-(const CVec2di& rhs) const
{
	return CVec2di(x-rhs.x,y-rhs.y);
}
inline CVec2di CVec2di::operator-() const
{
	return CVec2di(-x,-y);
}
inline CVec2di& CVec2di::operator-=(const CVec2di& rhs)
{
	*this = *this - rhs;
	return *this;
}

// Multiplication
inline CVec2di CVec2di::operator*(const CVec2di& rhs) const
{
	return CVec2di(x*rhs.x,y*rhs.y);
}
inline CVec2di CVec2di::operator*(const int s) const
{
	return CVec2di(x*s,y*s);
}
inline CVec2di& CVec2di::operator*=(const int s)
{
	x*=s;	y*=s;		
}
inline CVec2di& CVec2di::operator*=(const CVec2di& rhs)
{
	*this = (*this) * rhs;		
}

//Division
inline CVec2di CVec2di::operator/(const CVec2di& rhs) const
{
	return CVec2di(x/rhs.x,y/rhs.y);
}
inline CVec2di CVec2di::operator/(const int s) const
{
	return CVec2di(x/s,y/s);
}
inline CVec2di& CVec2di::operator/=(const CVec2di& rhs)
{
	x/=rhs.x;
	y/=rhs.y;
	return *this;
}
inline CVec2di& CVec2di::operator/=(const int s)
{
	x/=s;
	y/=s;
	return *this;
}

// Misc
inline int CVec2di::Dot(const CVec2di& rhs) const
{
	return ((x*rhs.x)+(y*rhs.y));
}
inline int CVec2di::Distance(const CVec2di& rhs) const
{
	return ( *this - rhs ).Mag();	
}
inline int CVec2di::Mag(void) const
{
	return (int)sqrt((float)((x*x)+(y*y)));
}
inline int CVec2di::Mag2(void) const
{
	return (x*x)+(y*y);
}
/*
_Vec2df operator =(_Vec2df& lhs, const CVec2df& rhs)
{
	lhs.x=rhs.x;
	lhs.y=rhs.y;
	return lhs;
}*/

#endif //_VEC2DFPP_H_