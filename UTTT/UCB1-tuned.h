#pragma once
//todo:implement UCB1-tuned
//https://orbi.uliege.be/bitstream/2268/132793/1/paper88.pdf
#include <vector>
#include "board.h"
typedef int value_type;
#define DRAW_REWARD 0
class searcher
{
public:
	searcher(board x, float c/*, size_t max = 0x100000*/) :
		search_data(1),
		board_data({ x }),
		c(c)
	{}
	void search(unsigned int trials)
	{
		do _search(0); while (--trials);
	}
	void search_within_time(unsigned int second)
	{
		clock_t end = clock() + second * CLOCKS_PER_SEC;
		do _search(0); while (clock() < end);
	}
	board getresult()
	{
		unsigned int max = search_data[1].num_simul, index = 1;
		for (unsigned char i = 2; i != search_data[0].child_index_end; ++i)
		{
			if (search_data[i].num_simul > max)
			{
				max = search_data[i].num_simul;
				index = i;
			}
		}
		return board_data[index];
	}
	unsigned int numsimualation()
	{
		return search_data[0].num_simul;
	}
protected:
	/*constexpr*/ inline float UCT(unsigned int index, unsigned int parent_total_simul) const
	{
		return //search_data[index].num_simul? 
			(float)search_data[index].value_sum / search_data[index].num_simul + sqrtf(c * log(parent_total_simul) / search_data[index].num_simul)
			//: FLT_MAX
			;
	}
private:
	std::pair<unsigned int, value_type> _search(unsigned int index)
	{
		if (search_data[index].child_index_start == search_data[index].child_index_end)
		{
			if (board_data[index].end())
			{
#define BIG_NUMBER INT_MAX
				search_data[index].num_simul = (BIG_NUMBER >> 3);
				value_type reward = board_data[index].win() ? 1 : DRAW_REWARD;
				search_data[index].value_sum = reward * BIG_NUMBER;
				return { 1, reward };
#undef BIG_NUMBER
				//이게 영향을 주는 경우를 생각해보면
				//얘가 root node의 direct child node인 경우인데
				//비기는 경우->어차피 수는 하나
				//이기는 경우->두면 무조건 좋지
			}
			//generate possible moves
			search_data[index].child_index_start = board_data.size();
			{
				board temp = board_data[index];
				temp.generate_moves(board_data);
			}
			search_data[index].child_index_end = board_data.size();
			for (unsigned int i = search_data[index].child_index_start; i != search_data[index].child_index_end; ++i)
			{
				board temp = board_data[i];
				while (!temp.end())
					temp.randplay();
				value_type reward = temp.win() ? 1 : DRAW_REWARD;
				if (temp.gett() != board_data[i].gett())
					reward = -reward;
				search_data[index].value_sum -= reward;
				search_data.push_back({ reward,1,0,0 });
			}
			return { search_data[index].num_simul = search_data[index].child_index_end - search_data[index].child_index_start
				, search_data[index].value_sum };
		}
		unsigned int node_to_search = search_data[index].child_index_start;
		float max_UCT = UCT(search_data[index].child_index_start, search_data[index].num_simul);
		for (unsigned int i = search_data[index].child_index_start + 1; i != search_data[index].child_index_end; ++i)
		{
			float temp = UCT(i, search_data[index].num_simul);
			if (temp > max_UCT)
			{
				max_UCT = temp;
				node_to_search = i;
			}
		}
		//const auto &[a, b] = _search(i);
		auto result = _search(node_to_search);
		result.second *= -1;
		search_data[index].num_simul += result.first;
		search_data[index].value_sum += result.second;
		return result;
	}
	struct node
	{
		value_type value_sum;
		unsigned int num_simul;
		unsigned int child_index_start, child_index_end;
	};
	std::vector <node> search_data;
	std::vector </*const*/ board> board_data;
	float c;
};