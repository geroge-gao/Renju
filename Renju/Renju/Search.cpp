#include"search.h"
#include<math.h>
#include<string.h>
#include<stdio.h>

Search::Search()
{

}

Search::~Search()
{

} 

void Search::MakeMove(ChessMove *move, int type)
{
	CurPosition[move->ChessPos.y][move->ChessPos.x] = type;
}

void Search::UnMakeMove(ChessMove *move)
{
	CurPosition[move->ChessPos.y][move->ChessPos.x] = NOCHESS;
}

int Search::IsGameOver(int position[][BOARD_NUM], int side)
{
	int  score;
	score =  peval->evelutaion(position,side);

	if (abs(score) > 9000)
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

//设置历史启发器
void Search::SetHistoryHeuristic(HistoryHeuristic *phh)
{
	this->hh = phh;
}

//设置评估函数
void Search::SetEveluation(Eveluation *evel)
{
	this->peval = evel;
}

//为当前棋局产生一种好的走法
int Search::SearchGoodMove(int position[][BOARD_NUM], int type)
{
	int Score,over;

	over = peval->evelutaion(position, !type);//判断当前棋局是否已经结束
	if (fabs(over) > 9000)
	{
		return over;
	}	
	memcpy(CurPosition, position, sizeof(int)*BOARD_COUNT);//保存当前棋盘
	CurrentDepth = MaxDepth;
	Score = AlphaBeta(CurrentDepth, -20000, 20000);//返回当前局数的得分
	MakeMove(&BestMove,type);
	memcpy(position, CurPosition, sizeof(int)*BOARD_COUNT);//复制当前所走棋盘 
	over = IsGameOver(CurPosition, type);
	if (fabs(Score) > 9000)
		return Score;
	return 0;
}

int Search::AlphaBeta(int depth, int alpha, int beta)
{
	int score, over, Count, side;	
	side = ((MaxDepth - depth) % 2);//判断当前输入哪一方

	if (depth == 0)//返回叶子节点估值
	{
		return peval->evelutaion(CurPosition, !side);
	}
	else if (depth != 0)
	{
		over = IsGameOver(CurPosition, side);
		if (fabs(over) > 9000)
			return over;
	}

	Count = pmg->PossibleMove(CurPosition, depth, side);
	HistoryHeuristic::QSort(pmg->MoveList[depth], 0, Count);
	int best = -1;
	for (int i = 0; i < Count; i++)
	{
		MakeMove(&pmg->MoveList[depth][i], side);
		score = -AlphaBeta(depth - 1, -beta, -alpha);
		UnMakeMove(&pmg->MoveList[depth][i]);//撤销之前的走法

		if (score > alpha)//alpha剪枝
		{
			alpha = score;
			if (depth == MaxDepth)//保存当前最佳路径
			{
				BestMove = pmg->MoveList[depth][i];
			}
			best = i;//保存当前最大节点
		}

		if (alpha > beta)//beta剪枝
			break;
	}
		return alpha;
}