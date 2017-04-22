
#include"define.h"
#include"TranspositionTable.h"
#include<stdlib.h>

long long TranspositionTable::rand64()
{
	return rand() ^ ((long long)rand() << 15) ^ ((long long)rand() << 30) ^	((long long)rand() << 45) ^ ((long long)rand() << 60);
}

long TranspositionTable::rand32()
{
	return rand() ^ ((long)rand() << 15) ^ ((long)rand() << 30);
}

TranspositionTable::TranspositionTable()
{
	InitHashTable();
}

TranspositionTable::~TranspositionTable()
{
	delete m_pTT[0];
	delete m_pTT[1];
}

//���������������ڼ����ϣֵ���������
void TranspositionTable::InitHashTable()
{
	//�������������
	srand((unsigned)time_t(NULL));
	//����������
	for(int k=0;k<2;k++)
		for(int i=0;i<BOARD_NUM;i++)
			for (int j = 0; j < BOARD_NUM; j++)
			{
				m_nHashKey64[k][i][j] = rand64();
				m_nHashKey32[k][i][j] = rand32();
			}

	//�����û������ÿռ�
	m_pTT[0] = new HashItem[1024 * 1024];
	m_pTT[1] = new HashItem[1024 * 1024];
}

//���ݴ�������̼���32λ��64λ��ϣֵ
void TranspositionTable::CalculateInitHashKey(int CurPosition[][BOARD_NUM])
{
	int chesstype;
	m_HashKey32 = 0;
	m_HashKey64 = 0;
	//���������Ӷ�Ӧ��Hashֵ���
	for(int i=0;i<BOARD_NUM;i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			chesstype = CurPosition[i][j];
			if (chesstype != NOCHESS)
			{
				m_HashKey32 = m_HashKey32^m_nHashKey32[chesstype][i][j];
				m_HashKey64 = m_HashKey64^m_nHashKey64[chesstype][i][j];
			}
		}
}

//���ݴ�����߷����޸���Ӧ�Ĺ�ϣֵ
void TranspositionTable::Hash_MakeMove(ChessMove *move,int CurPosition[][BOARD_NUM])
{
	int type;
	type = CurPosition[move->ChessPos.y][move->ChessPos.x];
	m_HashKey32 = m_HashKey32^m_nHashKey32[type][move->ChessPos.y][move->ChessPos.x];
	m_HashKey64 = m_HashKey64^m_nHashKey64[type][move->ChessPos.y][move->ChessPos.x];
}

//�ָ��ı��Hashֵ
void TranspositionTable::Hash_UnMakeMove(ChessMove *move, int CurPosition[][BOARD_NUM])
{
	int type;
	type = CurPosition[move->ChessPos.y][move->ChessPos.x];
	//����������λ�������������ӹ�ϣֵ���г�ȥ
	m_HashKey32 = m_HashKey32^m_nHashKey32[type][move->ChessPos.y][move->ChessPos.x];
	m_HashKey64 = m_HashKey64^m_nHashKey64[type][move->ChessPos.y][move->ChessPos.x];
}

//����Hash��
int TranspositionTable::LookUpHashTable(int alpha, int beta, int depth, int TableNo)
{
	int x;
	HashItem *pht;
	x = m_HashKey32 & 0xFFFFF;
	pht = &m_pTT[TableNo][x];
	if (pht->depth>=depth&&pht->checksum == m_HashKey64)
	{
		switch (pht->entry_type)
		{
		case exact:
			return pht->eval;
		case lower_bound:
			if (pht->eval >= beta)
				return pht->eval;
			else
				break;
		case upper_bound:
			if (pht->eval <= alpha)
				return pht->eval;
			else
				break;
		}		
	}

	return 666666;//û�����У�������Ч���
}

//���û����в�������
void TranspositionTable::EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo)
{
	int x;
	HashItem *pht;
	x = m_HashKey32 & 0xFFFFF;//20λ��ϣ��ַ
	pht = &m_pTT[TableNo][x];//ȡ�������ָ�����

	pht->checksum = m_HashKey64;//64λУ����
	pht->entry_type = entry_type;//��������
	pht->eval = eval;//Ҫ�����ֵ
	pht->depth = depth;//�β�
}

