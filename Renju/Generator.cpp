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
	MoveList[Layer][MoveCount].Score = PosValue[ToY][ToX];
	MoveCount++;
	return MoveCount;
}

int MoveGenerator::PossibleMove(int position[BOARD_NUM][BOARD_NUM], int Layer, int Side)
{
	
	MoveCount = 0;//¼ÇÂ¼Ã¿Ò»²ãµÄ×Ü²½Êý
	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			if (position[i][j] == NOCHESS)
				AddMove(j, i, Layer);
		}
	return MoveCount;
}

