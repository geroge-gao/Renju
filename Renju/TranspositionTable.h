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
	long long checksum;//64位校验码
	ENTRY_TYPE entry_type;//数据类型
	short depth;//递归层度
	short eval;//节点的值
}HashItem;

class TranspositionTable
{
public:
	TranspositionTable();
	virtual ~TranspositionTable();
	//计算棋盘所给的Hash值
	void CalculateInitHashKey(int Curposition[][BOARD_NUM]);
	//根据所给走法，增量生成新的Hash值
	void Hash_MakeMove(ChessMove *move,int CurPosition[][BOARD_NUM]);
	//撤销所给的走法的哈希值，还原成走过之前的
	void Hash_UnMakeMove(ChessMove *move,int CurPosition[][BOARD_NUM]);
	//查询Hash表中当前节点数据
	int LookUpHashTable(int alpha, int beta, int depth, int TableNo);
	//将当前节点的值存入Hash表
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo);
	//初始化随机数据，创建Hash表
	void InitHashTable();
	//32位随机数组，生成32位哈希值
	unsigned int m_nHashKey32[2][15][15];
	//64位随机数组，生成64位哈希值
	unsigned long long m_nHashKey64[2][15][15];

	long long rand64();
	long rand32();
	//置换表头指针
	HashItem *m_pTT[2];
	unsigned int m_HashKey32;//32位哈希值
	unsigned long long m_HashKey64;//64位Hash值
};


#endif // !TTable