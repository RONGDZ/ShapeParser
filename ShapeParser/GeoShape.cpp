#include "GeoShape.h"

GEO_NAMESPACE_START

GeoShape::GeoShape(std::string name)
	:m_name(name)
	, min_x(0)
	, min_y(0)
	, max_x(0)
	, max_y(0)
	, w(0)
	, h(0)
{
}

void GeoShape::geo(std::vector<GeoPoint>& outline, std::string xyza)
{
	m_xyza = xyza;
	m_outline.clear();
	size_t sz = outline.size();
	if (0 == sz) return;
	min_x = outline[0].x;
	min_y = outline[0].y;
	max_x = min_x;
	max_y = min_y;
	m_outline.push_back(outline[0]);
	for (size_t i = 1; i < sz; i++)
	{
		if (min_x > outline[i].x)
		{
			min_x = outline[i].x;
		}
		else if(max_x < outline[i].x)
		{
			max_x = outline[i].x;
		}

		if (min_y > outline[i].y)
		{
			min_y = outline[i].y;
		}
		else if (max_y < outline[i].y)
		{
			max_y = outline[i].y;
		}

		m_outline.push_back(outline[i]);
	}

	w = max_x - min_x;
	h = max_y - min_y;
}


std::string GeoShape::name()
{
	return m_name;
}

void GeoShape::setName(std::string s)
{
	m_name = s;
}

GEO_NAMESPACE_END