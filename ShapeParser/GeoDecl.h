#pragma once
#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "clipper.hpp"
using namespace ClipperLib;


#define GEO_PARSER_VERSION "0.0.1"
#define GEO_NAMESPACE_START namespace lygeometry{
#define GEO_NAMESPACE_END }
#define GEO_NAMESPACE_USING  using namespace lygeometry

#define GEO_FILL "fill"
#define GEO_STROKE "stroke"
#define GEO_STROKE_WIDTH "stroke-width"
#define GEO_OPACITY "opacity"

#define GEO_XY "xy"
#define GEO_XYZ "xyz"
#define GEO_XYA "xya"
#define GEO_XYZA "xyza"
#define GEO_OFFSET "offset"

#define GEO_ATOI(x) atoll(x)
#define DEL_CLEAR_VEC(l) for(auto l##_n : l){delete l##_n; } l.clear();
