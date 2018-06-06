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
	//设置最大搜索深度
	void SetSearchDepth(int depth);
	//判断游戏是否终结
	int IsGameOver(int position[][BOARD_NUM], int depth);
	//设置产生器
	void SetMoveGenerator(MoveGenerator *mg);
	//设置历史启发器
	void SetHistoryHeuristic(HistoryHeuristic *phh);
	//设置评估函数
	void SetEveluation(Eveluation *evel);
protected:
	//根据某一走法产生之后的棋局
	void MakeMove(ChessMove *move, int type);
	//恢复之前的棋盘
	void UnMakeMove(ChessMove *move);

	//搜索当前最佳路径
	int NegaScout_TT_HH(int depth, int alpha, int beta);

	//保存当前的棋盘状态
	int CurPosition[BOARD_NUM][BOARD_NUM];
	//记录最佳走法的变量
	ChessMove BestMove;
	//走法产生器指针 
	MoveGenerator *pmg;
	//估值核心指针
	Eveluation *peval;
	//历史启发表指针 
	HistoryHeuristic *hh;
	//最大搜索深度 
	int MaxDepth;
	//当前搜索深度
	int CurrentDepth;
	HistoryHeuristic history_h;//历史置换表
	TranspositionTable tt;
};


#endif