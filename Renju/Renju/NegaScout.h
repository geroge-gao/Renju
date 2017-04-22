#pragma once
#ifndef NEGASCOUT_H
#define NEGASCOUT_H
#include"define.h"
#include"Generator.h"
#include"eveluation.h"
#include"history_heuristic.h"
#include"TranspositionTable.h"

class NegaScout
{
public:
	NegaScout();
	~NegaScout();
	int SearchGoodMove(int position[][BOARD_NUM], int type);
	//��������������
	void SetSearchDepth(int depth);
	//�ж���Ϸ�Ƿ��ս�
	int IsGameOver(int position[][BOARD_NUM], int depth);
	//���ò�����
	void SetMoveGenerator(MoveGenerator *mg);
	//������ʷ������
	void SetHistoryHeuristic(HistoryHeuristic *phh);
	//������������
	void SetEveluation(Eveluation *evel);
protected:
	//����ĳһ�߷�����֮������
	void MakeMove(ChessMove *move, int type);
	//�ָ�֮ǰ������
	void UnMakeMove(ChessMove *move);

	//������ǰ���·��
	int NegaScout_TT_HH(int depth, int alpha, int beta);

	//���浱ǰ������״̬
	int CurPosition[BOARD_NUM][BOARD_NUM];
	//��¼����߷��ı���
	ChessMove BestMove;
	//�߷�������ָ�� 
	MoveGenerator *pmg;
	//��ֵ����ָ��
	Eveluation *peval;
	//��ʷ������ָ�� 
	HistoryHeuristic *hh;
	//���������� 
	int MaxDepth;
	//��ǰ�������
	int CurrentDepth;
	HistoryHeuristic history_h;//��ʷ�û���
	TranspositionTable tt;
};


#endif