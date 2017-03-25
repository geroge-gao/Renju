#include "eveluation.h"
#include"define.h"
#include<string.h>
#include<stdio.h>

int PosValue[BOARD_NUM][BOARD_NUM] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0 },
	{ 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0 },
	{ 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0 },
	{ 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,6,7,6,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,6,6,6,5,4,3,2,1,0 },
	{ 0,1,2,3,4,5,5,5,5,5,4,3,2,1,0 },
	{ 0,1,2,3,4,4,4,4,4,4,4,3,2,1,0 },
	{ 0,1,2,3,3,3,3,3,3,3,3,3,2,1,0 },
	{ 0,1,2,2,2,2,2,2,2,2,2,2,2,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

//保存估值函数执行的次数
int count = 0;

Eveluation::Eveluation()
{

}

Eveluation::~Eveluation()
{

}

int Eveluation::evelutaion(int position[][BOARD_NUM], int isWhite)
{
	int ChessType;
	count++;//计数器+1

	memset(TypeRecord, UNANALYSISED, sizeof(TypeRecord));//对数组初始化赋值
	memset(TypeCount, 0, sizeof(TypeCount));

	//对棋盘上的棋子在四个方向上面进行分析
	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			if (position[i][j] != NOCHESS)
			{
				if (TypeRecord[i][j][0] == UNANALYSISED)
				{
					AnalysisHorizon(position, i, j);
				}

				if (TypeRecord[i][j][1] == UNANALYSISED)
				{
					AnalysisVertical(position, i, j);
				}

				if (TypeRecord[i][j][2] == UNANALYSISED)
				{
					AnalysisLeft(position, i, j);
				}

				if (TypeRecord[i][j][3] == UNANALYSISED)
				{
					AnalysisRight(position, i, j);

				}
			}
		}
	//对结果进行分析
	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
			for (int k = 0; k < 4; k++)
			{
				ChessType = position[i][j];
				if (ChessType != NOCHESS)
				{
					switch (TypeRecord[i][j][k])
					{
					case FIVE:
						TypeCount[ChessType][FIVE]++;
						break;
					case FOUR:
						TypeCount[ChessType][FOUR]++;
						break;
					case SFOUR:
						TypeCount[ChessType][SFOUR]++;
						break;
					case THREE:
						TypeCount[ChessType][THREE]++;
						break;
					case STHREE:
						TypeCount[ChessType][STHREE]++;
						break;
					case TWO:
						TypeCount[ChessType][TWO]++;
						break;
					case STWO:
						TypeCount[ChessType][STWO]++;
						break;
					default:
						break;
					}
				}
			}

	/*
	由于采用负极大极小值，所以现在开始自己赢了应该返回负值
	*/
	if (isWhite)
	{
		if (TypeCount[WHITE][FIVE])
		{
			return -20000;
		}

		if (TypeCount[BLACK][FIVE])
		{
			return 20000;
		}
	}
	else//黑子
	{
		if (TypeCount[BLACK][FIVE])
		{
			return -20000;
		}
		if (TypeCount[WHITE][FIVE])
		{
			return 20000;
		}
	}

	//两个冲四相当于一个活四
	if (TypeCount[WHITE][SFOUR] > 1)
	{
		TypeCount[WHITE][FOUR]++;
	}

	if (TypeCount[BLACK][SFOUR] > 1)
	{
		TypeCount[BLACK][FOUR]++;
	}

	int white_value = 0;
	int black_value = 0;

	if (TypeCount[WHITE][SFOUR] > 1)
		TypeCount[WHITE][FOUR]++;

	if (TypeCount[BLACK][SFOUR] > 1)
		TypeCount[BLACK][FOUR]++;

	//if (isWhite==WHITE)
	//{

	//	if (TypeCount[WHITE][FOUR])//白胜
	//	{
	//		white_value+=7000;
	//	}

	//	if (TypeCount[WHITE][SFOUR])//白胜
	//	{
	//		white_value += 7000;
	//	}

	//	if (TypeCount[BLACK][FOUR])//黑胜
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[BLACK][SFOUR] == 1)
	//	{
	//		black_value += 5000;
	//	}

	//	if (TypeCount[BLACK][SFOUR] && TypeCount[BLACK][THREE])//黑胜
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[WHITE][THREE] && TypeCount[BLACK][SFOUR] == 0)//白胜//此处需要修改
	//	{
	//		white_value += 4000;
	//	}

	//	if (TypeCount[BLACK][THREE] > 1 &&TypeCount[WHITE][SFOUR] == 0 &&TypeCount[WHITE][THREE] == 0 &&TypeCount[WHITE][STHREE] == 0)
	//	{
	//		black_value += 7000;
	//	}		

	//	if (TypeCount[WHITE][THREE] > 1)
	//		white_value+= 2000;
	//	else if (TypeCount[WHITE][THREE])			
	//			white_value += 200;

	//	if (TypeCount[BLACK][THREE] > 1)
	//		black_value += 500;
	//	else {
	//		if (TypeCount[BLACK][THREE])
	//			black_value += 100;
	//	}


	//	if (TypeCount[WHITE][STHREE])
	//		white_value += TypeCount[WHITE][STHREE] * 10;

	//	if (TypeCount[BLACK][STHREE])
	//		black_value += TypeCount[BLACK][STHREE] * 10;

	//	if (TypeCount[WHITE][TWO])
	//		white_value += TypeCount[WHITE][TWO] * 4;

	//	if (TypeCount[BLACK][TWO])
	//		black_value += TypeCount[BLACK][TWO] *4;

	//	if (TypeCount[WHITE][STWO])
	//		white_value += TypeCount[WHITE][STWO];

	//	if (TypeCount[BLACK][STWO])
	//		black_value += TypeCount[BLACK][STWO];


	//}
	//else//轮到黑子
	//{
	//	if (TypeCount[BLACK][FOUR])
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[BLACK][SFOUR])
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[WHITE][FOUR])
	//	{
	//		white_value += 7000;
	//	}

	//	if (TypeCount[WHITE][SFOUR])
	//	{
	//		white_value += 4000;
	//	}

	//	if (TypeCount[WHITE][SFOUR] && TypeCount[WHITE][THREE])
	//	{
	//		white_value += 7000;
	//	}

	//	if (TypeCount[BLACK][THREE] && TypeCount[WHITE][SFOUR] == 0)
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[WHITE][THREE] > 1 &&TypeCount[BLACK][SFOUR] == 0 &&TypeCount[BLACK][THREE] == 0 &&TypeCount[BLACK][STHREE] == 0)
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[BLACK][THREE] > 1)
	//		black_value += 2000;
	//	else {
	//		if (TypeCount[BLACK][THREE])
	//			black_value += 200;
	//	}

	//	if (TypeCount[WHITE][THREE] > 1)
	//		white_value += 500;
	//	else {
	//		if (TypeCount[WHITE][THREE])
	//			white_value += 100;
	//	}
	//	if (TypeCount[WHITE][STHREE])
	//		white_value += TypeCount[WHITE][STHREE] * 10;

	//	if (TypeCount[BLACK][STHREE])
	//		black_value += TypeCount[BLACK][STHREE] * 10;

	//	if (TypeCount[WHITE][TWO])
	//		white_value += TypeCount[WHITE][TWO] * 4;

	//	if (TypeCount[BLACK][STWO])
	//		black_value += TypeCount[BLACK][TWO] * 4;

	//	if (TypeCount[WHITE][STWO])
	//		white_value+= TypeCount[WHITE][STWO];

	//	if (TypeCount[BLACK][STWO])
	//		black_value += TypeCount[BLACK][STWO];

	//}

	if (isWhite == WHITE)
	{
		//白子四连
		if (TypeCount[WHITE][FOUR])
		{
			white_value += 8000;
		}

		if (TypeCount[WHITE][SFOUR])
		{
			white_value += 8000;
		}
		//黑子四连
		if (TypeCount[BLACK][FOUR])
		{
			black_value += 8000;
		}

		if (TypeCount[BLACK][SFOUR])
		{
			black_value += 1200;
		}
		//活三
		if (TypeCount[WHITE][THREE])
		{
			white_value += TypeCount[WHITE][THREE] * 1000;
		}

		if (TypeCount[BLACK][THREE])
		{
			black_value += TypeCount[BLACK][THREE] * 100;
		}

		//眠三
		if (TypeCount[WHITE][STHREE])
		{
			white_value += TypeCount[BLACK][STHREE] * 200;
		}

		if (TypeCount[BLACK][STHREE])
		{
			black_value += TypeCount[BLACK][STHREE] * 20;
		}
		//活儿
		if (TypeCount[WHITE][TWO])
		{
			white_value += TypeCount[WHITE][TWO] * 4;
		}

		if (TypeCount[BLACK][TWO])
		{
			black_value += TypeCount[BLACK][TWO] * 4;
		}

		//眠二
		if (TypeCount[WHITE][STWO])
		{
			white_value += TypeCount[WHITE][STWO] * 2;
		}

		if (TypeCount[BLACK][STWO])
		{
			black_value += TypeCount[BLACK][STWO] * 2;;
		}
	}
	else
	{

		//黑子四连
		if (TypeCount[BLACK][FOUR])
		{
			black_value += 8000;
		}

		if (TypeCount[BLACK][SFOUR])
		{
			black_value += 8000;
		}
		//白子四连
		if (TypeCount[WHITE][FOUR])
		{
			white_value += 8000;
		}

		if (TypeCount[WHITE][SFOUR])
		{
			white_value += 1200;
		}
		//活三
		if (TypeCount[BLACK][THREE])
		{
			black_value += TypeCount[BLACK][THREE] * 1000;
		}

		if (TypeCount[WHITE][THREE])
		{
			white_value += TypeCount[WHITE][THREE] * 100;
		}

		//眠三
		if (TypeCount[BLACK][STHREE])
		{
			black_value += TypeCount[BLACK][STHREE] * 200;
		}

		if (TypeCount[WHITE][STHREE])
		{
			white_value += TypeCount[WHITE][STHREE] * 20;
		}
		//活儿
		if (TypeCount[BLACK][TWO])
		{
			black_value += TypeCount[BLACK][TWO] * 4;
		}

		if (TypeCount[WHITE][TWO])
		{
			white_value += TypeCount[WHITE][TWO] * 4;
		}

		//眠二
		if (TypeCount[BLACK][STWO])
		{
			black_value += TypeCount[BLACK][STWO] * 2;
		}

		if (TypeCount[WHITE][STWO])
		{
			white_value += TypeCount[WHITE][STWO] * 2;;
		}
	}

	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			ChessType = position[i][j];
			if (ChessType != NOCHESS)
			{
				if (ChessType == BLACK)//当前的值加上本身属于的值
					black_value += PosValue[i][j];
				else
					white_value += PosValue[i][j];


			}
		}

	if (isWhite == WHITE)
	{
		return black_value - white_value; 
	}
	else
	{
		return white_value - black_value;
	}
}

