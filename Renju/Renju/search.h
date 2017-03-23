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
	//为当前局走出下一步
	void SearchGoodMove(int position[][BOARD_NUM], int type);
	//设置最大搜索深度
	void SetSearchDepth(int depth);
	void SetMoveGenerator(MoveGenerator *mg);
protected:
	//根据某一走法产生之后的棋局
	int MakeMove(ChessMove *move, int type);
	//恢复之前的棋盘
	void UnMakeMove(ChessMove *move);
	//判断游戏是否终结
	int IsGameOver(int position[][BOARD_NUM], int depth);
	//搜索当前最佳路径
	int AlphaBeta(int depth, int alpha, int beta);
	//保存当前的棋盘状态
	int CurPosition[BOARD_NUM][BOARD_NUM];
	//记录最佳走法的变量
	ChessMove BestMove;
	//走法产生器指针 
	MoveGenerator *pmg;
	//估值核心指针
	Eveluation *peval;
	//最大搜索深度 
	int MaxDepth;
	//当前搜索深度
	int CurrentDepth;
};
#endif