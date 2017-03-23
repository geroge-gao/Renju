#include "eveluation.h"
#include"define.h"
#include<string.h>

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
			//�����鸳ֵ
	memset(TypeRecord, UNANALYSISED, BOARD_NUM * 4 * 4);
	memset(TypeCount, 0, 40 * 4);

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

	//����Ѿ��������飬���ؼ�ֵ
	if (isWhite)
	{
		if (TypeCount[WHITE][FIVE])
			return 9999;
		if (TypeCount[BLACK][FIVE])
			return -9999;
	}
	else
	{
		if (TypeCount[BLACK][FIVE])
			return 9999;
		if (TypeCount[WHITE][FIVE])
			return -9999;
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

	if (isWhite)
	{
		if (TypeCount[WHITE][FOUR])
		{
			return 9990;
		}

		if (TypeCount[WHITE][SFOUR])
		{
			return 9980;
		}

		if (TypeCount[BLACK][FOUR])
		{
			return -9970;
		}

		if (TypeCount[WHITE][THREE] && TypeCount[BLACK][SFOUR] == 0)
		{
			return 9950;
		}

		if (TypeCount[BLACK][THREE] > 1 && TypeCount[WHITE][SFOUR] == 0 && TypeCount[WHITE][THREE] == 0 && TypeCount[WHITE][STHREE] == 0)
		{
			return -9940;
		}

		//����ÿ��һ��������ֵ��2000
		if (TypeCount[WHITE][THREE] > 1)
		{
			white_value += 2000;
		}
		else if (TypeCount[WHITE][THREE] == 1)
		{
			white_value += 200;
		}

		//�����ж��������ÿ��һ����500��
		if (TypeCount[BLACK][THREE] > 1)
		{
			black_value += 500;
		}
		else if (TypeCount[BLACK][THREE] == 1)
		{
			black_value += 100;
		}

		if (TypeCount[WHITE][STHREE])
		{
			white_value += TypeCount[WHITE][STHREE] * 10;
		}

		if (TypeCount[BLACK][STHREE])
		{
			black_value += TypeCount[BLACK][STHREE] * 10;
		}

		if (TypeCount[WHITE][TWO])
		{
			white_value += TypeCount[WHITE][TWO];
		}

		if (TypeCount[BLACK][TWO])
		{
			black_value += TypeCount[BLACK][TWO];
		}

		if (TypeCount[WHITE][STWO])
		{
			white_value += TypeCount[WHITE][STWO];
		}

		if (TypeCount[BLACK][STWO])
		{
			black_value += TypeCount[BLACK][STWO];
		}

	}
	else//�ֵ�������
	{
		if (TypeCount[BLACK][FOUR])
		{
			return 9990;
		}

		if (TypeCount[BLACK][SFOUR])
		{
			return 9980;
		}

		if (TypeCount[WHITE][FOUR])
		{
			return -9970;
		}

		if (TypeCount[WHITE][SFOUR] && TypeCount[WHITE][THREE])
		{
			return -9960;
		}

		if (TypeCount[BLACK][THREE] && TypeCount[WHITE][SFOUR] == 0)
		{
			return 9950;
		}

		if (TypeCount[WHITE][THREE] > 1 && TypeCount[BLACK][SFOUR] == 0 && TypeCount[BLACK][THREE] == 0 && TypeCount[BLACK][STHREE] == 0)
		{
			return -9940;
		}

		if (TypeCount[BLACK][THREE] > 1)
			black_value += 2000;
		else if (TypeCount[BLACK][THREE] == 1)
		{
			black_value += 200;
		}

		if (TypeCount[WHITE][THREE] > 1)
		{
			white_value += 500;
		}
		else if (TypeCount[WHITE][THREE] == 1)
		{
			white_value += 100;
		}

		if (TypeCount[BLACK][THREE] > 1)
		{
			black_value += 500;
		}
		else if (TypeCount[BLACK][THREE] == 1)
		{
			black_value += 100;
		}
		//ÿ��������10
		if (TypeCount[WHITE][STHREE])
		{
			white_value += TypeCount[WHITE][STHREE] * 10;
		}

		if (TypeCount[BLACK][STHREE])
		{
			black_value += TypeCount[BLACK][STHREE] * 10;
		}

		if (TypeCount[WHITE][TWO])
		{
			white_value += TypeCount[WHITE][TWO];
		}

		if (TypeCount[BLACK][TWO])
		{
			black_value += TypeCount[BLACK][TWO];
		}

		if (TypeCount[WHITE][STWO])
		{
			white_value += TypeCount[WHITE][STWO];
		}

		if (TypeCount[BLACK][STWO])
		{
			black_value += TypeCount[BLACK][STWO];
		}
	}

	//�����������ӵ�λ��ֵ
	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			ChessType = position[i][j];
			if (ChessType == WHITE)
				white_value += PosValue[i][j];
			else
				black_value += PosValue[i][j];
		}

	if (isWhite)
		return white_value - black_value;
	else
		return black_value - white_value;
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
	AnalysisLine(temp, 15, i);

	for (int s = 0; s < BOARD_NUM; s++)
	{
		TypeRecord[s][j][1] = LineRecord[s];
	}
	return TypeRecord[i][j][1];
}


