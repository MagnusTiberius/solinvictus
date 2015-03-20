#ifdef _VEC2DFPP_H_


inline bool CVec2df::operator==(const CVec2df& rhs) const
{
	if(x == rhs.x && y == rhs.y)
		return true;	
	return false;		
}

// Addition
inline CVec2df CVec2df::operator+(const CVec2df& rhs) const
{
	return CVec2df(x+rhs.x,y+rhs.y);
}
inline CVec2df& CVec2df::operator+=(const CVec2df& rhs)
{
	*this = *this + rhs;
	return *this;
}

// Subtractioon
inline CVec2df CVec2df::operator-(const CVec2df& rhs) const
{
	return CVec2df(x-rhs.x,y-rhs.y);
}
inline CVec2df CVec2df::operator-() const
{
	return CVec2df(-x,-y);
}
inline CVec2df& CVec2df::operator-=(const CVec2df& rhs)
{
	*this = *this - rhs;
	return *this;
}

// Multiplication
inline CVec2df CVec2df::operator*(const CVec2df& rhs) const
{
	return CVec2df(x*rhs.x,y*rhs.y);
}
inline CVec2df CVec2df::operator*(const float s) const
{
	return CVec2df(x*s,y*s);
}
inline CVec2df& CVec2df::operator*=(const float s)
{
	x*=s;	y*=s;		
	return *this;
}
inline CVec2df& CVec2df::operator*=(const CVec2df& rhs)
{
	return *this = (*this) * rhs;		
}

//Division
inline CVec2df CVec2df::operator/(const CVec2df& rhs) const
{
	return CVec2df(x/rhs.x,y/rhs.y);
}
inline CVec2df CVec2df::operator/(const float s) const
{
	return CVec2df(x/s,y/s);
}
inline CVec2df& CVec2df::operator/=(const CVec2df& rhs)
{
	x/=rhs.x;
	y/=rhs.y;
	return *this;
}
inline CVec2df& CVec2df::operator/=(const float s)
{
	x/=s;
	y/=s;
	return *this;
}

// Normalization
inline CVec2df& CVec2df::Normalize()
{
	float length = (float)sqrt(((x*x)+(y*y)));
	if(length > 0)
	{
		x /= length;
		y /= length;
	}
	return *this;
}
inline CVec2df CVec2df::GetNormalized() const
{
	float length = (float)sqrt(((x*x)+(y*y)));
	if(length > 0)
	{
		return CVec2df(x/length,y/length);
	}
	return CVec2df(1.0f,0);
}

// Misc
inline float CVec2df::Cross(const CVec2df& rhs) const
{
	return this->y*rhs.x - this->x*rhs.y; 
}

inline float CVec2df::Dot(const CVec2df& rhs) const
{
	return ((x*rhs.x)+(y*rhs.y));
}
inline float CVec2df::Distance(const CVec2df& rhs) const
{
	return ( *this - rhs ).Mag();	
}
inline float CVec2df::Mag(void) const
{
	return (float)sqrt(((x*x)+(y*y)));
}
inline float CVec2df::Mag2(void) const
{
	return (x*x)+(y*y);
}

//-------------------------------------------------------------------
// Helper functions
inline CVec2df  operator*(const float s, const CVec2df& rhs)
{
	return CVec2df(rhs.x*s , rhs.y*s);
}



#endif //_VEC2DFPP_H_