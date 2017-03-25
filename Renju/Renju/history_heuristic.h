#pragma once
#ifndef HISTORY_H
#define HISTORY_H

#include"define.h"
#include<string.h>

//历史启发工具类

class HistoryHeuristic {
public:
	HistoryHeuristic();
	~HistoryHeuristic();
	//清空历史得分表
	void ResetHistoryTable();
	//获取历史得分
	int GetHistoryScore(ChessMove move);
	//将某一最佳走法加入历史记录中
	void EnterHistoryScore(ChessMove move, int depth);
	//将所得数据排序
	static void QSort(ChessMove *source, int low, int high);
protected:

	static int Partition(ChessMove *source, int low, int high);

	//历史得分表
	int History_Table[BOARD_NUM][BOARD_NUM];//保存当前棋盘的历史得分

};
#endif