//�������Խ��ߵ����
int Eveluation::AnalysisLeft(int position[][BOARD_NUM], int i, int j)
{
	int temp[BOARD_NUM];
	int x, y, k;
	if (i < j)
	{
		y = 0;
		x = j - i;
	}
	else
	{
		y = i - j;
		x = 0;
	}

	for (k = 0; k < BOARD_NUM; k++)
	{
		if (y + k > 14 || x + k>14)
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
	if (i + j < 15)
	{
		y = 0;
		x = i + j;
	}
	else
	{
		y = i + j - 14;
		x = 14;
	}

	for (k = 0; k < BOARD_NUM; k++)
	{
		if (y + k > 14 || x - k < 0)
			break;
		temp[k] = position[y + k][x - k];
	}
	AnalysisLine(temp, k, j - y);

	for (int s = 0; s < k; s++)
	{
		if (LineRecord[s] != UNANALYSISED)
		{
			TypeRecord[y + s][x - s][3] = LineRecord[s];
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
		memset(LineRecord, ANALYSIED, Length);
		return 0;
	}

	AnalyPos = pos;
	memset(LineRecord, UNANALYSISED, 30);
	//��ĳһ�е�ֵ���Ƶ�AnalyLine
	memcpy(AnalyLine, position, Length);
	Length--;
	ChessType = AnalyLine[pos];
	LeftEdge = AnalyPos;
	RightEdge = AnalyPos;

	while (LeftEdge > 0)
	{
		if (AnalyLine[LeftEdge - 1] != ChessType)
			break;
		LeftEdge--;
	}

	while (RightEdge < 14)
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
		//������Ƕ������ӣ���һֱ̽����ȥ
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
		for (int i = LeftRange; i <= rightRange; i++)
			LineRecord[i] = AnalyLine[i];
		return FALSE;
	}

	for (int k = LeftEdge; k <= RightEdge; k++)
		LineRecord[k] = AnalyLine[k];

	if (RightEdge - LeftEdge > 3)
	{
		LineRecord[pos] = FIVE;
		return FIVE;
	}

	//����
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
				if (leftfour)
					LineRecord[pos] = FOUR;
				else
					LineRecord[pos] = SFOUR;
			}
			else
			{
				if (leftfour)
					LineRecord[pos] = SFOUR;
			}
		}
		else
		{
			if (leftfour)
				LineRecord[pos] = FOUR;
		}

		return LineRecord[pos];
	}

	//������������Ļ�
	if (RightEdge - LeftEdge == 2)
	{
		int leftthree = FALSE;
		if (LeftEdge > 0)
		{
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
			{
				leftthree = TRUE;
				if (AnalyLine[LeftEdge - 2] == ChessType)
				{
					LineRecord[LeftEdge] = SFOUR;
					LineRecord[LeftEdge - 2] = ANALYSIED;
				}
				/*	else
				{
				leftthree = TRUE;
				}*/
			}
			else
			{
				if (RightEdge == Length || AnalyLine[RightEdge + 1] == NOCHESS)
					return FALSE;
			}
		}

		if (RightEdge < Length)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (AnalyLine[RightEdge + 2] == ChessType)
				{
					LineRecord[RightEdge] = SFOUR;
					LineRecord[RightEdge + 2] = ANALYSIED;
				}
				else
				{
					if (leftthree)
					{
						LineRecord[RightEdge] = THREE;
					}
					else
					{
						LineRecord[RightEdge] = STHREE;
					}
				}
			}
			else//�ұ�������
			{
				//����ǻ������߻���֮��ģ�ֻ�ü�¼��һ���������ˡ�
				if (LineRecord[LeftEdge] == SFOUR)
				{
					return LineRecord[LeftEdge];
				}

				if (leftthree)
				{
					LineRecord[pos] = STHREE;
				}
			}

			return LineRecord[pos];
		}
		else
		{
			//�ұߵ����ˣ����ܼ�����
			if (LineRecord[LeftEdge] == SFOUR)
			{
				return LineRecord[LeftEdge];
			}

			if (leftthree)
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
			//������û����
			if (AnalyLine[LeftEdge - 1] == NOCHESS)
			{
				if (AnalyLine[LeftEdge - 2] == ChessType)
				{
					if (AnalyLine[LeftEdge - 3] == ChessType)
					{
						AnalyLine[LeftEdge - 3] = ANALYSIED;
						AnalyLine[LeftEdge - 2] = ANALYSIED;
						AnalyLine[LeftEdge] = SFOUR;
					}
					else
					{
						if (AnalyLine[LeftEdge - 3] == NOCHESS)
						{
							LineRecord[LeftEdge - 2] = ANALYSIED;
							LineRecord[LeftEdge] = STHREE;
						}
					}
				}
				else
				{
					lefttwo = TRUE;
				}
			}
		}

		if (RightEdge < Length - 2)
		{
			if (AnalyLine[RightEdge + 1] == NOCHESS)
			{
				if (AnalyLine[RightEdge + 2] == ChessType)
				{
					if (AnalyLine[RightEdge + 3] == ChessType)
					{
						LineRecord[RightEdge + 3] = ANALYSIED;
						LineRecord[RightEdge + 2] = ANALYSIED;
						LineRecord[RightEdge] = SFOUR;
					}
					else
					{
						if (AnalyLine[RightEdge + 3] == NOCHESS)
						{
							LineRecord[RightEdge + 2] = ANALYSIED;
							if (lefttwo)
								LineRecord[RightEdge] = TWO;
							else
								LineRecord[RightEdge] = STHREE;
						}
					}
				}
				else
				{
					if (LineRecord[LeftEdge] == SFOUR)
					{
						return LineRecord[LeftEdge];
					}

					if (LineRecord[LeftEdge] == STHREE)
					{
						LineRecord[LeftEdge] = THREE;
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
				if (LineRecord[LeftEdge] == SFOUR)
				{
					return LineRecord[LeftEdge];
				}

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

