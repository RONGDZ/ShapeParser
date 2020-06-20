#include "GeoShapeFmtMgr.h"
#include "GeoShape.h"
#include "GeoPlank.h"

GEO_NAMESPACE_START
#define GEO_FMT_MAX_LEN 8192


void GeoShapeFmtMgr::fmtShape(GeoShape* obj, std::string & out)
{
	out.append(obj->m_name);
	char ch[GEO_FMT_MAX_LEN] = { 0 };
	char *p = ch;
	int dwflag = 0;

	auto cbChkLen = [&ch, &p,&out]
	{
		if (1024 < (p - ch))
		{
			int c = p - ch;
			char buff[16] = { 0 };
			sprintf_s(buff, "blocksize %d\n", c);
			out.append(buff);
			out.append(ch, c);
			out.append("\n");
			p = ch;
		}
	};

	auto cbAppend = [&ch, &p, &out]()
	{
		if (p != ch)
		{
			*p++ = ' ';
			out.append(ch, p - ch);
			p = ch;

		}
	};

	auto cbFreeLen = [&ch, &p]()
	{
		return GEO_FMT_MAX_LEN - (p - ch);
	};

	if (0 < obj->tags.size())
	{
		dwflag++;
		*p++ = '\n';
		for (auto tag : obj->tags)
		{
			cInt x = tag.first->x;
			cInt y = tag.first->y;
			cInt z = tag.first->z;
			cInt a = tag.first->a;
			p += sprintf_s(p, cbFreeLen(), "tag %lld,%lld,%lld,%lld %d %s", x, y, z, a, tag.second.size(), tag.second.c_str());
			cbChkLen();
		}
		cbAppend();
	}

	if (0 < obj->infos.size())
	{
		dwflag++;
		p += sprintf_s(ch, "\n%s", "info");
		for (auto info : obj->infos)
		{
			*p++ = ' ';
			p += sprintf_s(p, cbFreeLen(), "%d", info.second.size());
			cbChkLen();
		}
		*p++ = '\n';
		for (auto info : obj->infos)
		{
			*p++ = ' ';
			p += sprintf_s(p, cbFreeLen(), "%s %s", info.first.c_str(), info.second.c_str());
			cbChkLen();
		}
		cbAppend();
	}

	if (0 < obj->attrs.size())
	{
		dwflag++;
		*p++ = '\n';
		for (auto attr : obj->attrs)
		{
			p += sprintf_s(p, cbFreeLen(), "%s %s ", attr.first.c_str(), attr.second.c_str());
			cbChkLen();
		}
		cbAppend();
	}

	int c = obj->m_xyza.size();
	if (2 == c)
	{
		if (0 < dwflag)
		{
			p += sprintf_s(ch, "\noutline xy");
		}
		
		for (GeoPoint pt : obj->m_outline)
		{
			p += sprintf_s(p,cbFreeLen(), " %lld,%lld", pt.x, pt.y);
			cbChkLen();
		}
		cbAppend();
	}
	else if(3 == c)
	{
		if (0 < obj->m_xyza.find('a'))
		{
			if (0 < dwflag)
			{
				p += sprintf_s(ch, "\noutline xya");
			}
			for (GeoPoint pt : obj->m_outline)
			{
				p += sprintf_s(p, cbFreeLen(), " %lld,%lld,%lld", pt.x, pt.y, pt.a);
				cbChkLen();
			}
			cbAppend();
		}
		else
		{
			if (0 < dwflag)
			{
				p += sprintf_s(ch, "\noutline xyz");
			}
			for (GeoPoint pt : obj->m_outline)
			{
				p += sprintf_s(p, cbFreeLen(), " %lld,%lld,%lld", pt.x, pt.y, pt.z);
				cbChkLen();
			}
			cbAppend();
		}
	}
	else
	{
		if (0 < dwflag)
		{
			p += sprintf_s(ch, "\noutline xyza");
		}
		for (GeoPoint pt : obj->m_outline)
		{
			p += sprintf_s(p, cbFreeLen(), " %lld,%lld,%lld,%lld", pt.x, pt.y, pt.z, pt.a);
			cbChkLen();
		}
		cbAppend();
	}

	out.append("\n\n");

}
void GeoShapeFmtMgr::fmtPlank(GeoPlank* obj, std::string& out)
{
	
}


GEO_NAMESPACE_END
