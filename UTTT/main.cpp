
// main.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
//아이디어 1
//81개의 선택지가 있는경우
//2개의 subaction으로 나눈다
//작은 판 내부의 위치를 결정
//후 작은 판을 결정

//일반적인 경우도 두개로 나누고 싶은데
//자유 위치에 둘 건지(상대방이 다음 턴에 어디든 둘 수 있음)
//아님 일반 위치에 둘건지(상대방이 둘 수 있는 곳이 제한됨)
//일반위치 노드 여러개 + 자유 위치 노드 하나
//자유위치가 다시 자식 가지고
//이런식으로

//그럼 이 아이디어를 겹쳐 쓰면
//81개의 선택지가 있는데 다음 수에 상대방이 81개의 경우의 수가 있게 하는 경우는
//3개로 나뉘겠네

//우선 selection에 필요한 데이터(승률, 시뮬레이션 수)만 넣어놓은 array를 만들고
//그 다음 게임 데이터를 넣어놓은 array를 만들자
//메모리 지역성!



int main()
{
	//srand((unsigned int)time(NULL));
	init();
	//printf("%u", rolloutspeed(1));
	printf("%f", find_c(1000, 100, 0, 4, 0.0001));
	unsigned char i;
	for (;;)
	{
		unsigned char t;
		puts("먼저 하시려면 1, 나중에 하시려면 0을 입력해주세요.");
		do
		{
			scanf_s("%hhu", &t);
		} while (t != 0 && t != 1);
		board x;
//		_wsystem(L"CLS");
		while (!x.end())
		{
			_wsystem(L"CLS");
			x.print();
			x.printpb();
			switch (x.gett() ^ t)
			{
			case 0:
				scanf_s("%hhu", &i);
				--i;
				i += (1 - (i / 3)) * 6;
				x.play(i);
				//_wsystem(L"CLS");
				break;
			case 1:
				searcher a(x, 1.03125);
				a.search_within_time(1);
				x = a.getresult();
				//_wsystem(L"CLS");
				//printf("%u\n", a.numsimualation());
				break;
			}
		}
		x.print();
		_wsystem(L"PAUSE");
	}
    return 0;
}

