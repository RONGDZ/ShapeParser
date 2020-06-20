#pragma once
#include "GeoDecl.h"

GEO_NAMESPACE_START
class GeoCabinet;
class GeoPlank;
class GeoShape;
class GeoCanvas;
class GeoWhole
{
public:
	~GeoWhole();
public:
	std::map<std::string, std::string> info;
	std::vector<GeoCabinet*> cabinets;
	std::vector<GeoShape*> shapes;
	std::vector<GeoPlank*> planks;
	GeoCanvas* canvas;
};

GEO_NAMESPACE_END