//分析棋盘上面水平方向的棋局
int Eveluation::AnalysisHorizon(int position[][BOARD_NUM], int i, int j)
{
	AnalysisLine(position[i], 15, j);
	for (int s = 0; s < 15; s++)
	{
		if (LineRecord[s] != UNANALYSISED)
		{
			TypeRecord[i][s][0] = LineRecord[s];
		}
	}
	return TypeRecord[i][j][0];
}

//分析垂直方向的棋局
int Eveluation::AnalysisVertical(int position[][BOARD_NUM], int i, int j)
{
	int temp[BOARD_NUM];
	for (int s = 0; s < BOARD_NUM; s++)
	{
		temp[s] = position[s][j];
	}
	AnalysisLine(temp, BOARD_NUM, i);

	for (int s = 0; s < BOARD_NUM; s++)
	{
		TypeRecord[s][j][1] = LineRecord[s];
	}
	return TypeRecord[i][j][1];
}


//分析左对角线的棋局
int Eveluation::AnalysisLeft(int position[][BOARD_NUM], int i, int j)
{
	int temp[BOARD_NUM];
	int x, y, k;
	if (i < j)//上三角
	{
		y = 0;
		x = j - i;
	}
	else//下三角
	{
		y = i - j;
  		x = 0;
	}

	for (k = 0; k < BOARD_NUM; k++)
	{
		if (y + k > 14 || x + k > 14)
			break;
		temp[k] = position[y + k][x + k];
	}
	AnalysisLine(temp, k, j - x);

	for (int s = 0; s < k; s++)
	{
		if (LineRecord[s] != UNANALYSISED)
		{
			TypeRecord[y + s][x + s][2] = LineRecord[s];
		}
	}

	return TypeRecord[i][j][2];
}

