#pragma once
#ifndef EVELUATION_H
#define EVELUATION_H

#define STWO 1//眠二
#define STHREE 2//眠三
#define SFOUR 3//冲四
#define TWO 4//活二
#define THREE 5//活三
#define FOUR 6//活四
#define FIVE 7//五子连珠
#define NOTYPE 11//未定义
#define ANALYSIED 255//已经分析
#define UNANALYSISED 0//未分析

#include"define.h"
#include"Generator.h"
#include"history_heuristic.h"
#include"eveluation.h"

//棋子价值表
extern int PosValue[15][15];

class Eveluation {
public:
	Eveluation();
	~Eveluation();
	int evelutaion(int position[][BOARD_NUM], int isWhite);	
protected:
	//分析水平方向 
	int AnalysisHorizon(int position[][BOARD_NUM], int i, int j);
	//分析垂直方向
	int AnalysisVertical(int position[][BOARD_NUM], int i, int j);
	//分析左边
	int AnalysisLeft(int position[][BOARD_NUM], int i, int j);
	//分析右边
	int AnalysisRight(int position[][BOARD_NUM], int i, int j);
	int AnalysisLine(int position[], int Num, int p);
	//记录分析的结果
	int LineRecord[30];
	//记录各个方向上面所形成的的棋局
	int TypeRecord[15][15][4];
	//记录黑白方棋盘上面的类型
	int TypeCount[2][20];
};

#endif