#include"history_heuristic.h"
#include"define.h"

HistoryHeuristic::HistoryHeuristic()
{

}

HistoryHeuristic::~HistoryHeuristic()
{

}

void HistoryHeuristic::ResetHistoryTable()
{
	memset(History_Table, 10, BOARD_NUM*sizeof(int));
}

//去给定走法的历史得分
int HistoryHeuristic::GetHistoryScore(ChessMove *move)
{
	return History_Table[move->ChessPos.y][move->ChessPos.x];
}

void HistoryHeuristic::EnterHistoryScore(ChessMove *move, int depth)
{
	History_Table[move->ChessPos.y][move->ChessPos.x] += 2 << depth;
}

void HistoryHeuristic::QSort(ChessMove *source, int low, int high)
{
	int i;
	if (low < high)
	{
		i = Partition(source, low, high);
		QSort(source, low, i - 1);
		QSort(source, i, high);
	}
}

int HistoryHeuristic::Partition(ChessMove *source, int low, int high)
{
	ChessMove temp;
	temp = source[low];
	while (low < high)
	{
		while (source[high].Score <= temp.Score&&low < high)
			high--;
		source[low] = source[high];
		while (source[low].Score > temp.Score&&low < high)
			low++;
		source[high] = source[low];
	}
	source[low] = temp;

	return low;
}


