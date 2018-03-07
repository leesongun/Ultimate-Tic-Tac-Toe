#pragma once
#include <iostream>
#include <vector>
#include <intrin.h>
#include "table.h"
//#include <emmintrin.h>
class board
{
public:
	board() :bb{ 0, }, playable{ 0 }, pb{ 9 }, t{ 1 }
	{}
	board(const board &) = default;
	void print() const;
	void printpb() const;
	void play(unsigned char x)
	{
		if (pb != 9)
			if (((bb[0][pb] | bb[1][pb])&(1 << x)))
				return;
			else if (::win(bb[t ^= 1][pb] |= (1 << x)))
			{
				bb[t][9] |= (1 << pb);
				playable |= (1 << pb);
			}
			else if ((bb[0][pb] | bb[1][pb]) == 0x1FF)
				playable |= (1 << pb);
		pb = (playable & (1<<x)) ? 9 : x;
	}
	inline bool win() const
	{
		return ::win(bb[t][9]);
	}
	inline bool end() const
	{
		return (playable == 0x1FF) || win();
	}
	inline unsigned char gett() const
	{
		return t;
	}
	void generate_moves(std::vector</*const*/ board> &v) const
	{
		if (pb == 9)
		{
			for (unsigned int i = 0; i != 9; ++i)
			{
				if (playable & (1 << i))continue;
				for (unsigned short x = 0x1FF ^ (bb[0][i] | bb[1][i]), a = 0;
					a = _blsi_u32(x); x ^= a)
				{
					board temp = *this;
					temp.play(i, a);
					v.push_back(temp);
				}
			}
		}
		else
		{
			for (unsigned short x = 0x1FF ^ (bb[0][pb] | bb[1][pb]), a = 0;
				a = _blsi_u32(x); x ^= a)
			{
				board temp = *this;
				temp.play(pb, a);
				v.push_back(temp);
			}
		}
	}
	inline void randplay()
	{
		if (pb == 9)
			pb = rand_tbl2[playable][fastrand() * (9 - __popcnt16(playable)) >> RAND_SHIFT];
		else
		{
			unsigned short temp = bb[0][pb] | bb[1][pb];
			play(pb, rand_tbl[temp][fastrand() * (9 - __popcnt16(temp)) >> RAND_SHIFT]);
		}
	}
	std::vector<int> tovector();
protected:
	inline void play(unsigned char pb, unsigned short a)
	{
		unsigned short b = 1 << pb;
		if (::win(bb[t ^= 1][pb] |= a))
		{
			bb[t][9] |= b;
			playable |= b;
		}
		else if ((bb[0][pb] | bb[1][pb]) == 0x1FF)
			playable |= b;
		board::pb = (playable & a) ? 9 : _tzcnt_u32(a);
	}
private:
	//unsigned int bitboard[2][3];//(81+9)*2
	//9*3+9*3+9*4?Â©¸®´Âµ¥?
	//__m128i
	unsigned short bb[2][10];
	unsigned short playable;
	unsigned char pb;//playing board
	unsigned char t;
};
std::ostream &operator<<(std::ostream& os, const board& b);