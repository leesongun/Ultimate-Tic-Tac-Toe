#include "stdafx.h"
#define VAR_CONST 2
#define PRINT_RESULTS
//todo:implement multithreading
float find_c(unsigned int plays, unsigned int num, float min, float max, float error)
{
	float c[2] = {min, max};
	unsigned int t = num;
	value_type sum = 0;
	while(max - min > error)
	{
		while(t--)
		{
			unsigned char start_randomizer = fastrand() & 1;
			board x{};
			while (!x.end())
			{
				searcher a(x, c[x.gett()^start_randomizer]);
				a.search(plays);
				x = a.getresult();
			}
			value_type a = x.win() ? 1 : DRAW_REWARD;
			if (x.gett()^start_randomizer)
				a = -a;
			sum += a;
#ifdef PRINT_RESULTS
			printf("%6u%6d\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", num-t, sum);
#endif
		}
		if (sum > sqrt(VAR_CONST * num))
#ifdef PRINT_RESULTS
			printf("%f vs %f:\t%dplays\t%f win by %d\n", c[0], c[1], num, c[1], sum),
#endif
			sum = 0, t = num, c[0] = (c[0] + c[1]) / 2;
		else if (sum < -sqrt(VAR_CONST * num))
#ifdef PRINT_RESULTS
			printf("%f vs %f:\t%dplays\t%f win by %d\n", c[0], c[1], num, c[0], -sum),
#endif
			sum = 0, t = num, c[1] = (c[0] + c[1]) / 2;
		else
		{
			t = num;
			num *= 2;
		}
	}
}
unsigned int rolloutspeed(unsigned int sec)
{
	unsigned int result = 0;
	clock_t a = clock() + sec * CLOCKS_PER_SEC;
	do {
		board x = board{};
		do x.randplay(); while (!x.end());
		++result;
	} while (clock() < a);
	return result;
}