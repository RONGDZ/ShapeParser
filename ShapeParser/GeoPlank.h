#pragma once
#include "GeoShape.h"
GEO_NAMESPACE_START

//��
struct GeoRing
{
	int depth{ 0 };
	int ring{ 0 };
	int ring_depth{ 0 };
};

//��
struct GeoSlot : public GeoAttr, GeoRing
{
	GeoPoint start;
	GeoPoint end;
	unsigned int width{ 0 };
};

//��
struct GeoHole : public GeoAttr, GeoRing
{
	GeoPoint center;
	unsigned int radius;
};

//����
struct GeoMill :public GeoShape, GeoRing {};

//������
struct GeoOrbit :public GeoShape, GeoRing {};

//��
class GeoPlank :public GeoShape
{
public:
	std::vector<GeoSlot> slot;
	std::vector<GeoHole> hole;
	std::vector<GeoMill> mill;
	std::vector<GeoOrbit> orbit;
};

GEO_NAMESPACE_END
