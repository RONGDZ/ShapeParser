#include "ShapeParserMgr.h"
#include "GeoCabinet.h"
#include "GeoCanvas.h"
#include "GeoShape.h"
#include "GeoPlank.h"
#include "GeoWhole.h"
#include "util.h"
#define GEO_OBJ_OUTLINE(obj) cbOutline=[obj](void* ptr,std::string xyza){std::vector<GeoPoint>* lst = (std::vector<GeoPoint>*)ptr;obj->geo(*lst,xyza);};
#define GEO_OBJ_ATTR(obj) cbAttr=[obj](std::string &name, std::string &v){obj->setAttr(name, v);};
#define GEO_OBJ_INFO(obj) cbInfo=[obj](std::string &name, std::string &v){obj->setInfo(name, v);};
#define GEO_OBJ_TAG(obj) cbTag=[obj](void* ptr, std::string v) {obj->setTag((*(std::vector<cInt>*)ptr), v); };
#define GEO_OBJ_OFFSET(obj) cbOffset=[obj](void *ptr)\
{\
	std::vector<cInt>* v = (std::vector<cInt>*)ptr;\
	size_t c = v->size();\
	if (1 < c)\
	{\
		obj->m_offset.x = (*v)[0];\
		obj->m_offset.y = (*v)[1];\
		if (2 < c)\
		{\
			obj->m_offset.z = (*v)[3];\
		}\
	}\
};

#define GEO_OBJ_PTR(obj) cbObj=[obj](){ return obj;};

#define GEO_OBJ_CB(obj) GEO_OBJ_OUTLINE(obj) GEO_OBJ_ATTR(obj) GEO_OBJ_OFFSET(obj) GEO_OBJ_OFFSET(obj) GEO_OBJ_INFO(obj) GEO_OBJ_TAG(obj)

GEO_NAMESPACE_START

ShapeParserMgr::ShapeParserMgr(GeoWhole* geo)
{
	is_whole_free = nullptr == geo;
	if (is_whole_free)
	{
		whole = new GeoWhole();
	}
	else
	{
		whole = geo;
	}
	
	//画布会有基本信息
	cbInfo = [obj = whole](std::string& k, std::string& v)
	{
		obj->info[k] = v;
	};

	cbAttr = [](std::string& k, std::string& v) {};

	cbTag = [](void* ptr, std::string &v) {};

	cbOutline = [](void* ptr,std::string xyza) {};

	cbOffset = [](void*ptr) {};

	cbObj = []() {return nullptr; };

	init();
}

ShapeParserMgr::~ShapeParserMgr()
{
	if (is_whole_free)
	{
		delete whole;
		//whole = nullptr;
		//is_whole_free = false;
	}
}

char* ShapeParserMgr::plank(char* ptr, size_t& sz)
{
	GeoPlank* obj = new GeoPlank();
	obj->m_name = "plank";
	whole->planks.push_back(obj);
	GEO_OBJ_CB(obj);
	return indexNext(ptr,sz);
}

char* ShapeParserMgr::line(char* ptr, size_t &sz)
{
	return addShape("line", ptr, sz);
}

char* ShapeParserMgr::arc(char* ptr, size_t& sz)
{
	return addShape("arc", ptr, sz);
}

char* ShapeParserMgr::polygen(char* ptr, size_t& sz)
{
	return addShape("polygen", ptr, sz);
}

char* ShapeParserMgr::outline(char* ptr, size_t& sz)
{
	std::vector<cInt> v;
	char *p = indexNextArray(ptr, sz, v);
	size_t c = v.size();
	p = s2vec(p, sz, v);
	std::string xyza = "";
	std::vector<GeoPoint> lst;
	if (2 == c)
	{
		xyza = "xy";
		//2d
		c = v.size() + 1;
		for (size_t j = 2; j < c; j+=2)
		{
			GeoPoint pt;
			pt.x = v[j - 2];
			pt.y = v[j - 1];
			lst.push_back(pt);
		}
	}
	else if(3 == c)
	{
		xyza = "xya";
		//2d xya
		c = v.size() + 1;
		for (size_t j = 3; j < c; j += 3)
		{
			GeoPoint pt;
			pt.x = v[j - 3];
			pt.y = v[j - 2];
			pt.a = v[j - 1];
			lst.push_back(pt);
		}

	}
	else
	{
		xyza = "xyza";
		//3d xyza
		c = v.size() + 1;
		for (size_t j = 4; j < c; j += 3)
		{
			GeoPoint pt;
			pt.x = v[j - 4];
			pt.y = v[j - 3];
			pt.z = v[j - 2];
			pt.a = v[j - 1];
			lst.push_back(pt);
		}
	}
	
	if (nullptr != cbOutline)
	{
		void* v = &lst;
		cbOutline(v,xyza);
	}
	return p;
}

