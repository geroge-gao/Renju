#pragma once
#ifndef define_h
#define define_h

//����ĸ��ֱ���
#define BOARD_NUM 15
#define BOARD_COUNT 225
#define BLACK 1
#define WHITE 0
#define NOCHESS -1
#define TRUE 1
#define FALSE 0

typedef struct Position {
	int x;
	int y;
}Position;

typedef struct ChessMove {
	Position ChessPos;
	int Score;
}ChessMove;

#endif 

