#pragma once
#ifndef HISTORY_H
#define HISTORY_H

#include"define.h"
#include<string.h>

//��ʷ����������

class HistoryHeuristic {
public:
	HistoryHeuristic();
	~HistoryHeuristic();
	//�����ʷ�÷ֱ�
	void ResetHistoryTable();
	//��ȡ��ʷ�÷�
	int GetHistoryScore(ChessMove move);
	//��ĳһ����߷�������ʷ��¼��
	void EnterHistoryScore(ChessMove move, int depth);
	//��������������
	static void QSort(ChessMove *source, int low, int high);
protected:

	static int Partition(ChessMove *source, int low, int high);

	//��ʷ�÷ֱ�
	int History_Table[BOARD_NUM][BOARD_NUM];//���浱ǰ���̵���ʷ�÷�

};
#endif