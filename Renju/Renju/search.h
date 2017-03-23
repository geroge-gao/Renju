#pragma once
#ifndef SEARCH_H
#define SEARCH_H
#include"define.h"
#include"Generator.h"
#include"eveluation.h"

#include"history_heuristic.h"

class Search {
public:
	Search();
	~Search();
	//Ϊ��ǰ���߳���һ��
	void SearchGoodMove(int position[][BOARD_NUM], int type);
	//��������������
	void SetSearchDepth(int depth);
	void SetMoveGenerator(MoveGenerator *mg);
protected:
	//����ĳһ�߷�����֮������
	int MakeMove(ChessMove *move, int type);
	//�ָ�֮ǰ������
	void UnMakeMove(ChessMove *move);
	//�ж���Ϸ�Ƿ��ս�
	int IsGameOver(int position[][BOARD_NUM], int depth);
	//������ǰ���·��
	int AlphaBeta(int depth, int alpha, int beta);
	//���浱ǰ������״̬
	int CurPosition[BOARD_NUM][BOARD_NUM];
	//��¼����߷��ı���
	ChessMove BestMove;
	//�߷�������ָ�� 
	MoveGenerator *pmg;
	//��ֵ����ָ��
	Eveluation *peval;
	//���������� 
	int MaxDepth;
	//��ǰ�������
	int CurrentDepth;
};
#endif