//分析有对角线的棋局
int Eveluation::AnalysisRight(int position[][BOARD_NUM], int i, int j)
{
	int temp[BOARD_NUM];
	int x, y, k;
	if (i + j >14)
	{
		y = 14;
		x = i + j - 14;
	}
	else
	{
		x = 0;
		y = i + j;
	}

	for (k = 0; k < BOARD_NUM; k++)
	{
		if (y - k <0 || x + k > 14)
			break;
		temp[k] = position[y - k][x + k];
	}
	AnalysisLine(temp, k, j - x);

	for (int s = 0; s < k; s++)
	{
		if (LineRecord[s] != UNANALYSISED)
		{
			TypeRecord[y - s][x+s][3] = LineRecord[s];
		}
	}

	return TypeRecord[i][j][3];
}

int Eveluation::AnalysisLine(int position[], int Length, int pos)
{
	int ChessType;
	int AnalyLine[30];
	int AnalyPos;
	int LeftEdge, RightEdge;
	int LeftRange, rightRange;
	int leftfour;
	if (Length < 5)
	{
		//直接填写Length不行
		memset(LineRecord, ANALYSIED, sizeof(int)*Length);
		return 0;
	}

	AnalyPos = pos;
	memset(LineRecord, UNANALYSISED, sizeof(int) * 30);
	//将某一行的值复制到AnalyLine
	memcpy(AnalyLine, position, sizeof(int)*Length);
	Length--;//数组的最大下标
	ChessType = AnalyLine[pos];
	LeftEdge = AnalyPos;
	RightEdge = AnalyPos;

	while (LeftEdge > 0)
	{
		if (AnalyLine[LeftEdge - 1] != ChessType)
			break;

		LeftEdge--;
	}

	while (RightEdge < Length)
	{
		if (AnalyLine[RightEdge + 1] != ChessType)
			break;

		RightEdge++;
	}

	LeftRange = LeftEdge;
	rightRange = RightEdge;

	//推断能走的范围
	while (LeftRange > 0)
	{
		//如果不是对方棋子，则归于可走范围   o_oo类型
		if (AnalyLine[LeftRange - 1] == !ChessType)
			break;
		LeftRange--;
	}

	while (rightRange < Length)
	{
		if (AnalyLine[rightRange + 1] == !ChessType)
			break;
		rightRange++;
	}

	if (rightRange - LeftRange < 4)
	{
		//无论怎么走都不能连成五子
		for (int i = LeftRange; i <= rightRange; i++)
			LineRecord[i] = ANALYSIED;
		return FALSE;
	}

	for (int k = LeftEdge; k <= RightEdge; k++)
	{
		//分析连续区域
		LineRecord[k] = ANALYSIED;
	}

	if (RightEdge - LeftEdge == 4)
	{
		LineRecord[pos] = FIVE;
		return FIVE;
	}

	//四连
	leftfour = FALSE;
	if (RightEdge - LeftEdge == 3)
	{
		if (LeftEdge > 0)
		{
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
				leftfour = TRUE;
		}

		if (RightEdge < Length)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (leftfour)//_oooo_
					LineRecord[pos] = FOUR;//现在是标记当前分析点的位置
				else//|oooo_或xoooo_
					LineRecord[pos] = SFOUR;
			}
			else
			{
				if (leftfour)//_oooox
					LineRecord[pos] = SFOUR;
			}
		}
		else
		{
			if (leftfour)// _oooo|
				LineRecord[pos] = SFOUR;
		}

		return LineRecord[pos];
	}

	//如果棋子三连的话
	if (RightEdge - LeftEdge == 2)
	{
		int leftthree = FALSE;//表示左边是否可走
		if (LeftEdge > 0)
		{
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
			{
				if (LeftEdge > 1 && AnalyLine[LeftEdge - 2] == ChessType)//o_ooo
				{
					LineRecord[LeftEdge] = SFOUR;
					LineRecord[LeftEdge - 2] = ANALYSIED;
				}
				else//_ooo
				{
					leftthree = TRUE;
				}
			}
			else//xooo|  xooox
			{
				if (RightEdge == Length || AnalyLine[RightEdge + 1] != NOCHESS)//位置错误
					return FALSE;
			}
		}

		if (RightEdge < Length)//右边有空位置
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)//
			{
				if (RightEdge < Length - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
				{// ooo_o眠四
					LineRecord[RightEdge] = SFOUR;
					LineRecord[RightEdge + 2] = ANALYSIED;
				}
				else
				{
					if (leftthree)//_ooo_
					{
						LineRecord[RightEdge] = THREE;
					}
					else//|ooo_或xooo_
					{
						LineRecord[RightEdge] = STHREE;
					}
				}
			}
			else//右边有对方棋子
			{

				if (LineRecord[LeftEdge] == SFOUR)//o_ooox
				{
					return LineRecord[LeftEdge];
				}

				if (leftthree)//_ooox
				{
					LineRecord[pos] = STHREE;
				}
			}

			return LineRecord[pos];
		}
		else
		{
			//右边到底了，不能继续下
			if (LineRecord[LeftEdge] == SFOUR)//o_ooo|
			{
				return LineRecord[LeftEdge];
			}

			if (leftthree)// _ooo
			{
				LineRecord[pos] = STHREE;
			}
		}

		return LineRecord[pos];
	}

	//如果棋子两连
	if (RightEdge - LeftEdge == 1)
	{
		int lefttwo = FALSE;
		int leftthree = FALSE;
		if (LeftEdge > 2)
		{
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
			{
				if (AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
				{
					if (AnalyLine[LeftEdge - 3] == ChessType)//oo_oo
					{
						AnalyLine[LeftEdge - 3] = ANALYSIED;
						AnalyLine[LeftEdge - 2] = ANALYSIED;
						AnalyLine[LeftEdge] = SFOUR;
					}
					else//当AnalyLine[LeftEdge-3]为空，_o_oo,有敌方棋子时xo_oo
					{						
						LineRecord[LeftEdge - 2] = ANALYSIED;
						LineRecord[LeftEdge] = STHREE;
					}
				}
				else//__oo或x_oo
				{
					lefttwo = TRUE;//左边可落子
				}
			}
		}

		if (RightEdge < Length - 2)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
				{
					if (AnalyLine[RightEdge + 3] == AnalyLine[RightEdge])//oo_oo
					{
						LineRecord[RightEdge + 3] = ANALYSIED;
						LineRecord[RightEdge + 2] = ANALYSIED;
						LineRecord[RightEdge] = SFOUR;
					}
					else
					{
						//oo_o_或oo_ox
						LineRecord[RightEdge + 2] = ANALYSIED;
						if (lefttwo)//_oo_o_或_oo_ox
						{
							LineRecord[RightEdge] = STHREE;
						}
						else
						{
							//xoo_o_
							if (AnalyLine[RightEdge + 3] == NOCHESS)
							{
								LineRecord[RightEdge] = STHREE;
							}
						}

					}
				}
				else//oo_x或oo__
				{
					if (LineRecord[LeftEdge] == SFOUR)
					{
						return LineRecord[LeftEdge];
					}

					if (LineRecord[LeftEdge] == STHREE)
					{
						return LineRecord[LeftEdge];
					}

					if (lefttwo)
					{
						LineRecord[pos] = TWO;
					}
					else
					{
						LineRecord[pos] = STWO;
					}
				}
			}
			else
			{
				//oo_oox
				if (LineRecord[LeftEdge] == SFOUR)
				{
					return LineRecord[LeftEdge];
				}

				//o_oox
				if (LineRecord[LeftEdge] == STHREE)
				{
					return LineRecord[LeftEdge];
				}
				//_oox
				if (lefttwo)
				{
					LineRecord[pos] = STWO;
				}
			}
		}

		return LineRecord[pos];
	}

	return 0;
}

