#pragma once
#include "GeoShape.h"
GEO_NAMESPACE_START

class GeoCanvas:public GeoAttr,GeoTag,GeoInfo
{
public:
	std::vector<GeoShape*> shapes;
};

GEO_NAMESPACE_END