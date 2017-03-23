#include"search.h"
#include<math.h>
#include<string.h>
#include"history_heuristic.h"

Search::Search()
{

}

Search::~Search()
{
	delete pmg;
	delete peval;
}

int Search::MakeMove(ChessMove *move, int type)
{
	CurPosition[move->ChessPos.y][move->ChessPos.x] = type;
	return  0;
}

void Search::UnMakeMove(ChessMove *move)
{
	CurPosition[move->ChessPos.y][move->ChessPos.x] = NOCHESS;
}

int Search::IsGameOver(int position[][BOARD_NUM], int depth)
{
	int i, score;
	i = (MaxDepth - depth) % 2;
	score = peval->evelutaion(position, i);

	if (abs(score) > 8000)
	{
		return score;//结束，返回极值
	}

	return 0;//未结束，不返回极值
}

//设置搜索的深度，提供给用户接口使用
void Search::SetSearchDepth(int depth)
{
	this->MaxDepth = depth;
}

//设置走法产生器
void Search::SetMoveGenerator(MoveGenerator *mg)
{
	this->pmg = mg;
}

void Search::SearchGoodMove(int position[][BOARD_NUM], int type)
{
	int Score;
	memcpy(CurPosition, position, BOARD_NUM*BOARD_NUM);
	CurrentDepth = MaxDepth;
	Score = AlphaBeta(CurrentDepth, -20000, 20000);

	if (CurPosition[BestMove.ChessPos.y][BestMove.ChessPos.x] != NOCHESS)
	{
	}
}

int Search::AlphaBeta(int depth, int alpha, int beta)
{
	return 0;
}

