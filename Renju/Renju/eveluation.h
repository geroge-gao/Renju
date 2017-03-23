#pragma once
#ifndef EVELUATION_H
#define EVELUATION_H

#define STWO 1//�߶�
#define STHREE 2//����
#define SFOUR 3//����
#define TWO 4//���
#define THREE 5//����
#define FOUR 6//����
#define FIVE 7//��������
#define NOTYPE 11//δ����
#define ANALYSIED 255//�Ѿ�����
#define UNANALYSISED 0//

#include"define.h"

//���Ӽ�ֵ��
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