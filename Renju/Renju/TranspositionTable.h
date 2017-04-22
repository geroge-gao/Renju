#pragma once
#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include<stdlib.h>
#include"define.h"

enum ENTRY_TYPE
{
	exact, lower_bound, upper_bound
};

typedef struct HashItem
{
	long long checksum;//64λУ����
	ENTRY_TYPE entry_type;//��������
	short depth;//�ݹ���
	short eval;//�ڵ��ֵ
}HashItem;

class TranspositionTable
{
public:
	TranspositionTable();
	virtual ~TranspositionTable();
	//��������������Hashֵ
	void CalculateInitHashKey(int Curposition[][BOARD_NUM]);
	//���������߷������������µ�Hashֵ
	void Hash_MakeMove(ChessMove *move,int CurPosition[][BOARD_NUM]);
	//�����������߷��Ĺ�ϣֵ����ԭ���߹�֮ǰ��
	void Hash_UnMakeMove(ChessMove *move,int CurPosition[][BOARD_NUM]);
	//��ѯHash���е�ǰ�ڵ�����
	int LookUpHashTable(int alpha, int beta, int depth, int TableNo);
	//����ǰ�ڵ��ֵ����Hash��
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo);
	//��ʼ��������ݣ�����Hash��
	void InitHashTable();
	//32λ������飬����32λ��ϣֵ
	unsigned int m_nHashKey32[2][15][15];
	//64λ������飬����64λ��ϣֵ
	unsigned long long m_nHashKey64[2][15][15];

	long long rand64();
	long rand32();
	//�û���ͷָ��
	HashItem *m_pTT[2];
	unsigned int m_HashKey32;//32λ��ϣֵ
	unsigned long long m_HashKey64;//64λHashֵ
};


#endif // !TTable