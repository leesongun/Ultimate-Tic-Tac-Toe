#pragma once
#include <intrin.h>
static_assert(sizeof(unsigned int) == 4, "size of unsigned int must be 4 bytes");
extern unsigned int win_tbl[16];
//불가능한 비트를 1로 표시
extern unsigned short rand_tbl[511][9];
extern unsigned char rand_tbl2[511][9];
inline bool testwin(unsigned short i)
{
	return (i & (i >> 3) & (i >> 6) & 7) || (i & (i >> 1) & (i >> 2) & 0111) || (__popcnt16(i & 0421) == 3) || (__popcnt16(i & 0124) == 3);
}
//initialize tables
inline void init()
{
	memset(win_tbl, 0, sizeof(win_tbl));
	for (unsigned short i = 0; i != 512; ++i)
		if (testwin(i))
			win_tbl[i / 32] |= (1 << (i % 32));
	memset(rand_tbl, 0, sizeof(rand_tbl));
	for (unsigned short i = 0; i != 511; ++i)
	{
		for (unsigned short k = 0x1FF ^ i, t = 0, j = 0;
			k ^= t, t = _blsi_u32(k); ++j)
		{
			rand_tbl[i][j] = t;
			rand_tbl2[i][j] = _tzcnt_u32(t);
		}
	}
}
//read win table
inline bool win(unsigned short a)
{
	return win_tbl[a >> 5] & (1 << (a & 0x1F));
	//return win_tbl[a / 32] & (1 << (a % 32));
}
#define RAND_SHIFT 16
inline unsigned int fastrand()
{
	static unsigned int g_seed = (unsigned int)time(NULL);
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16)/*&0x7FFF*/;
}