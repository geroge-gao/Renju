#include"NegaScout.h"
#include"define.h"
#include"eveluation.h"
#include"TranspositionTable.h"
#include<math.h>

NegaScout::NegaScout()
{
	tt.InitHashTable();
	history_h.ResetHistoryTable();
}

NegaScout::~NegaScout()
{

}

void NegaScout::MakeMove(ChessMove *move, int type)
{
	CurPosition[move->ChessPos.y][move->ChessPos.x] = type;
}

void NegaScout::UnMakeMove(ChessMove *move)
{
	CurPosition[move->ChessPos.y][move->ChessPos.x] = NOCHESS;
}

int NegaScout::IsGameOver(int position[][BOARD_NUM], int type)
{
	int scores;
	scores = peval->evelutaion(position, type);
	if (fabs(scores)>15000)
	{
		return scores;//结束，返回极值
	}
	return 0;
}

void NegaScout::SetSearchDepth(int depth)
{
	this->MaxDepth = depth;
}


void NegaScout::SetMoveGenerator(MoveGenerator *mg)
{
	this->pmg = mg;
}

void NegaScout::SetHistoryHeuristic(HistoryHeuristic *phh)
{
	this->hh = phh;
}

void NegaScout::SetEveluation(Eveluation *evel)
{
	this->peval = evel;
}


int NegaScout::SearchGoodMove(int position[][BOARD_NUM], int type)
{
	int Score,over;
	over = -peval->evelutaion(position, type);
	if (fabs(over) > 15000)
	{
		return over;
	}
	tt.CalculateInitHashKey(position);//初始化哈希表
	history_h.ResetHistoryTable();
	memcpy(CurPosition, position, sizeof(int)*BOARD_NUM*BOARD_NUM);
	CurrentDepth = MaxDepth;
	Score = NegaScout_TT_HH(CurrentDepth, -50000, 50000);
	MakeMove(&BestMove, type);
	memcpy(position, CurPosition, BOARD_COUNT * sizeof(int));
	if (fabs(Score) > 15000)
	{
		return Score;
	}
	return 0;
}

int NegaScout::NegaScout_TT_HH(int depth, int alpha, int beta)
{
	int type,i;
	int a, b, t,side,score,over;
	
	side = (MaxDepth - depth) % 2;

	score = tt.LookUpHashTable(alpha, beta, depth, side);
	if (score != 666666)
		return score;

	if (depth == 0)
	{
		score = peval->evelutaion(CurPosition, !side);
		tt.EnterHashTable(exact, score, depth, side);
		return score;
	}

	int Count = pmg->PossibleMove(CurPosition,depth, side);

	for (int i = 0; i < Count; i++)
	{
		pmg->MoveList[depth][i].Score = history_h.GetHistoryScore(pmg->MoveList[depth][i]);
	}
	history_h.QSort(pmg->MoveList[depth], 0, Count);

	int best = -1;

	a = alpha;
	b = beta;
	int eval_is_exact = 0;
	for (int i = 0; i < Count; i++)
	{
		MakeMove(&pmg->MoveList[depth][i], side);
		tt.Hash_MakeMove(&pmg->MoveList[depth][i], CurPosition);
		t = -NegaScout_TT_HH(depth-1, -b, -a);
		
		if (t > a&&t < beta&&i>0)
		{
			eval_is_exact = 1;
			a = -NegaScout_TT_HH(depth - 1, -beta, -t);
			if (depth == MaxDepth)
				BestMove = pmg->MoveList[depth][i];
			best = i;
		}
		tt.Hash_UnMakeMove(&pmg->MoveList[depth][i], CurPosition);
		UnMakeMove(&pmg->MoveList[depth][i]);
		if (a < t)
		{
			eval_is_exact = 1;
			a = t;
			if (depth == MaxDepth)
				BestMove = pmg->MoveList[depth][i];
			
		}
		if (a >= beta)
		{
			tt.EnterHashTable(lower_bound, a, depth, side);
			history_h.EnterHistoryScore(pmg->MoveList[depth][i], depth);
			return a;
		}
		b = a + 1;
	}

	if (best != -1)
		history_h.EnterHistoryScore(pmg->MoveList[depth][best], depth);
	if (eval_is_exact == 1)
		tt.EnterHashTable(exact, a, depth, side);
	else
		tt.EnterHashTable(upper_bound, a, depth, side);

	return a;
}

