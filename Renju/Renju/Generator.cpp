#include"Generator.h"
#include"eveluation.h"
#include"history_heuristic.h"
MoveGenerator::MoveGenerator()
{

}

MoveGenerator::~MoveGenerator()
{

}

int MoveGenerator::AddMove(int ToX, int ToY, int Layer)
{
	MoveList[Layer][MoveCount].ChessPos.x = ToX;
	MoveList[Layer][MoveCount].ChessPos.y = ToY;
	MoveCount++;
	MoveList[Layer][MoveCount].Score = PosValue[ToX][ToY];
	return MoveCount;
}

int MoveGenerator::PossibleMove(int position[BOARD_NUM][BOARD_NUM], int Layer, int Side)
{
	//记录每一层的总步数
	MoveCount = 0;

	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			if (position[i][j] == NOCHESS)
				AddMove(j, i, Layer);
		}

	HistoryHeuristic::QSort(MoveList[Layer], 0, MoveCount - 1);
	return MoveCount;
}

