#include "GeoWhole.h"
#include "GeoCabinet.h"
#include "GeoCanvas.h"
#include "GeoShape.h"
#include "GeoPlank.h"

GEO_NAMESPACE_START
GeoWhole::~GeoWhole()
{
	DEL_CLEAR_VEC(cabinets);
	DEL_CLEAR_VEC(shapes);
	DEL_CLEAR_VEC(planks);
	delete canvas;
}
GEO_NAMESPACE_END