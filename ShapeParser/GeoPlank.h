#pragma once
#include "GeoShape.h"
GEO_NAMESPACE_START

//环
struct GeoRing
{
	int depth{ 0 };
	int ring{ 0 };
	int ring_depth{ 0 };
};

//槽
struct GeoSlot : public GeoAttr, GeoRing
{
	GeoPoint start;
	GeoPoint end;
	unsigned int width{ 0 };
};

//孔
struct GeoHole : public GeoAttr, GeoRing
{
	GeoPoint center;
	unsigned int radius;
};

//造型
struct GeoMill :public GeoShape, GeoRing {};

//造型线
struct GeoOrbit :public GeoShape, GeoRing {};

//板
class GeoPlank :public GeoShape
{
public:
	std::vector<GeoSlot> slot;
	std::vector<GeoHole> hole;
	std::vector<GeoMill> mill;
	std::vector<GeoOrbit> orbit;
};

GEO_NAMESPACE_END
