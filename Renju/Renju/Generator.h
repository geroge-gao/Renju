#pragma once
#ifndef GENERATOR_H
#define GENERATOR_H
#include"define.h"
class MoveGenerator {
public:
	MoveGenerator();
	~MoveGenerator();
	int PossibleMove(int position[BOARD_NUM][BOARD_NUM], int Layer, int Side);
	//�����߷�������
	ChessMove MoveList[10][225];
protected:
	int AddMove(int FromX, int ToX, int Layer);
	int MoveCount;//��¼ÿһ�������ߵĲ���
};
#endif
