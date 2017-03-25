#include<iostream>
#include"search.h"
#include"define.h"
#include"Generator.h"
#include"history_heuristic.h" 
using namespace std;

//计算机棋盘
int curpos[BOARD_NUM][BOARD_NUM] = {NOCHESS};
//人类棋盘
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
	//输出列表
	printf("   ");
	for (int i = 0; i < BOARD_NUM; i++)
	{
		printf("%3d", i + 1);
	}
	printf("\n");

	//输出行标
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
	int a, b;//人类选手要下的位置
	int depth=1;//当前搜索深度为三层
	Search s;//创建搜索引擎
	HistoryHeuristic hh;
	Eveluation evel;
	MoveGenerator mg;	

	s.SetSearchDepth(depth);//设置搜索深度
	s.SetHistoryHeuristic(&hh);//设置历史启发器
	s.SetEveluation(&evel);//设置评估函数
	s.SetMoveGenerator(&mg);//设置走法器
	memset(curpos, NOCHESS, sizeof(curpos));//初始化棋盘
	Transfer();
	Print(pos);
	int t = 0;	
	while (t==0)
	{
		cout << "please input:";
		cin >> a >> b;
		curpos[a - 1][b - 1] = BLACK;//自己先手黑子，电脑默认为白子
		t=s.SearchGoodMove(curpos, WHITE);
		system("CLS");
		Transfer();
		Print(pos);
	}

	if (t < 0)
		printf("电脑胜!\n");
	else
		printf("恭喜你，胜利!\n");
	system("pause");
	return 0;
}