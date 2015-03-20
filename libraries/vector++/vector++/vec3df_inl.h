//vec3df++.h support file as it is getting too messy and long

#ifdef _VEC3DFPP_H_
//-------------------------------------------------------------------
// Vec3df Methods
//-------------------------------------------------------------------

inline CVec3df& CVec3df::operator=(const Vec3df& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

inline bool CVec3df::operator==(const CVec3df& rhs) const
{
	if(x == rhs.x && y == rhs.y && z == rhs.z)
		return true;
	return false;
}

// Addition

inline CVec3df CVec3df::operator+(const CVec3df& rhs) const
{
	return CVec3df(x+rhs.x,y+rhs.y,z+rhs.z);
}
inline CVec3df& CVec3df::operator+=(const CVec3df& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

// Subtraction

inline CVec3df CVec3df::operator-(const CVec3df& rhs) const
{
	return CVec3df(x-rhs.x,y-rhs.y,z-rhs.z);
}
inline CVec3df CVec3df::operator-() const
{
	return CVec3df(-x,-y,-z);
}
inline CVec3df& CVec3df::operator-=(const CVec3df& rhs)
{
	x-=rhs.x;
	y-=rhs.y;
	z-=rhs.z;
	return *this;
}

// Multiplication

inline CVec3df CVec3df::operator*(const CVec3df& rhs) const
{
	return CVec3df(x*rhs.x,y*rhs.y,z*rhs.z);
}

inline CVec3df CVec3df::operator*(const float s) const
{
	return CVec3df(x*s,y*s,z*s);
}
inline CVec3df& CVec3df::operator*=(const CVec3df& rhs)
{
	*this = (*this) * rhs;		
	return *this;
}
inline CVec3df& CVec3df::operator*=(const float s)
{
	x*=s;	y*=s;	z*=s;		
	return *this;
}
inline CVec3df& CVec3df::operator*=(const float m[9])
{
	this->x = this->x*m[0] + this->y*m[3] + this->z*m[6];
	this->y = this->x*m[1] + this->y*m[4] + this->z*m[7];
	this->z = this->x*m[2] + this->y*m[5] + this->z*m[8];
	return *this;
}

// Division

inline CVec3df CVec3df::operator/(const CVec3df& rhs) const
{
	return CVec3df(x/rhs.x,y/rhs.y,z/rhs.z);
}
inline CVec3df CVec3df::operator/(const float s) const
{
	return CVec3df(x/s,y/s,z/s);
}
inline CVec3df& CVec3df::operator/=(const float s)
{
	*this = (*this) / s;
	return *this;
}
inline CVec3df& CVec3df::operator/=(CVec3df& rhs)
{
	*this = (*this) / rhs;
	return *this;
}

// Normals

inline CVec3df& CVec3df::Normalize()
{
	float length = (float)sqrt((x*x)+(y*y)+(z*z));
	if(length > 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	return *this;
}
inline CVec3df CVec3df::GetNormalized() const
{
	float length = (float)sqrt((x*x)+(y*y)+(z*z));
	if(length > 0)
	{
		return CVec3df(
		x / length,
		y / length,
		z / length
		);
	}
	return CVec3df(1,0,0);
}	



// Misc

inline float CVec3df::Dot(const CVec3df& rhs) const
{
	return ((x*rhs.x)+(y*rhs.y)+(z*rhs.z));
}

inline CVec3df CVec3df::Cross(const CVec3df& rhs) const
{
	//middle component should be negated!
	//u X v  =	 (u2v3-u3v2),
	//			-(u1v3 - u3v1),
	//			 (u1v2-u2v1)
	return CVec3df(
				(this->y*rhs.z) - (this->z*rhs.y),
				-((this->x*rhs.z) - (this->z*rhs.x)),
				(this->x*rhs.y) - (this->y*rhs.x)
				);
}
inline float CVec3df::Distance(const CVec3df& rhs) const
{
	return ( *this - rhs ).Mag();	
}

//-------------------------------------------------------------------
// Helper functions
inline CVec3df  operator*(const float s, const CVec3df& rhs)
{
	return CVec3df(rhs.x*s , rhs.y*s , rhs.z*s);
}

inline CVec3df Cross(const CVec3df& rhs, const CVec3df& lhs)
{
	return rhs.Cross(lhs);
}

inline float Dot(const CVec3df& rhs, const CVec3df& lhs)
{
	return rhs.Dot(lhs);
}

inline void Normalize(CVec3df& vec)
{
	vec.Normalize();
}

inline CVec3df GetNormalized(const CVec3df& vec)
{
	return vec.GetNormalized();
}

#endif //_VEC3DFPP_H_