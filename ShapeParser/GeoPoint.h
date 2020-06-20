#pragma once
#include "GeoDecl.h"
GEO_NAMESPACE_START
// xyz a is start point width angle 
struct GeoPoint
{
	cInt x{ 0 };
	cInt y{ 0 };
	cInt z{ 0 };
	cInt a{ 0 };
	bool operator==(GeoPoint pt)
	{
		return x == pt.x && y == pt.y && z == pt.z && a == pt.a;
	}

	cInt& operator[](int index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return a;
		}
	}

};
GEO_NAMESPACE_END