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

//�����ֵ����ִ�еĴ���
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
	count++;//������+1

	memset(TypeRecord, UNANALYSISED, sizeof(TypeRecord));//�������ʼ����ֵ
	memset(TypeCount, 0, sizeof(TypeCount));

	//�������ϵ��������ĸ�����������з���
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
	//�Խ�����з���
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
	���ڲ��ø�����Сֵ���������ڿ�ʼ�Լ�Ӯ��Ӧ�÷��ظ�ֵ
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
	else//����
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

	//���������൱��һ������
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

	//	if (TypeCount[WHITE][FOUR])//��ʤ
	//	{
	//		white_value+=7000;
	//	}

	//	if (TypeCount[WHITE][SFOUR])//��ʤ
	//	{
	//		white_value += 7000;
	//	}

	//	if (TypeCount[BLACK][FOUR])//��ʤ
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[BLACK][SFOUR] == 1)
	//	{
	//		black_value += 5000;
	//	}

	//	if (TypeCount[BLACK][SFOUR] && TypeCount[BLACK][THREE])//��ʤ
	//	{
	//		black_value += 7000;
	//	}

	//	if (TypeCount[WHITE][THREE] && TypeCount[BLACK][SFOUR] == 0)//��ʤ//�˴���Ҫ�޸�
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
	//else//�ֵ�����
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
		//��������
		if (TypeCount[WHITE][FOUR])
		{
			white_value += 8000;
		}

		if (TypeCount[WHITE][SFOUR])
		{
			white_value += 8000;
		}
		//��������
		if (TypeCount[BLACK][FOUR])
		{
			black_value += 8000;
		}

		if (TypeCount[BLACK][SFOUR])
		{
			black_value += 1200;
		}
		//����
		if (TypeCount[WHITE][THREE])
		{
			white_value += TypeCount[WHITE][THREE] * 1000;
		}

		if (TypeCount[BLACK][THREE])
		{
			black_value += TypeCount[BLACK][THREE] * 100;
		}

		//����
		if (TypeCount[WHITE][STHREE])
		{
			white_value += TypeCount[BLACK][STHREE] * 200;
		}

		if (TypeCount[BLACK][STHREE])
		{
			black_value += TypeCount[BLACK][STHREE] * 20;
		}
		//���
		if (TypeCount[WHITE][TWO])
		{
			white_value += TypeCount[WHITE][TWO] * 4;
		}

		if (TypeCount[BLACK][TWO])
		{
			black_value += TypeCount[BLACK][TWO] * 4;
		}

		//�߶�
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

		//��������
		if (TypeCount[BLACK][FOUR])
		{
			black_value += 8000;
		}

		if (TypeCount[BLACK][SFOUR])
		{
			black_value += 8000;
		}
		//��������
		if (TypeCount[WHITE][FOUR])
		{
			white_value += 8000;
		}

		if (TypeCount[WHITE][SFOUR])
		{
			white_value += 1200;
		}
		//����
		if (TypeCount[BLACK][THREE])
		{
			black_value += TypeCount[BLACK][THREE] * 1000;
		}

		if (TypeCount[WHITE][THREE])
		{
			white_value += TypeCount[WHITE][THREE] * 100;
		}

		//����
		if (TypeCount[BLACK][STHREE])
		{
			black_value += TypeCount[BLACK][STHREE] * 200;
		}

		if (TypeCount[WHITE][STHREE])
		{
			white_value += TypeCount[WHITE][STHREE] * 20;
		}
		//���
		if (TypeCount[BLACK][TWO])
		{
			black_value += TypeCount[BLACK][TWO] * 4;
		}

		if (TypeCount[WHITE][TWO])
		{
			white_value += TypeCount[WHITE][TWO] * 4;
		}

		//�߶�
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
				if (ChessType == BLACK)//��ǰ��ֵ���ϱ������ڵ�ֵ
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

//������������ˮƽ��������
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

//������ֱ��������
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


//������Խ��ߵ����
int Eveluation::AnalysisLeft(int position[][BOARD_NUM], int i, int j)
{
	int temp[BOARD_NUM];
	int x, y, k;
	if (i < j)//������
	{
		y = 0;
		x = j - i;
	}
	else//������
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

//�����жԽ��ߵ����
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
		//ֱ����дLength����
		memset(LineRecord, ANALYSIED, sizeof(int)*Length);
		return 0;
	}

	AnalyPos = pos;
	memset(LineRecord, UNANALYSISED, sizeof(int) * 30);
	//��ĳһ�е�ֵ���Ƶ�AnalyLine
	memcpy(AnalyLine, position, sizeof(int)*Length);
	Length--;//���������±�
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

	//�ƶ����ߵķ�Χ
	while (LeftRange > 0)
	{
		//������ǶԷ����ӣ�����ڿ��߷�Χ   o_oo����
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
		//������ô�߶�������������
		for (int i = LeftRange; i <= rightRange; i++)
			LineRecord[i] = ANALYSIED;
		return FALSE;
	}

	for (int k = LeftEdge; k <= RightEdge; k++)
	{
		//������������
		LineRecord[k] = ANALYSIED;
	}

	if (RightEdge - LeftEdge == 4)
	{
		LineRecord[pos] = FIVE;
		return FIVE;
	}

	//����
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
					LineRecord[pos] = FOUR;//�����Ǳ�ǵ�ǰ�������λ��
				else//|oooo_��xoooo_
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

	//������������Ļ�
	if (RightEdge - LeftEdge == 2)
	{
		int leftthree = FALSE;//��ʾ����Ƿ����
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
				if (RightEdge == Length || AnalyLine[RightEdge + 1] != NOCHESS)//λ�ô���
					return FALSE;
			}
		}

		if (RightEdge < Length)//�ұ��п�λ��
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)//
			{
				if (RightEdge < Length - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
				{// ooo_o����
					LineRecord[RightEdge] = SFOUR;
					LineRecord[RightEdge + 2] = ANALYSIED;
				}
				else
				{
					if (leftthree)//_ooo_
					{
						LineRecord[RightEdge] = THREE;
					}
					else//|ooo_��xooo_
					{
						LineRecord[RightEdge] = STHREE;
					}
				}
			}
			else//�ұ��жԷ�����
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
			//�ұߵ����ˣ����ܼ�����
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

	//�����������
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
					else//��AnalyLine[LeftEdge-3]Ϊ�գ�_o_oo,�ез�����ʱxo_oo
					{						
						LineRecord[LeftEdge - 2] = ANALYSIED;
						LineRecord[LeftEdge] = STHREE;
					}
				}
				else//__oo��x_oo
				{
					lefttwo = TRUE;//��߿�����
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
						//oo_o_��oo_ox
						LineRecord[RightEdge + 2] = ANALYSIED;
						if (lefttwo)//_oo_o_��_oo_ox
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
				else//oo_x��oo__
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

