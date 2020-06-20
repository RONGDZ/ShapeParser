#pragma once
#include "GeoDecl.h"
GEO_NAMESPACE_START
void awk(const char* s, size_t sz, std::vector<std::string>& v);
size_t hex(const char* s, size_t sz);
int rgba(int r, int g, int b, int a = 255);
int argb(int r, int g, int b, int a = 255);
int rgba(const char* s, size_t sz);
int argb(const char* s, size_t sz);
GEO_NAMESPACE_END