char* ShapeParserMgr::offset(char* ptr, size_t& sz)
{
	std::vector<cInt> v;
	char* p = indexNextArray(indexNext(ptr,sz), sz, v);
	cbOffset(&v);
	return p;
}

char* ShapeParserMgr::blocksize(char* ptr, size_t& sz)
{
	int v = 0;
	char* p = s2int(indexNext(ptr, sz), sz, v);
	parser(++p, v++);
	if (sz <= (size_t)v)
	{
		sz = 0;
	}
	else
	{
		sz -= v;
	}
	return p;
}

char* ShapeParserMgr::tag(char* ptr, size_t& sz)
{
	std::vector<cInt> v;
	char* p = s2vec(ptr, sz, v, ',');
	std::string s;
	p = s2sub(indexNext(p,sz), sz, s);
	cbTag(&v, s);
	return p;
}

char* ShapeParserMgr::info(char* ptr, size_t& sz)
{
	std::vector<cInt> v;
	char* p = s2vec(ptr, sz, v);

	size_t c = v.size();
	for (size_t i = 0; i < c; i++)
	{
		std::string  k;
		p = s2key(p, sz, k) + 1;
		std::string s(p,(size_t)v[i]);
		cbInfo(k, s);
		p += (size_t)v[i];
		sz -= (size_t)v[i] + 1;
	}

	return p;
}

char* ShapeParserMgr::attr(std::string& name, char* ptr, size_t& sz)
{
	char *p = indexNext(ptr, sz);
	char* n = p;
	while (0 < sz)
	{
		if ((0 > *p || 32 < *p))
		{
			p++;
			sz--;
		}
		else
		{
			break;
		}
		
	}
	std::string s(n,p);
	cbAttr(name, s);
	return p;
}

GeoShape* ShapeParserMgr::addShape(const char* name)
{
	GeoShape* obj = new GeoShape();
	obj->m_name = name;
	whole->shapes.push_back(obj);
	GEO_OBJ_CB(obj);
	return obj;
}

inline char* ShapeParserMgr::addShape(const char* name, char* ptr, size_t &sz)
{
	if (nullptr != addShape(name))
	{
		size_t typ = 0;
		char *p = startWithType(indexNext(ptr,sz), sz, typ);
		if (1 == typ)
		{
			return outline(p, sz);
		}
		return p;
	}
	return ptr;
}

inline char* ShapeParserMgr::startWithType(char* ptr, size_t &sz,size_t &typ)
{
	char* p = ptr;
	while(0 < sz)
	{
		if (0 > *p || 32 < *p)
		{
			if (('a' <= *p && 'z' >= *p) || ('A' <= *p && 'Z' >= *p))
			{
				typ = 2;
				return p;
			}
			else if('0'<= *p && '9' >= *p)
			{
				typ = 1;
				return p;
			}
		}
		p++;
		sz--;
	}
	typ = 0;
	return p;
}

inline char* ShapeParserMgr::indexNextArray(char* ptr, size_t sz, std::vector<cInt>& v)
{
	char* p = ptr;
	int index = 0;
	char  ch[64] = {0};
	while(0 < sz)
	{
		if ('0' > *p || '9' < *p)
		{
			ch[index] = '\0';
			v.push_back(GEO_ATOI(ch));
			if (',' == *p)
			{
				index = 0;
			}
			else
			{
				break;
			}
		}
		else
		{
			ch[index++] = *p;
		}
		p++;
		sz--;
	}
	return p;
}

inline char* ShapeParserMgr::indexNext(char* ptr, size_t &sz)
{
	char* p = ptr;
	//找取下一个开始点
	while (0 < sz)
	{
		if (('a' <= *p && 'z' >= *p) || ('A' <= *p && 'Z' >= *p) || ('0' <= *p && '9' >= *p))
		{
			break;
		}
		p++;
		sz--;
	}
	return p;
}

inline char* ShapeParserMgr::s2vec(char* s, size_t &sz, std::vector<cInt>& v)
{
	char* p = s;
	size_t index = 0;
	size_t dwflag = 0;
	char  ch[64] = { 0 };
	while (0 < sz)
	{
		if ('0' > *p || '9' < *p)
		{
			if (0 < index)
			{
				ch[index] = '\0';
				v.push_back(GEO_ATOI(ch));

				if ('\n' == *p)
				{
					if (0 == index)
					{
						//2 line feed 
						if (0 < dwflag)
						{
							break;
						}
						dwflag++;
					}
					else
					{
						dwflag = 0;
					}
				}
				index = 0;
			}

			if (('a' <= *p && 'z' >= *p) || ('A' <= *p && 'Z' >= *p))
			{
				break;
			}
		}
		else
		{
			ch[index++] = *p;
		}
		p++;
		sz--;
	}
	return p;
}

