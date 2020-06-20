#pragma once
#include "GeoDecl.h"
GEO_NAMESPACE_START

class GeoShape;
class GeoPlank;
class GeoShapeFmtMgr
{
public :
	void fmtShape(GeoShape* obj, std::string &out);
	void fmtPlank(GeoPlank* obj, std::string& out);
};

GEO_NAMESPACE_END

