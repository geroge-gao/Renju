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
		return score;//���������ؼ�ֵ
	}

	return 0;//δ�����������ؼ�ֵ
}

//������������ȣ��ṩ���û��ӿ�ʹ��
void Search::SetSearchDepth(int depth)
{
	this->MaxDepth = depth;
}

//�����߷�������
void Search::SetMoveGenerator(MoveGenerator *mg)
{
	this->pmg = mg;
}

//������ʷ������
void Search::SetHistoryHeuristic(HistoryHeuristic *phh)
{
	this->hh = phh;
}

//������������
void Search::SetEveluation(Eveluation *evel)
{
	this->peval = evel;
}

//Ϊ��ǰ��ֲ���һ�ֺõ��߷�
int Search::SearchGoodMove(int position[][BOARD_NUM], int type)
{
	int Score,over;

	over = peval->evelutaion(position, !type);//�жϵ�ǰ����Ƿ��Ѿ�����
	if (fabs(over) > 9000)
	{
		return over;
	}	
	memcpy(CurPosition, position, sizeof(int)*BOARD_COUNT);//���浱ǰ����
	CurrentDepth = MaxDepth;
	Score = AlphaBeta(CurrentDepth, -20000, 20000);//���ص�ǰ�����ĵ÷�
	MakeMove(&BestMove,type);
	memcpy(position, CurPosition, sizeof(int)*BOARD_COUNT);//���Ƶ�ǰ�������� 
	over = IsGameOver(CurPosition, type);
	if (fabs(Score) > 9000)
		return Score;
	return 0;
}

int Search::AlphaBeta(int depth, int alpha, int beta)
{
	int score, over, Count, side;	
	side = ((MaxDepth - depth) % 2);//�жϵ�ǰ������һ��

	if (depth == 0)//����Ҷ�ӽڵ��ֵ
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
		UnMakeMove(&pmg->MoveList[depth][i]);//����֮ǰ���߷�

		if (score > alpha)//alpha��֦
		{
			alpha = score;
			if (depth == MaxDepth)//���浱ǰ���·��
			{
				BestMove = pmg->MoveList[depth][i];
			}
			best = i;//���浱ǰ���ڵ�
		}

		if (alpha > beta)//beta��֦
			break;
	}
		return alpha;
}