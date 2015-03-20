#ifdef _MATRIX33PP_H_

inline void CMatrix33::Identity( )
{
	data[ 0] = 1.0f;    data[ 3] = 0.0f;      data[ 6] = 0.0f;
	data[ 1] = 0.0f;    data[ 4] = 1.0f;      data[ 7] = 0.0f;
	data[ 2] = 0.0f;    data[ 5] = 0.0f;      data[ 8] = 1.0f;		
}


//openGL is column major
//"this" is the LHs and so we use it's rows
inline CMatrix33 CMatrix33::operator*(const CMatrix33 &rhs) const
{
	static CMatrix33 result;
	for (int i=0;i<9;i+=3)
	{
		for (int j=0;j<3;j++)
		{
			result.data[i + j] =	data[j  ] * rhs.data[i  ] 
								+	data[j+3] * rhs.data[1+i]
								+	data[j+6] * rhs.data[2+i];
		}
	}
	return result;
}

inline CMatrix33& CMatrix33::operator*=(const CMatrix33 &rhs)
{
	static CMatrix33 result;
	for (int i=0;i<9;i+=3)
	{
		for (int j=0;j<3;j++)
		{
			result.data[i + j] =	data[j  ] * rhs.data[i  ] 
								+	data[j+3] * rhs.data[1+i]
								+	data[j+6] * rhs.data[2+i];
		}
	}
	*this = result;
	return *this;
}


inline CMatrix33& CMatrix33::operator*(const float &rhs) const
{
	static CMatrix33 result;
	for (int i=0;i<9;i++)
		result.data[i] = data[i] * rhs;
	return result;
}

inline CMatrix33& CMatrix33::operator*=(const float &rhs)
{
	for (int i=0;i<9;i++)
		data[i] = data[i] * rhs;	
	return *this;
}

#endif