#include "stdafx.h"
float find_max_c(unsigned int seconds)
{
	float c[2];
	{
		board x;
		while (!x.end())
		{
			searcher a(x, c[x.gett()]);
			a.search_within_time(seconds);
			x = a.getresult();
		}
	}
}