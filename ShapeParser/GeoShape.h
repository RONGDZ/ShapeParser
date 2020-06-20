#pragma once
#include "GeoAttr.h"

GEO_NAMESPACE_START


class GeoShape :public GeoAttr, public GeoInfo, public GeoTag, public GeoLua
{
public:
	GeoShape(std::string name = "");
public:
	std::string m_name;
	std::string m_xyza;
	std::vector<GeoPoint> m_outline;
	GeoPoint m_offset;
	cInt min_x;
	cInt min_y;
	cInt max_x;
	cInt max_y;
	cInt w;
	cInt h;
public:
	//目前没有对 arc 做处理，后面需要增加
	virtual void geo(std::vector<GeoPoint>& outline,std::string xyza = "");
	virtual std::string name();
	virtual void setName(std::string s);
};
GEO_NAMESPACE_END

