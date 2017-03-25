#include<iostream>
#include"search.h"
#include"define.h"
#include"Generator.h"
#include"history_heuristic.h" 
using namespace std;

//���������
int curpos[BOARD_NUM][BOARD_NUM] = {NOCHESS};
//��������
char pos[BOARD_NUM][BOARD_NUM];

void InitChess()
{
	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
			curpos[i][j] = NOCHESS;
}

void Transfer()
{
	for (int i = 0; i < BOARD_NUM; i++)
		for (int j = 0; j < BOARD_NUM; j++)
		{
			if (curpos[i][j] == BLACK)
			{
				pos[i][j] = 'O';
			}
			else if (curpos[i][j] == WHITE)
			{
				pos[i][j] = 'X';
			}
			else
			{
				pos[i][j] = '.';//
			}
		}
}

void Print(char a[][BOARD_NUM])
{
	//����б�
	printf("   ");
	for (int i = 0; i < BOARD_NUM; i++)
	{
		printf("%3d", i + 1);
	}
	printf("\n");

	//����б�
	for (int i = 0; i < BOARD_NUM; i++)
	{
		printf("%3d", i + 1);
		for (int j = 0; j < BOARD_NUM; j++)
		{
			printf("  %c", a[i][j]);
		} 
		printf("\n");
	}
}

int main()
{
	int a, b;//����ѡ��Ҫ�µ�λ��
	int depth=1;//��ǰ�������Ϊ����
	Search s;//������������
	HistoryHeuristic hh;
	Eveluation evel;
	MoveGenerator mg;	

	s.SetSearchDepth(depth);//�����������
	s.SetHistoryHeuristic(&hh);//������ʷ������
	s.SetEveluation(&evel);//������������
	s.SetMoveGenerator(&mg);//�����߷���
	memset(curpos, NOCHESS, sizeof(curpos));//��ʼ������
	Transfer();
	Print(pos);
	int t = 0;	
	while (t==0)
	{
		cout << "please input:";
		cin >> a >> b;
		curpos[a - 1][b - 1] = BLACK;//�Լ����ֺ��ӣ�����Ĭ��Ϊ����
		t=s.SearchGoodMove(curpos, WHITE);
		system("CLS");
		Transfer();
		Print(pos);
	}

	if (t < 0)
		printf("����ʤ!\n");
	else
		printf("��ϲ�㣬ʤ��!\n");
	system("pause");
	return 0;
}