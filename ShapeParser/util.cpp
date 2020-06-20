#include "util.h"
GEO_NAMESPACE_START

void awk(const char *s,size_t sz, std::vector<std::string>& v)
{
	size_t k = 0;
	size_t i = 0;
	for (; i < sz; i++)
	{
		if (',' == s[i] || (0 <= s[i] && 32 >= s[i]))
		{
			if (i == k)
			{
				v.push_back("");
			}
			else
			{
				v.push_back(std::string(s + k, i - k));
			}

			k = i + 1;
		}
	}
	if (0 < k)
	{
		if (',' == s[k] || (0 <= s[k] && 32 >= s[k]))
		{
			v.push_back("");
		}
		else
		{
			v.push_back(std::string(s + k, i - k));
		}
	}
}

size_t hex(const char* s, size_t sz)
{
	size_t v = 0;
	size_t c = 0;
	constexpr size_t  ua = 'A' + 10;
	constexpr size_t la = 'a' + 10;
	constexpr size_t z = '0';
	for (size_t i = sz - 1; -1 != i; i--)
	{
		if ('0' <= s[i] && '9' >= s[i])
		{
			v += ((s[i] - z) << c);
		}
		else if ('a' <= s[i] && 'f' >= s[i])
		{
			v += ((s[i] - la) << c);
		}
		else if ('A' <= s[i] && 'F' >= s[i])
		{
			v += ((s[i] - ua) << c);
		}
		else
		{
			break;
		}
		c += 4;
	}
	return v;
}

int rgba(int r, int g, int b, int a)
{
	int v = (a & 255) | ((b & 255) << 8) | ((g & 255) << 16) | ((r & 255) << 24);
	return v;
}

int argb(int r, int g, int b, int a)
{
	int v = (b & 255) | ((g & 255) << 8) | ((r & 255) << 16) | ((a & 255) << 24);
	return v;
}

int rgba(const char* s, size_t sz)
{
	if (5 > sz) return 0;
	int flag = 'x' == s[1] || 'X' == s[1] ? 1 : 0;

	if (0 == flag)
	{
		flag = 2;
		for (size_t i = 0; i < sz; i++)
		{
			if (',' == s[i])
			{
				flag = 0;
				break;
			}
		}
	}

	if (0 == flag)
	{
		std::vector<std::string> v;
		awk(s, sz, v);
		if (3 == v.size())
		{
			int r = atoi(v[0].c_str());
			int g = atoi(v[1].c_str());
			int b = atoi(v[2].c_str());
			return rgba(r, g, b);
		}
		else if (4 == v.size())
		{
			int r = atoi(v[0].c_str());
			int g = atoi(v[1].c_str());
			int b = atoi(v[2].c_str());
			int a = atoi(v[3].c_str());
			return rgba(r, g, b, a);
		}
	}
	else if (1 == flag)
	{
		if (8 == sz)
		{
			return ((hex(s, sz) << 8) | 0xFF);
		}
		else if (10 == sz)
		{
			return hex(s, sz);
		}
	}
	else
	{
		if (6 == sz)
		{
			return ((hex(s, sz) << 8) | 0xFF);
		}
		else if (8 == sz)
		{
			return hex(s, sz);
		}
	}

	return 0;
}

int argb(const char* s, size_t sz)
{
	if (5 > sz) return 0;
	int flag = 'x' == s[1] || 'X' == s[1] ? 1 : 0;

	if (0 == flag)
	{
		flag = 2;
		for (size_t i = 0; i < sz; i++)
		{
			if (',' == s[i])
			{
				flag = 0;
				break;
			}
		}
	}

	if (0 == flag)
	{
		std::vector<std::string> v;
		awk(s, sz, v);
		if (3 == v.size())
		{
			int r = atoi(v[0].c_str());
			int g = atoi(v[1].c_str());
			int b = atoi(v[2].c_str());
			return rgba(r, g, b);
		}
		else if (4 == v.size())
		{
			int a = atoi(v[0].c_str());
			int r = atoi(v[1].c_str());
			int g = atoi(v[2].c_str());
			int b = atoi(v[3].c_str());
			return rgba(r, g, b, a);
		}
	}
	else if (1 == flag)
	{
		if (8 == sz)
		{
			return hex(s, sz) | 0xFF000000;
		}
		else if (10 == sz)
		{
			return hex(s, sz);
		}
	}
	else
	{
		if (6 == sz)
		{
			return hex(s, sz) | 0xFF000000;
		}
		else if (8 == sz)
		{
			return hex(s, sz);
		}
	}

	return 0;
}

GEO_NAMESPACE_END