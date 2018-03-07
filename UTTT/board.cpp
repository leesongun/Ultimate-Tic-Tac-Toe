#include "stdafx.h"
#include "board.h"
unsigned int win_tbl[16];
unsigned short rand_tbl[511][9];
unsigned char rand_tbl2[511][9];
void board::print() const
{
	for (unsigned int i = 0; i != 9; ++i)
	{
		if (i && (i % 3 == 0))
			puts("����������������������������������������");
		for (unsigned int j = 0; j != 9; ++j)
		{
			if (j && (j % 3 == 0))
				printf("��");
			unsigned int A = (i / 3) * 3 + (j / 3);
			unsigned int B = (i % 3) * 3 + (j % 3);
			if (bb[1][9] & (1 << A))
				printf("��");
			else if ((bb[0][9] & (1 << A)) || (bb[0][A] & (1 << B)))
				printf("��");
			else if (bb[1][A] & (1 << B))
				printf("��");//��
			else printf("  ");
		}
		puts("");
	}
}

void board::printpb() const
{
	if (pb == 9)
	{
		puts("�ᦢ�ᦢ��");
		puts("����������������");
		puts("�ᦢ�ᦢ��");
		puts("����������������");
		puts("�ᦢ�ᦢ��");
	}
	else
	{
		for (unsigned int i = 0; i != 3; ++i)
		{
			if(i)
				puts("����������������");
			for (unsigned int j = 0; j != 3; ++j)
			{
				if (j)printf("��");
				if (i * 3 + j == pb)
					printf("��");
				else printf("  ");
			}
			puts("");
		}
	}
}
std::ostream & operator<<(std::ostream & os, const board & b)
{
	b.print();
	return os;
}