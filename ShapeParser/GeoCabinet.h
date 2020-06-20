#pragma once
#include "GeoPlank.h"
GEO_NAMESPACE_START

class GeoCabinet :public GeoAttr, public GeoInfo, public GeoTag, public GeoLua
{
public:
	std::vector<GeoPlank*> planks;
};

GEO_NAMESPACE_END