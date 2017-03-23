#pragma once
#ifndef GENERATOR_H
#define GENERATOR_H
#include"define.h"

class MoveGenerator {
public:
	MoveGenerator();
	~MoveGenerator();
	int PossibleMove(int position[BOARD_NUM][BOARD_NUM], int Layer, int Side);
	//保存走法的数组
	ChessMove MoveList[10][225];
protected:
	int AddMove(int ToX, int ToY, int Layer);
	int MoveCount;//记录每一层所能走的步数
};
#endif