inline char* ShapeParserMgr::s2vec(char* s, size_t& sz, std::vector<cInt>& v, char sep)
{
	char* p = indexNext(s,sz);
	size_t index = 0;
	size_t dwflag = 0;
	char  ch[64] = { 0 };
	while (0 < sz)
	{
		if (sep == *p)
		{
			ch[index] = '\0';
			v.push_back(GEO_ATOI(ch));
			index = 0;

		}
		else if ('0' > * p || '9' < *p)
		{
			if (0 < index)
			{
				ch[index] = '\0';
				v.push_back(GEO_ATOI(ch));
			}
			break;
		}
		else
		{
			ch[index++] = *p;
		}
		p++;
		sz--;
	}
	return p;
}

inline char* ShapeParserMgr::s2vec(char* s, size_t &sz, std::vector<std::string>& v)
{
	char* p = s;
	size_t index = 0;
	size_t dwflag = 0;
	char  ch[256] = { 0 };
	while(0 < sz)
	{
		if ('0' > *p || '9' < *p)
		{
			break;
		}
		else if(',' == *p)
		{
			ch[index] = '\0';
			std::string str = ch;
			str.resize(index);
			v.push_back(str);
			index = 0;
		}
		else
		{
			ch[index++] = *p;
		}
		p++;
		sz--;
	}

	return p;
}

inline char* ShapeParserMgr::s2key(char* s, size_t &sz, std::string& key)
{
	char* p = indexNext(s,sz);
	char ch[128] = { 0 };
	int j = 0;
	while(0 < sz)
	{
		if (0 <= *p && 32 >= *p)
		{
			key = ch;
			break;
		}
		else
		{
			if (('A' <= *p && 'Z' >= *p))
			{
				ch[j++] = *p + 32;
			}
			else
			{
				ch[j++] = *p;
			}
		}
		p++;
		sz--;
	}
	key = ch;
	return p;
}

inline char* ShapeParserMgr::s2int(char* s, size_t &sz, int& v)
{
	size_t i = 0;
	char ch[128] = { 0 };
	char* p = s;
	while (0 < sz)
	{
		if ('0' <= *p && '9' >= *p)
		{
			ch[i++] = *p;
		}
		else
		{
			v = atoi(ch);
			break;
		}
		p++;
		sz--;
	}
	return p;
}

inline char* ShapeParserMgr::s2sub(char* s, size_t& sz, std::string& v)
{
	int len = 0;
	char *p = s2int(s, sz, len) + 1;
	sz -= 1;
	if (0 < len)
	{
		v.append(p, len);
		p += len;
		sz -= len;
	}
	return p;
}

inline char* ShapeParserMgr::doCmd(std::string cmd, char* ptr, size_t &sz)
{
	if (m_cmds.end() == m_cmds.find(cmd))
	{
		return ptr;
	}
	return m_cmds[cmd](ptr,sz);
}

void ShapeParserMgr::init()
{
	initCmd();
}

void ShapeParserMgr::initEvent()
{
}

void ShapeParserMgr::initCmd()
{
	m_cmds["line"] = [&](char *ptr, size_t &sz)
	{
		return line(ptr,sz);
	};

	m_cmds["arc"] = [&](char* ptr, size_t &sz)
	{
		return arc(ptr, sz);
	};

	m_cmds["polygen"] = [&](char* ptr, size_t &sz)
	{
		return polygen(ptr, sz);
	};

	m_cmds["plank"] = [&](char* ptr, size_t& sz)
	{
		return plank(ptr, sz);
	};

	m_cmds["offset"] = [&](char* ptr, size_t& sz)
	{
		return offset(ptr, sz);
	};

	m_cmds["xy"] = [&](char* ptr, size_t& sz)
	{
		return outline(indexNext(ptr,sz), sz);
	};

	m_cmds["xya"] = [&](char* ptr, size_t& sz)
	{
		return outline(indexNext(ptr, sz), sz);
	};

	m_cmds["xyza"] = [&](char* ptr, size_t& sz)
	{
		return outline(indexNext(ptr, sz), sz);
	};

	m_cmds["outline"] = [&](char* ptr, size_t& sz)
	{
		return outline(indexNext(ptr, sz), sz);
	};

	m_cmds["blocksize"] = [&](char* ptr, size_t& sz)
	{
		return blocksize(ptr, sz);
	};

	m_cmds["info"] = [&](char* ptr, size_t& sz)
	{
		return info(ptr, sz);
	};

	m_cmds["tag"] = [&](char* ptr, size_t& sz)
	{
		return tag(ptr, sz);
	};
}

void ShapeParserMgr::parser(char* ptr, size_t sz)
{
	size_t i = 0;
	size_t c = sz;
	char* p = ptr;
	while(0 < c)
	{
		std::string k;
		char *n = s2key(p, c, k);
		if (1 > sz) return;

		p = doCmd(k, n, c);

		if (n == p)
		{
			p = attr(k, p, c);
		}
	}
}

GEO_NAMESPACE_END


