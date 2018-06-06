
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

//函数用于生成用于计算哈希值的随机数组
void TranspositionTable::InitHashTable()
{
	//设置随机数种子
	srand((unsigned)time_t(NULL));
	//填充随机数组
	for(int k=0;k<2;k++)
		for(int i=0;i<BOARD_NUM;i++)
			for (int j = 0; j < BOARD_NUM; j++)
			{
				m_nHashKey64[k][i][j] = rand64();
				m_nHashKey32[k][i][j] = rand32();
			}

	//申请置换表所用空间
	m_pTT[0] = new HashItem[1024 * 1024];
	m_pTT[1] = new HashItem[1024 * 1024];
}

//根据传入的棋盘计算32位及64位哈希值
void TranspositionTable::CalculateInitHashKey(int CurPosition[][BOARD_NUM])
{
	int chesstype;
	m_HashKey32 = 0;
	m_HashKey64 = 0;
	//将所有棋子对应的Hash值相加
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

//根据传入的走法，修改相应的哈希值
void TranspositionTable::Hash_MakeMove(ChessMove *move,int CurPosition[][BOARD_NUM])
{
	int type;
	type = CurPosition[move->ChessPos.y][move->ChessPos.x];
	m_HashKey32 = m_HashKey32^m_nHashKey32[type][move->ChessPos.y][move->ChessPos.x];
	m_HashKey64 = m_HashKey64^m_nHashKey64[type][move->ChessPos.y][move->ChessPos.x];
}

//恢复改变的Hash值
void TranspositionTable::Hash_UnMakeMove(ChessMove *move, int CurPosition[][BOARD_NUM])
{
	int type;
	type = CurPosition[move->ChessPos.y][move->ChessPos.x];
	//将棋子现在位置上面的随机数从哈希值当中除去
	m_HashKey32 = m_HashKey32^m_nHashKey32[type][move->ChessPos.y][move->ChessPos.x];
	m_HashKey64 = m_HashKey64^m_nHashKey64[type][move->ChessPos.y][move->ChessPos.x];
}

//查找Hash表
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

	return 666666;//没有命中，返回无效标记
}

//向置换表中插入数据
void TranspositionTable::EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo)
{
	int x;
	HashItem *pht;
	x = m_HashKey32 & 0xFFFFF;//20位哈希地址
	pht = &m_pTT[TableNo][x];//取到具体的指针表项

	pht->checksum = m_HashKey64;//64位校验码
	pht->entry_type = entry_type;//表项类型
	pht->eval = eval;//要保存的值
	pht->depth = depth;//参差
}

