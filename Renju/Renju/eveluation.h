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
#define UNANALYSISED 0//

#include"define.h"

//棋子价值表
extern int PosValue[15][15];

class Eveluation {
public:
	Eveluation();
	~Eveluation();
	int evelutaion(int position[][BOARD_NUM], int isWhite);
protected:
	int AnalysisHorizon(int position[][BOARD_NUM], int i, int j);
	int AnalysisVertical(int position[][BOARD_NUM], int i, int j);
	int AnalysisLeft(int position[][BOARD_NUM], int i, int j);
	int AnalysisRight(int position[][BOARD_NUM], int i, int j);
	int AnalysisLine(int position[], int Num, int p);
	int LineRecord[30];
	int TypeRecord[BOARD_NUM][BOARD_NUM][4];
	int TypeCount[2][20];
};

#endif