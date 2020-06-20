#pragma once
#include "GeoDecl.h"

GEO_NAMESPACE_START

class GeoWhole;
class GeoShape;
struct GeoPoint;
class ShapeParserMgr
{
public:
	ShapeParserMgr(GeoWhole *geo = nullptr);
	~ShapeParserMgr();
private:
	std::map<std::string, std::function<char* (char *ptr,size_t &size)>> m_cmds;
	GeoWhole* whole; 
	bool is_whole_free;
private:
	std::function<void(std::string&, std::string&)> cbAttr;
	std::function<void(std::string&, std::string&)> cbInfo;
	std::function<void(void*, std::string&)> cbTag;
	std::function<void(void*,std::string xyza)> cbOutline;
	std::function<void (void*)> cbOffset;
	std::function<void*()> cbObj;
private:
	char* plank(char* ptr, size_t& sz);
private:
	char* line(char* ptr, size_t &sz);
	char* arc(char* ptr, size_t& sz);
	char* polygen(char* ptr, size_t& sz);
	char* outline(char* ptr, size_t& sz);
	char* offset(char* ptr, size_t& sz);
	char* blocksize(char* ptr, size_t& sz);
	char* tag(char* ptr, size_t& sz);
	char* info(char* ptr, size_t& sz);
private:
	char* attr(std::string& name, char* ptr, size_t& sz);
	
private:
	inline GeoShape* addShape(const char *name);
	inline char* addShape(const char* name,char* ptr,size_t &sz);
	inline char* startWithType(char* ptr, size_t &sz,size_t &typ);
	inline char* indexNextArray(char* ptr, size_t sz, std::vector<cInt>& v);
	inline char* indexNext(char* ptr, size_t &sz);
	inline char* s2vec(char* s, size_t &sz, std::vector<cInt>& v);
	inline char* s2vec(char* s, size_t& sz, std::vector<cInt>& v, char sep);
	inline char* s2vec(char* s, size_t &sz, std::vector<std::string>& v);
	inline char* s2key(char* s,size_t &sz, std::string &key);
	inline char* s2int(char* s, size_t &sz, int& v);
	inline char* s2sub(char* s, size_t& sz, std::string& v);
	inline char* doCmd(std::string cmd, char* ptr, size_t &sz);
public:
	void init();
	void initEvent();
	void initCmd();
	void parser(char* ptr, size_t sz);
};

GEO_NAMESPACE_END