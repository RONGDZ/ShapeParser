#include "GeoAttr.h"
#include "GeoShape.h"
#include "util.h"
GEO_NAMESPACE_START

bool GeoAttr::attr(std::string name, std::string& v)
{
	if (attrs.end() == attrs.find(name))
	{
		return false;
	}
	v = attrs[name];
	return true;
}

void GeoAttr::setAttr(std::string name, std::string v)
{
	attrs[name] = v;
}

bool GeoAttr::attr2argb(std::string name, int& rgb)
{
	std::string s;
	if (attr(name, s))
	{
		rgb = argb(s.c_str(), s.size());
		return true;
	}
	return false;
}

bool GeoAttr::attr2color(std::string name, int& rgb)
{
	return attr2argb(name, rgb);
}

bool GeoTag::tag(GeoPoint *pt, std::string& v)
{
	if (tags.end() == tags.find(pt))
	{
		return false;
	}
	v = tags[pt];
	return true;
}

void GeoTag::setTag(GeoPoint *pt, std::string v)
{
	tags[pt] = v;
}

GeoPoint* GeoTag::setTag(GeoPoint pt, std::string v)
{
	GeoPoint* p = new GeoPoint();
	*p = pt;
	tags[p] = v;
	return p;
}

GeoPoint* GeoTag::setTag(std::vector<cInt> lst, std::string v)
{
	size_t c = lst.size();
	if (1 < c)
	{
		GeoPoint* pt = new GeoPoint();
		for (size_t i = 0; i < c; i++)
		{
			(*pt)[i] = lst[i];
		}
		tags[pt] = v;
		return pt;
	}
	return  nullptr;
}

bool GeoInfo::info(std::string name, std::string& v)
{
	if (infos.end() == infos.find(name))
	{
		return false;
	}
	v = infos[name];
	return true;
}

void GeoInfo::setInfo(std::string name, std::string v)
{
	infos[name] = v;
}

bool GeoLua::getLua(std::string name, std::string& v)
{
	if (gluas.end() == gluas.find(name))
	{
		return false;
	}
	v = gluas[name];
	return true;
}

void GeoLua::setLua(std::string name, std::string v)
{
	gluas[name] = v;
}


GEO_NAMESPACE_END

