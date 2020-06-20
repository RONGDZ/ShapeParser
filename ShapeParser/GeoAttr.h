#pragma once
#include "GeoDecl.h"
#include "GeoPoint.h"

GEO_NAMESPACE_START

class GeoAttr
{
public:
	std::map<std::string, std::string> attrs;
public:
	virtual bool attr(std::string name, std::string& v);
	virtual void setAttr(std::string name, std::string v);
	virtual bool attr2argb(std::string name, int& rgb);
	virtual bool attr2color(std::string name, int& rgb);
};

class  GeoTag
{
public:
	std::map<GeoPoint*,std::string> tags;
public:
	virtual bool tag(GeoPoint* pt, std::string& v);
	virtual void setTag(GeoPoint* pt, std::string v);
	virtual GeoPoint* setTag(GeoPoint pt, std::string v);
	virtual GeoPoint* setTag(std::vector<cInt> lst, std::string v);
};

class GeoInfo
{
public:
	std::map<std::string, std::string> infos;
public:
	virtual bool info(std::string name, std::string& v);
	virtual void setInfo(std::string name, std::string v);
};

class  GeoLua
{
public:
	std::map<std::string, std::string> gluas;
public:
	virtual bool getLua(std::string name, std::string& v);
	virtual void setLua(std::string name, std::string v);
};

GEO_NAMESPACE_END