#include<stdio.h>
#include<conio.h>   //使用getch()函数
#include<time.h>
#include <stdlib.h>

int num[4][4];
int score, gameover, ifappear, gamew, gamef, move;
char key;

void explation() {
	void menu();
	system("cls");
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t*****************************************\n");
	printf("\t\t******************游戏规则***************\n");
	printf("\t\t*****************************************\n");
	printf("\t\t*****************************************\t\t\n");
	printf("玩家可以选择上、下、左、右或W、A、S、D去移动滑块\n");
	printf("玩家选择的方向上若有相同的数字则合并\n");
	printf("合并所得的所有新生成数字相加即为该步的有效得分\n");
	printf("玩家选择的方向行或列前方有空格则出现位移\n");
	printf("每移动一步，空位随机出现一个2或4\n");
	printf("棋盘被数字填满，无法进行有效移动，判负，游戏结束\n");
	printf("棋盘上出现2048，获胜，游戏结束\n");
	printf("按上下左右去移动滑块\n");
	printf("请按任意键返回主菜单...\n");
	getch();
	system("cls");
	main();
}

void gamefaile() {
	int i, j;
	system("cls");
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t*****************************************\n");
	printf("\t\t******************you fail***************\n");
	printf("\t\t*****************************************\n");
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t\t---------------------\n\t\t\t");
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++)
			if (num[j][i] == 0)
				printf("|    ");
			else
				printf("|%4d", num[j][i]);
		printf("|\n");
		printf("\t\t\t---------------------\n\t\t\t");
	}
	printf("你的成绩：%d,移动了%d步\n", score, move);
	printf("请按任意键返回主菜单...\n");
	getch();
	system("cls");
	main();

}

void gamewin() {
	int i, j;
	system("cls");
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t*****************************************\n");
	printf("\t\t*******************you win***************\n");
	printf("\t\t*****************************************\n");
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t\t---------------------\n\t\t\t");
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++)
			if (num[j][i] == 0)
				printf("|    ");
			else
				printf("|%4d", num[j][i]);
		printf("|\n");
		printf("\t\t\t---------------------\n\t\t\t");
	}
	printf("你的成绩：%d,移动了%d步\n", score, move);
	printf("请按任意键返回主菜单...\n");
	getch();
	system("cls");
	main();
}

void prin() {
	int i, j;
	system("cls");
	printf("\t\t*****************************************\t\t\n");//输出界面
	printf("\t\t*****************************************\n");
	printf("\t\t******************游戏开始***************\n");
	printf("\t\t*****************************************\n");
	printf("\t\t*****************************************\t\t\n");
	printf("\t\t      请按方向键或W、A、S、D移动滑块\n");//输出操作提示语句
	printf("\t\t          按ESC返回至主菜单\n");
	printf("\t\t\t---------------------\n\t\t\t");
	for (j = 0; j < 4; j++)                 //输出4*4的表格
	{
		for (i = 0; i < 4; i++)
			if (num[j][i] == 0)
				printf("|    ");
			else
				printf("|%4d", num[j][i]);
		printf("|\n");
		printf("\t\t\t---------------------\n\t\t\t");
	}
	printf("你的成绩：%d，移动了%d步\n", score, move);//输出得分和移动步数
}

void appear() {
	int i, j, ran, t[16], x = 0, a, b;
	srand((int) time(0));          //随机种子初始化
	for (j = 0; j < 4; j++)      //将空白的区域的坐标保存到中间数组t中
		for (i = 0; i < 4; i++)
			if (num[j][i] == 0) {
				t[x] = j * 10 + i;
				x++;
			}
	if (x == 1)            //在t中随机取一个坐标
		ran = x - 1;
	else
		ran = rand() % (x - 1);
	a = t[ran] / 10;      //取出这个数值的十位数
	b = t[ran] % 10;     //取出这个数值的个位数
	srand((int) time(0));
	if ((rand() % 9) > 2)    //在此空白区域随机赋值2或4
		num[a][b] = 2;
	else
		num[a][b] = 4;
}

void close() {
	exit(0);
}

void add(int* p) {

	int i = 0, b;
	while (i < 3) {
		if (*(p + i) != 0) {
			for (b = i + 1; b < 4; b++) {
				if (*(p + b) != 0)
					if (*(p + i) == *(p + b)) {
						score = score + (*(p + i)) + (*(p + b));
						*(p + i) = *(p + i) + *(p + b);
						if (*(p + i) == 2048)
							gamew = 1;
						*(p + b) = 0;
						i = b + i;
						++ifappear;
						break;
					} else {
						i = b;
						break;
					}
			}
			if (b == 4)
				i++;
		} else
			i++;
	}

}

void Gameplay() {
	int i, j, g, e, a, b[4];
	appear();
	appear();
	while (1) {
		if (ifappear != 0)
			appear();
		prin();
		key = getch();
		switch (key) {
			case 'w':
			case 'W':
			case 72:
				ifappear = 0;
				for (j = 0; j < 4; j++) {
					for (i = 0; i < 4; i++) {
						b[i] = num[i][j];
						num[i][j] = 0;
					}
					add(b);
					e = 0;
					for (g = 0; g < 4; g++) {
						if (b[g] != 0) {
							num[e][j] = b[g];
							if (g != e)
								++ifappear;
							e++;
						}
					}
				}
				if (ifappear != 0)
					++move;
				break;
			case 's':
			case 'S':
			case 80:
				ifappear = 0;
				for (j = 0; j < 4; j++) {
					for (i = 0; i < 4; i++) {
						b[i] = num[i][j];
						num[i][j] = 0;
					}
					add(b);
					e = 3;
					for (g = 3; g >= 0; g--) {
						if (b[g] != 0) {
							num[e][j] = b[g];
							if (g != e)
								++ifappear;
							e--;
						}
					}
				}
				if (ifappear != 0)
					++move;
				break;
			case 'a':
			case 'A':
			case 75:
				ifappear = 0;
				for (j = 0; j < 4; j++) {
					for (i = 0; i < 4; i++) {
						b[i] = num[j][i];
						num[j][i] = 0;
					}
					add(b);
					e = 0;
					for (g = 0; g < 4; g++) {
						if (b[g] != 0) {
							num[j][e] = b[g];
							if (g != e)
								++ifappear;
							e++;
						}
					}
				}
				if (ifappear != 0)
					++move;
				break;
			case 'd':
			case 'D':
			case 77:
				ifappear = 0;
				for (j = 0; j < 4; j++) {
					for (i = 0; i < 4; i++) {
						b[i] = num[j][i];
						num[j][i] = 0;
					}
					add(b);
					e = 3;
					for (g = 3; g >= 0; g--) {
						if (b[g] != 0) {
							num[j][e] = b[g];
							if (g != e)
								++ifappear;
							e--;
						}
					}
				}
				if (ifappear != 0)
					++move;
				break;
			case 27:
				system("cls");
				main();
				break;

		}
		for (j = 0; j < 4; j++) {
			for (i = 0; i < 4; i++) {
				if (j < 3) {
					if (i < 3) {
						if (num[j][i] == num[j + 1][i] || num[j][i] == num[j][i + 1] || num[j][i] == 0) {
							gamef = 0;
							break;
						} else
							gamef = 1;
					} else {
						if (num[j][i] == num[j + 1][i] || num[j][i] == 0) {
							gamef = 0;
							break;
						} else
							gamef = 1;
					}
				} else {
					if (i < 3) {
						if (num[j][i] == num[j][i + 1] || num[j][i] == 0 || num[j][i + 1] == 0) {
							gamef = 0;
							break;
						} else
							gamef = 1;
					}
				}

			}
			if (gamef == 0)
				break;
		}
		if (gamef == 1 || gamew == 1)
			break;

	}
	if (gamef == 1)
		gamefaile();
	else
		gamewin();
}

void menu() {
	int n;
	printf("\t\t*****************************************\t\t\n");            //输出游戏菜单的图形
	printf("\t\t*              1、开始游戏              *\n");
	printf("\t\t*              2、游戏规则              *\n");
	printf("\t\t*              3、退出游戏              *\n");
	printf("\t\t*****************************************\n");
	printf("请输入1或2或3:[ ]\b\b");
	scanf("%d", &n);
	switch (n) {
		case 1:
			Gameplay();                                                         //游戏开始函数
			break;
		case 2:
			explation();                                                       //游戏规则函数
			break;
		case 3:
			close();                                                          //关闭游戏函数
			break;
	}
}

int main() {
	int j, i;
	for (j = 0; j < 4; j++)             //对4*4进行初始赋值为0
		for (i = 0; i < 4; i++)
			num[j][i] = 0;
	gamew = 0;                        //游戏获胜的判断变量初始化
	gamef = 0;                       //游戏失败的判断变量初始化
	ifappear = 0;                   //判断是否应该随机出现2或4的变量初始化
	score = 0;                     //游戏得分变量初始化
	gameover = 0;                 //游戏是否结束的变量初始化
	move = 0;                    //游戏的移动步数初始化
	menu();                     //调用主菜单函数
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int main() {
	int i, j;
	int x = 5;
	int y = 10;
	char input;
	int target_x = 5;
	int target_y = 5;

	int isFired = 0;
	int isKilled = 0;

	while (1) {
		system("cls");

		//如果没击中靶子，就显示靶子
		if (isKilled == 0) {
			for (i = 0; i < target_y; ++i) {
				printf("\n");
			}
			for (i = 0; i < target_x; ++i) {
				printf(" ");
			}

			printf("+\n");

		}

		if (isFired == 0) {
			for (i = 0; i < y; ++i) {
				printf("\n");
			}
		} else//如果开火，有竖线
		{
			for (i = 0; i < y; ++i) {
				for (j = 0; j < x; ++j) {
					printf(" ");
				}
				printf("  |\n");
			}

			if (x + 2 == target_x) {
				isKilled = 1;
			}

			isFired = 0;
		}
		for (j = 0; j < x; ++j) {
			printf(" ");
		}
		printf("  *\n");
		for (i = 0; i < x; ++i) {
			printf(" ");
		}
		printf("*****\n");
		for (i = 0; i < x; ++i) {
			printf(" ");
		}
		printf(" * *\n");

// 		scanf("%c", &input);按回车*才会移动
		input = getch();//实时移动

		//飞机上下左右移动
		if (input == 's') {
			y++;
		}
		if (input == 'w') {
			y--;
		}
		if (input == 'a') {
			x--;
		}
		if (input == 'd') {
			x++;
		}

		//按空格射击
		if (input == ' ') {
			isFired = 1;
		}

	}

//system("pause");
}

#include"stdio.h"
#include"windows.h"
#include"string.h"
#include"conio.h"
#include"time.h"

typedef struct pipe {
	int x;
	int y;
	struct pipe* next;
} PIPE;

char backGround[14][80] = {0};
int Time = 0;
unsigned int Score = 0;

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Getready() {
	int i = 0, j = 0;

	for (i = 0; i < 11; i++) {
		for (j = 0; j < 80; j++) {
			backGround[i][j] = ' ';
		}
	}
	for (i = 0; i < 8; i++) {
		strcat(backGround, "  ┌┐    ");
	}
	for (i = 0; i < 8; i++) {
		strcat(backGround, "┌┤│    ");
	}
	for (i = 0; i < 8; i++) {
		strcat(backGround, "││├┐  ");
	}
	puts(backGround);

	gotoxy(30, 3);
	printf("G e t  R e a d y");

	gotoxy(0, 14);
	for (i = 0; i < 40; i++) {
		printf("▁");
	}
	for (i = 0; i < 11; i++) {
		printf("  ╱╱ ");
	}
	gotoxy(0, 16);
	for (i = 0; i < 40; i++) {
		printf("▔");
	}
	gotoxy(18, 3);
	printf("*@>");
	getch();
	gotoxy(30, 3);
	printf("                ");


}

PIPE* Pipefun(PIPE* h) {
	int i = 0, j = 0;
	PIPE* p;

	for (p = h, i = 0; i < 6; i++) {
		for (j = 0; j < 14; j++) {
			if (j == p->y - 1 || j == p->y || j == p->y + 1)
				continue;
			else {
				if (p->x >= 0 && p->x < 80)
					gotoxy(p->x, j), printf("■");
				if (p->x + 2 >= 0 && p->x + 2 < 80)
					gotoxy(p->x + 2, j), printf("■");
				if (p->x + 4 >= 0 && p->x + 4 < 80)
					gotoxy(p->x + 4, j), printf("%c%c", backGround[j][p->x + 4], backGround[j][p->x + 5]);
			}
		}
		p->x = p->x - 2;
		p = p->next;
	}

	if (h->x < -4) {
		h->x = 78 + 12;
		h->y = rand() % 9 + 3;
		h = h->next;
	}

	return h;
}

void Bird() {
	int i = 0, bird = 3, temp = 0;
	char ch = '0';
	PIPE* h, * p, * q;

	p = h = q = (PIPE*) malloc(sizeof(PIPE));
	for (i = 0; i < 5; i++) {
		p->x = 78 + 16 * i;
		p->y = rand() % 9 + 3;
		q = (PIPE*) malloc(sizeof(PIPE));
		p->next = q;
		q->next = NULL;
		p = q;
	}
	p->x = 78 + 16 * i;
	p->y = rand() % 13 + 1;
	q->next = h;

	while (1) {
		Time++;

		temp = bird;

		if (kbhit())
			ch = getch();

		ch == ' ' ? bird-- : bird++;
		ch = '0';

		if (bird < 0 || bird >= 14)
			break;

		gotoxy(18, temp);
		printf("  %c%c", backGround[temp][20], backGround[temp][21]);
		gotoxy(18, bird);
		printf("*@>");

		if (Time % 3 == 1)
			h = Pipefun(h);
		for (p = h, i = 0; i < 6; i++, p = p->next)
			if (p->x == 18 && p->y - 1 != bird && p->y != bird && p->y + 1 != bird)
				break;
		if (p->x == 18 && p->y - 1 != bird && p->y != bird && p->y + 1 != bird)
			break;

		Sleep(300);
	}
}

void Gameover() {
	Score = (Time - 88) / 24 < 0 ? 0 : (Time - 88) / 24;
	gotoxy(28, 5);
	printf("┌──────────┐");
	gotoxy(28, 6);
	printf("│   G A M E O V E R  │");
	gotoxy(28, 7);
	printf("│                    │");
	gotoxy(28, 8);
	printf("│             %4d   │", Score);
	gotoxy(28, 9);
	printf("└──────────┘");

}

int main() {
	HideCursor();
	system("title Flappy Bird");
	system("mode con cols = 80 lines = 20");
	srand((unsigned) time(NULL));

	Getready();
	Bird();
	Gameover();

	getch();
}

#include "stdio.h"
#include <windows.h>
#include <conio.h>
#include <time.h>

#define Esc 27 //退出
#define Up 72 //上，下，左，右
#define Down 80
#define Left 75
#define Right 77
#define Kong 32 //发射子弹


int x = 10; //飞机坐标
int y = 18;

int d2 = 10;//敌机坐标
int d1 = 10;
int d = 10;
int r = 1;
int r1 = 1;
int r2 = 1;


int t = 1; // 游戏结束
int f = 0; // 计分数
int m = 3; // 敌机数
int j = 0; // 歼敌数
char p; // 接受按键


void kongzhi(int bx, int by);//声明函数
void huatu();


void gotoxy(int x, int y) //移动坐标
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hidden()//隐藏光标
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;//赋1为显示，赋0为隐藏
	SetConsoleCursorInfo(hOut, &cci);
}
//**************************************************************************************


//说明
void shuoming() {
	printf("\t\t\t\n\n\n\n");

	printf("\t\t\t方向控制\n\n"
		   "\t\t\t上 ↑\n\n"
		   "\t\t\t下 ↓\n\n"
		   "\t\t\t左 ←\n\n"
		   "\t\t\t右 →\n\n"
		   "\t\t\t子弹 空格\n\n\n"
		   "\t\t\t退出请按 ESC\n");
	gotoxy(0, 0);
}


//****************************************************************************************


//判断我机死没死/游戏结束
void byebye() {
	if ((x == d && y == r) || (x == d1 && y == r1) || (x == d2 && y == r2)) {
		gotoxy(1, 3);
		printf(" !!! 游戏结束 !!!\n"
			   "*******************\n"
			   " 您的总得分: %d\n\n"
			   " 敌机数: %d\n"
			   " 歼敌数: %d\n"
			   " 命中率: %.0f %%\n"
			   "*******************\n", f, m, j, ((float) j / (float) m) * 100);
		while (!kbhit()) {
			Sleep(500);
			gotoxy(1, 12);
			printf(" 继续请按任意键...\n\n\n");
			Sleep(900);
			gotoxy(1, 12);
			printf(" ");
		}
		gotoxy(0, 0);
		huatu();
		f = 0;
		m = 0;
		j = 0;
		if (x >= 18) x--;
		else x++;
		gotoxy(x, y);
		printf("Ж");
	}
}

// 计分/更新敌机
void jifan() {
	if (x == d && y == r) {
		gotoxy(d, r);
		printf("3");
		Sleep(200);
		gotoxy(d, r);
		printf(" ");
		f += 2;
		r = 0;
		j++;
	}
	if (x == d1 && y == r1) {
		gotoxy(d1, r1);
		printf("1");
		Sleep(200);
		gotoxy(d1, r1);
		printf(" ");
		f += 3;
		r1 = 0;
		j++;
	}
	if (x == d2 && y == r2) {
		gotoxy(d2, r2);
		printf("0");
		Sleep(200);
		gotoxy(d2, r2);
		printf(" ");
		f += 1;
		r2 = 0;
		j++;
	}

	gotoxy(26, 2);
	printf(" %d \n", f);

}

//画图
void huatu() {
	int i, n;

	for (i = 0; i <= 20; i++) {
		for (n = 0; n <= 20; n++) {
			printf("*");
		}
		printf("\n");
	}
	for (i = 1; i <= 19; i++) {
		for (n = 1; n <= 19; n++) {
			gotoxy(i, n);
			printf(" ");
		}
	}
}


//随机产生敌机
void dfeiji() {
	while (t) {
		if (!r) {
			d = rand() % 17 + 1;
			m++;
		}
		if (!r1) {
			d1 = rand() % 17 + 1;
			m++;
		}
		if (!r2) {
			d2 = rand() % 17 + 1;
			m++;
		}

		while (t) {
			r++;
			r1++;
			r2++;
			gotoxy(d, r);
			printf("Ψ");
			gotoxy(d1, r1);
			printf("ж");
			gotoxy(d2, r2);
			printf("♀");
			Sleep(900);
			gotoxy(d, r);
			printf(" ");
			gotoxy(d1, r1);
			printf(" ");
			gotoxy(d2, r2);
			printf(" ");


			kongzhi(0, 0);
			byebye();
			if (r == 18) r = 0;
			if (r1 == 18) r1 = 0;
			if (r2 == 18) r2 = 0;
			if (r == 0 || r1 == 0 || r2 == 0) break;
		}
	}
}


//操控飞机
void kongzhi(int bx, int by) {
	int a;


	while (kbhit()) {
		if ((p = getch()) == -32) p = getch();
		a = p;
		gotoxy(22, 5);

		switch (a) {//控制方向
			case Up:
				if (y != 1) {
					gotoxy(x, y);
					printf(" ");
					y--;
					gotoxy(x, y);
					printf("Ж");
				}
				break;
			case Down:
				if (y != 18) {
					gotoxy(x, y);
					printf(" ");
					y++;
					gotoxy(x, y);
					printf("Ж");
				}
				break;
			case Left:
				if (x != 1) {
					gotoxy(x, y);
					printf(" ");
					x--;
					gotoxy(x, y);
					printf("Ж");
				}
				break;
			case Right:
				if (x != 18) {
					gotoxy(x, y);
					printf(" ");
					x++;
					gotoxy(x, y);
					printf("Ж");
				}
				break;
			case Kong: {
				bx = y;
				for (by = y; by > 1;) //发射子弹
				{
					by--;
					gotoxy(x, by);
					printf("θ");
					Sleep(10);
					gotoxy(x, by);
					printf(" ");
					y = by;
					jifan();
					if (r == 0 || r1 == 0 || r2 == 0) break;
				}
				y = bx;
			}
				break;

			case Esc:
				t = 0;
				break; //退出

			default:
				break;
		}
	}
}

void main() {
	srand(time(NULL));
	shuoming();
	hidden();
	huatu();
	gotoxy(x, y);
	printf("Ж");

	gotoxy(22, 2);
	printf("分数:");
	while (t) {
		kongzhi(0, 0);
		if (t)
			dfeiji();
	}

}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//水平方向为x，竖直方向为y

int main() {
	int i, j;
	int x = 15;
	int y = 1;
	int velocity_x = 1;
	int velocity_y = 1;

	//上下左右边界
	int left = 0;
	int right = 25;
	int top = 0;
	int bottom = 25;

	while (1) {
		x = x + velocity_x;
		y = y + velocity_y;

		system("cls");//清屏

		//输出小球前的空行
		for (i = 0; i < y; ++i) {
			printf("\n");
		}
		for (j = 0; j < x; j++) {
			printf(" ");
		}
		printf("o\n");//输出小球o
		Sleep(50);

		//触壁响铃
		if (x == left || x == right || y == top || y == bottom) {
			printf("\a");
		}

		//越界判断
		if (y <= top || y >= bottom) {
			velocity_y = -velocity_y;
		}
		if (x <= left || x >= right) {
			velocity_x = -velocity_x;
		}
	}

// 	system("pause");
	return 0;
}

#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>

#define U 1
#define D 2
#define L 3
#define R 4       //蛇的状态，U：上 ；D：下；L:左 R：右

typedef struct SNAKE //蛇身的一个节点
{
	int x;
	int y;
	struct SNAKE* next;
} snake;

//全局变量//
int score = 0, add = 10;//总得分与每次吃食物得分。
int status, sleeptime = 200;//每次运行的时间间隔
snake* head, * food;//蛇头指针，食物指针
snake* q;//遍历蛇的时候用到的指针
int endgamestatus = 0; //游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。

//声明全部函数//
void Pos();

void creatMap();

void initsnake();

int biteself();

void createfood();

void cantcrosswall();

void snakemove();

void pause();

void gamecircle();

void welcometogame();

void endgame();

void gamestart();

void Pos(int x, int y)//设置光标位置
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void creatMap()//创建地图
{
	int i;
	for (i = 0; i < 58; i += 2)//打印上下边框
	{
		Pos(i, 0);
		printf("■");
		Pos(i, 26);
		printf("■");
	}
	for (i = 1; i < 26; i++)//打印左右边框
	{
		Pos(0, i);
		printf("■");
		Pos(56, i);
		printf("■");
	}
}

void initsnake()//初始化蛇身
{
	snake* tail;
	int i;
	tail = (snake*) malloc(sizeof(snake));//从蛇尾开始，头插法，以x,y设定开始的位置//
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	for (i = 1; i <= 4; i++) {
		head = (snake*) malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	while (tail != NULL)//从头到为，输出蛇身
	{
		Pos(tail->x, tail->y);
		printf("■");
		tail = tail->next;
	}
}

int biteself()//判断是否咬到了自己
{
	snake* self;
	self = head->next;
	while (self != NULL) {
		if (self->x == head->x && self->y == head->y) {
			return 1;
		}
		self = self->next;
	}
	return 0;
}

void createfood()//随机出现食物
{
	snake* food_1;
	srand((unsigned) time(NULL));
	food_1 = (snake*) malloc(sizeof(snake));
	while ((food_1->x % 2) != 0)    //保证其为偶数，使得食物能与蛇头对其
	{
		food_1->x = rand() % 52 + 2;
	}
	food_1->y = rand() % 24 + 1;
	q = head;
	while (q->next == NULL) {
		if (q->x == food_1->x && q->y == food_1->y) //判断蛇身是否与食物重合
		{
			free(food_1);
			createfood();
		}
		q = q->next;
	}
	Pos(food_1->x, food_1->y);
	food = food_1;
	printf("■");
}

void cantcrosswall()//不能穿墙
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26) {
		endgamestatus = 1;
		endgame();
	}
}

void snakemove()//蛇前进,上U,下D,左L,右R
{
	snake* nexthead;
	cantcrosswall();

	nexthead = (snake*) malloc(sizeof(snake));
	if (status == U) {
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		if (nexthead->x == food->x && nexthead->y == food->y)//如果下一个有食物//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		} else                                               //如果没有食物//
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == D) {
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		if (nexthead->x == food->x && nexthead->y == food->y)  //有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		} else                               //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L) {
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		} else                                //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R) {
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		if (nexthead->x == food->x && nexthead->y == food->y)//有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			score = score + add;
			createfood();
		} else                                         //没有食物
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL) {
				Pos(q->x, q->y);
				printf("■");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			printf("  ");
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteself() == 1)       //判断是否会咬到自己
	{
		endgamestatus = 2;
		endgame();
	}
}

void pause()//暂停
{
	while (1) {
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE)) {
			break;
		}

	}
}

void gamecircle()//控制游戏
{

	Pos(64, 15);
	printf("不能穿墙，不能咬到自己\n");
	Pos(64, 16);
	printf("用↑.↓.←.→分别控制蛇的移动.");
	Pos(64, 17);
	printf("F1 为加速，F2 为减速\n");
	Pos(64, 18);
	printf("ESC ：退出游戏.space：暂停游戏.");
	Pos(64, 20);
	status = R;
	while (1) {
		Pos(64, 10);
		printf("得分：%d  ", score);
		Pos(64, 11);
		printf("每个食物得分：%d分", add);
		if (GetAsyncKeyState(VK_UP) && status != D) {
			status = U;
		} else if (GetAsyncKeyState(VK_DOWN) && status != U) {
			status = D;
		} else if (GetAsyncKeyState(VK_LEFT) && status != R) {
			status = L;
		} else if (GetAsyncKeyState(VK_RIGHT) && status != L) {
			status = R;
		} else if (GetAsyncKeyState(VK_SPACE)) {
			pause();
		} else if (GetAsyncKeyState(VK_ESCAPE)) {
			endgamestatus = 3;
			break;
		} else if (GetAsyncKeyState(VK_F1)) {
			if (sleeptime >= 50) {
				sleeptime = sleeptime - 30;
				add = add + 2;
				if (sleeptime == 320) {
					add = 2;//防止减到1之后再加回来有错
				}
			}
		} else if (GetAsyncKeyState(VK_F2)) {
			if (sleeptime < 350) {
				sleeptime = sleeptime + 30;
				add = add - 2;
				if (sleeptime == 350) {
					add = 1;  //保证最低分为1
				}
			}
		}
		Sleep(sleeptime);
		snakemove();
	}
}

void welcometogame()//开始界面
{
	Pos(40, 12);
	printf("欢迎来到贪食蛇游戏！");
	Pos(40, 25);
	system("pause");
	system("cls");
	Pos(25, 12);
	printf("用↑.↓.←.→分别控制蛇的移动， F1 为加速，2 为减速\n");
	Pos(25, 13);
	printf("加速将能得到更高的分数。\n");
	system("pause");
	system("cls");
}

void endgame()//结束游戏
{

	system("cls");
	Pos(24, 12);
	if (endgamestatus == 1) {
		printf("对不起，您撞到墙了。游戏结束!");
	} else if (endgamestatus == 2) {
		printf("对不起，您咬到自己了。游戏结束!");
	} else if (endgamestatus == 3) {
		printf("您已经结束了游戏。");
	}
	Pos(24, 13);
	printf("您的得分是%d\n", score);
	exit(0);
}

void gamestart()//游戏初始化
{
	system("mode con cols=100 lines=30");
	welcometogame();
	creatMap();
	initsnake();
	createfood();
}

int main() {
	gamestart();
	gamecircle();
	endgame();
	return 0;
}

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//游戏窗口
#define FrameX 4   //游戏窗口左上角的X轴坐标
#define FrameY 4   //游戏窗口左上角的Y轴坐标
#define Frame_height  20 //游戏窗口的高度
#define Frame_width   18 //游戏窗口的宽度

//定义全局变量
int i, j, temp, temp1, temp2; //temp,temp1,temp2用于记住和转换方块变量的值
int a[80][80] = {0};   //标记游戏屏幕的图案：2,1,0分别表示该位置为游戏边框、方块、无图案;初始化为无图案
int b[4];     //标记4个"口"方块：1表示有方块，0表示无方块

//声明俄罗斯方块的结构体
struct Tetris {
	int x;     //中心方块的x轴坐标
	int y;     //中心方块的y轴坐标
	int flag;    //标记方块类型的序号
	int next;    //下一个俄罗斯方块类型的序号
	int speed;    //俄罗斯方块移动的速度
	int count;    //产生俄罗斯方块的个数
	int score;    //游戏的分数
	int level;    //游戏的等级
};

//函数原型声明
//光标移到指定位置
void gotoxy(HANDLE hOut, int x, int y);

//制作游戏窗口
void make_frame();

//随机产生方块类型的序号
void get_flag(struct Tetris*);

//制作俄罗斯方块
void make_tetris(struct Tetris*);

//打印俄罗斯方块
void print_tetris(HANDLE hOut, struct Tetris*);

//清除俄罗斯方块的痕迹
void clear_tetris(HANDLE hOut, struct Tetris*);

//判断是否能移动，返回值为1，能移动，否则，不动
int if_moveable(struct Tetris*);

//判断是否满行，并删除满行的俄罗斯方块
void del_full(HANDLE hOut, struct Tetris*);

//开始游戏
void start_game();


void main() {
	//制作游戏窗口
	make_frame();
	//开始游戏
	start_game();
}

/******光标移到指定位置**************************************************************/
void gotoxy(HANDLE hOut, int x, int y) {
	COORD pos;
	pos.X = x;  //横坐标
	pos.Y = y;  //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}

/******制作游戏窗口******************************************************************/
void make_frame() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //定义显示器句柄变量

	gotoxy(hOut, FrameX + Frame_width - 5, FrameY - 2);   //打印游戏名称
	printf("俄罗斯方块");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 7);  //打印选择菜单
	printf("**********下一个方块：");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 13);
	printf("**********");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 17);
	printf("↑键：变体");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 19);
	printf("空格：暂停游戏");
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 15);
	printf("Esc ：退出游戏");

	gotoxy(hOut, FrameX, FrameY);       //打印框角并记住该处已有图案
	printf("╔");
	gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY);
	printf("╗");
	gotoxy(hOut, FrameX, FrameY + Frame_height);
	printf("╚");
	gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + Frame_height);
	printf("╝");
	a[FrameX][FrameY + Frame_height] = 2;
	a[FrameX + 2 * Frame_width - 2][FrameY + Frame_height] = 2;

	for (i = 2; i < 2 * Frame_width - 2; i += 2) {
		gotoxy(hOut, FrameX + i, FrameY);
		printf("═");         //打印上横框
	}
	for (i = 2; i < 2 * Frame_width - 2; i += 2) {
		gotoxy(hOut, FrameX + i, FrameY + Frame_height);
		printf("═");         //打印下横框
		a[FrameX + i][FrameY + Frame_height] = 2;    //记住下横框有图案
	}
	for (i = 1; i < Frame_height; i++) {
		gotoxy(hOut, FrameX, FrameY + i);
		printf("║");         //打印左竖框
		a[FrameX][FrameY + i] = 2;       //记住左竖框有图案
	}
	for (i = 1; i < Frame_height; i++) {
		gotoxy(hOut, FrameX + 2 * Frame_width - 2, FrameY + i);
		printf("║");         //打印右竖框
		a[FrameX + 2 * Frame_width - 2][FrameY + i] = 2;   //记住右竖框有图案
	}
}

/******制作俄罗斯方块********************************************************************/
void make_tetris(struct Tetris* tetris) {
	a[tetris->x][tetris->y] = b[0];    //中心方块位置的图形状态:1-有,0-无
	switch (tetris->flag)      //共6大类，19种类型
	{
		case 1:         //田字方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x + 2][tetris->y - 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 2:         //直线方块:----
		{
			a[tetris->x - 2][tetris->y] = b[1];
			a[tetris->x + 2][tetris->y] = b[2];
			a[tetris->x + 4][tetris->y] = b[3];
			break;
		}
		case 3:         //直线方块: |
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x][tetris->y - 2] = b[2];
			a[tetris->x][tetris->y + 1] = b[3];
			break;
		}
		case 4:         //T字方块
		{
			a[tetris->x - 2][tetris->y] = b[1];
			a[tetris->x + 2][tetris->y] = b[2];
			a[tetris->x][tetris->y + 1] = b[3];
			break;
		}
		case 5:         //T字顺时针转90度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x][tetris->y + 1] = b[2];
			a[tetris->x - 2][tetris->y] = b[3];
			break;
		}
		case 6:         //T字顺时针转180度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x - 2][tetris->y] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 7:         //T字顺时针转270度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x][tetris->y + 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 8:         //Z字方块
		{
			a[tetris->x][tetris->y + 1] = b[1];
			a[tetris->x - 2][tetris->y] = b[2];
			a[tetris->x + 2][tetris->y + 1] = b[3];
			break;
		}
		case 9:         //Z字顺时针转90度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x - 2][tetris->y] = b[2];
			a[tetris->x - 2][tetris->y + 1] = b[3];
			break;
		}
		case 10:        //Z字顺时针转180度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x - 2][tetris->y - 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 11:        //Z字顺时针转270度方块
		{
			a[tetris->x][tetris->y + 1] = b[1];
			a[tetris->x + 2][tetris->y - 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 12:        //7字方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x][tetris->y + 1] = b[2];
			a[tetris->x - 2][tetris->y - 1] = b[3];
			break;
		}
		case 13:        //7字顺时针转90度方块
		{
			a[tetris->x - 2][tetris->y] = b[1];
			a[tetris->x - 2][tetris->y + 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 14:        //7字顺时针转180度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x][tetris->y + 1] = b[2];
			a[tetris->x + 2][tetris->y + 1] = b[3];
			break;
		}
		case 15:        //7字顺时针转270度方块
		{
			a[tetris->x - 2][tetris->y] = b[1];
			a[tetris->x + 2][tetris->y - 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 16:        //倒7字方块
		{
			a[tetris->x][tetris->y + 1] = b[1];
			a[tetris->x][tetris->y - 1] = b[2];
			a[tetris->x + 2][tetris->y - 1] = b[3];
			break;
		}
		case 17:        //倒7字顺指针转90度方块
		{
			a[tetris->x - 2][tetris->y] = b[1];
			a[tetris->x - 2][tetris->y - 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
		case 18:        //倒7字顺时针转180度方块
		{
			a[tetris->x][tetris->y - 1] = b[1];
			a[tetris->x][tetris->y + 1] = b[2];
			a[tetris->x - 2][tetris->y + 1] = b[3];
			break;
		}
		case 19:        //倒7字顺时针转270度方块
		{
			a[tetris->x - 2][tetris->y] = b[1];
			a[tetris->x + 2][tetris->y + 1] = b[2];
			a[tetris->x + 2][tetris->y] = b[3];
			break;
		}
	}
}

//******判断是否可动*************************************************************************/
int if_moveable(struct Tetris* tetris) {
	if (a[tetris->x][tetris->y] != 0)//当中心方块位置上有图案时，返回值为0，即不可移动
	{
		return 0;
	} else {
		if ( //当为田字方块且除中心方块位置外，其他"口"字方块位置上无图案时，返回值为1，即可移动
				(tetris->flag == 1 && (a[tetris->x][tetris->y - 1] == 0 &&
									   a[tetris->x + 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
				//或为直线方块且除中心方块位置外，其他"口"字方块位置上无图案时，返回值为1，即可移动
				(tetris->flag == 2 && (a[tetris->x - 2][tetris->y] == 0 &&
									   a[tetris->x + 2][tetris->y] == 0 && a[tetris->x + 4][tetris->y] == 0)) ||

				(tetris->flag == 3 && (a[tetris->x][tetris->y - 1] == 0 &&
									   a[tetris->x][tetris->y - 2] == 0 && a[tetris->x][tetris->y + 1] == 0)) ||

				(tetris->flag == 4 && (a[tetris->x - 2][tetris->y] == 0 &&
									   a[tetris->x + 2][tetris->y] == 0 && a[tetris->x][tetris->y + 1] == 0)) ||

				(tetris->flag == 5 && (a[tetris->x][tetris->y - 1] == 0 &&
									   a[tetris->x][tetris->y + 1] == 0 && a[tetris->x - 2][tetris->y] == 0)) ||

				(tetris->flag == 6 && (a[tetris->x][tetris->y - 1] == 0 &&
									   a[tetris->x - 2][tetris->y] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 7 && (a[tetris->x][tetris->y - 1] == 0 &&
									   a[tetris->x][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 8 && (a[tetris->x][tetris->y + 1] == 0 &&
									   a[tetris->x - 2][tetris->y] == 0 && a[tetris->x + 2][tetris->y + 1] == 0)) ||

				(tetris->flag == 9 && (a[tetris->x][tetris->y - 1] == 0 &&
									   a[tetris->x - 2][tetris->y] == 0 && a[tetris->x - 2][tetris->y + 1] == 0)) ||

				(tetris->flag == 10 && (a[tetris->x][tetris->y - 1] == 0 &&
										a[tetris->x - 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 11 && (a[tetris->x][tetris->y + 1] == 0 &&
										a[tetris->x + 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 12 && (a[tetris->x][tetris->y - 1] == 0 &&
										a[tetris->x][tetris->y + 1] == 0 && a[tetris->x - 2][tetris->y - 1] == 0)) ||

				(tetris->flag == 13 && (a[tetris->x - 2][tetris->y] == 0 &&
										a[tetris->x - 2][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 14 && (a[tetris->x][tetris->y - 1] == 0 &&
										a[tetris->x][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y + 1] == 0)) ||

				(tetris->flag == 15 && (a[tetris->x - 2][tetris->y] == 0 &&
										a[tetris->x + 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 16 && (a[tetris->x][tetris->y + 1] == 0 &&
										a[tetris->x][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y - 1] == 0)) ||

				(tetris->flag == 17 && (a[tetris->x - 2][tetris->y] == 0 &&
										a[tetris->x - 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||

				(tetris->flag == 18 && (a[tetris->x][tetris->y - 1] == 0 &&
										a[tetris->x][tetris->y + 1] == 0 && a[tetris->x - 2][tetris->y + 1] == 0)) ||

				(tetris->flag == 19 && (a[tetris->x - 2][tetris->y] == 0 &&
										a[tetris->x + 2][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y] == 0))) {
			return 1;
		}
	}
	return 0;
}

/******随机产生俄罗斯方块类型的序号**********************************************************/
void get_flag(struct Tetris* tetris) {
	tetris->count++;     //记住产生方块的个数
	srand((unsigned) time(NULL));  //初始化随机数
	if (tetris->count == 1) {
		tetris->flag = rand() % 19 + 1;  //记住第一个方块的序号
	}
	tetris->next = rand() % 19 + 1;   //记住下一个方块的序号
}

/******打印俄罗斯方块**********************************************************************/
void print_tetris(HANDLE hOut, struct Tetris* tetris) {
	for (i = 0; i < 4; i++) {
		b[i] = 1;         //数组b[4]的每个元素的值都为1
	}
	make_tetris(tetris);      //制作俄罗斯方块
	for (i = tetris->x - 2; i <= tetris->x + 4; i += 2) {
		for (j = tetris->y - 2; j <= tetris->y + 1; j++) {
			if (a[i][j] == 1 && j > FrameY) {
				gotoxy(hOut, i, j);
				printf("□");     //打印边框内的方块
			}
		}
	}
	//打印菜单信息
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 1);
	printf("level : %d", tetris->level);
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 3);
	printf("score : %d", tetris->score);
	gotoxy(hOut, FrameX + 2 * Frame_width + 3, FrameY + 5);
	printf("speed : %dms", tetris->speed);
}

/******清除俄罗斯方块的痕迹****************************************************************/
void clear_tetris(HANDLE hOut, struct Tetris* tetris) {
	for (i = 0; i < 4; i++) {
		b[i] = 0;         //数组b[4]的每个元素的值都为0
	}
	make_tetris(tetris);      //制作俄罗斯方块
	for (i = tetris->x - 2; i <= tetris->x + 4; i += 2) {
		for (j = tetris->y - 2; j <= tetris->y + 1; j++) {
			if (a[i][j] == 0 && j > FrameY) {
				gotoxy(hOut, i, j);
				printf("  ");     //清除方块
			}
		}
	}
}

/******判断是否满行并删除满行的俄罗斯方块****************************************************/
void del_full(HANDLE hOut, struct Tetris* tetris) {       //当某行有Frame_width-2个方块时，则满行
	int k, del_count = 0;  //分别用于记录某行方块的个数和删除方块的行数的变量
	for (j = FrameY + Frame_height - 1; j >= FrameY + 1; j--) {
		k = 0;
		for (i = FrameX + 2; i < FrameX + 2 * Frame_width - 2; i += 2) {
			if (a[i][j] == 1) //竖坐标依次从下往上，横坐标依次由左至右判断是否满行
			{
				k++;  //记录此行方块的个数
				if (k == Frame_width - 2) {
					for (k = FrameX + 2; k < FrameX + 2 * Frame_width - 2; k += 2) {  //删除满行的方块
						a[k][j] = 0;
						gotoxy(hOut, k, j);
						printf("  ");
						Sleep(1);
					}
					for (k = j - 1; k > FrameY; k--) {  //如果删除行以上的位置有方块，则先清除，再将方块下移一个位置
						for (i = FrameX + 2; i < FrameX + 2 * Frame_width - 2; i += 2) {
							if (a[i][k] == 1) {
								a[i][k] = 0;
								gotoxy(hOut, i, k);
								printf("  ");
								a[i][k + 1] = 1;
								gotoxy(hOut, i, k + 1);
								printf("□");
							}
						}
					}
					j++;   //方块下移后，重新判断删除行是否满行
					del_count++; //记录删除方块的行数
				}
			}
		}
	}
	tetris->score += 100 * del_count; //每删除一行，得100分
	if (del_count > 0 && (tetris->score % 1000 == 0 || tetris->score / 1000 > tetris->level - 1)) {        //如果得1000分即累计删除10行，速度加快20ms并升一级
		tetris->speed -= 20;
		tetris->level++;
	}
}

/******开始游戏******************************************************************************/
void start_game() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //定义显示器句柄变量
	struct Tetris t, * tetris = &t;       //定义结构体的指针并指向结构体变量
	unsigned char ch;         //定义接收键盘输入的变量

	tetris->count = 0;      //初始化俄罗斯方块数为0个
	tetris->speed = 300;      //初始移动速度为300ms
	tetris->score = 0;      //初始游戏的分数为0分
	tetris->level = 1;      //初始游戏为第1关

	while (1) {//循环产生方块，直至游戏结束
		get_flag(tetris);     //得到产生俄罗斯方块类型的序号
		temp = tetris->flag;     //记住当前俄罗斯方块序号

		//打印下一个俄罗斯方块的图形(右边窗口)
		tetris->x = FrameX + 2 * Frame_width + 6;
		tetris->y = FrameY + 10;
		tetris->flag = tetris->next;
		print_tetris(hOut, tetris);

		tetris->x = FrameX + Frame_width;  //初始中心方块x坐标
		tetris->y = FrameY - 1;     //初始中心方块y坐标
		tetris->flag = temp;     //取出当前的俄罗斯方块序号

		while (1) {//控制方块方向，直至方块不再下移
			label:
			print_tetris(hOut, tetris);//打印俄罗斯方块
			Sleep(tetris->speed);   //延缓时间
			clear_tetris(hOut, tetris);  //清除痕迹
			temp1 = tetris->x;    //记住中心方块横坐标的值
			temp2 = tetris->flag;    //记住当前俄罗斯方块序号
			if (kbhit()) {        //判断是否有键盘输入，有则用ch↓接收
				ch = getch();
				if (ch == 75)     //按←键则向左动，中心横坐标减2
				{
					tetris->x -= 2;
				}
				if (ch == 77)     //按→键则向右动，中心横坐标加2
				{
					tetris->x += 2;
				}
				if (ch == 72)     //按↑键则变体即当前方块顺时针转90度
				{
					if (tetris->flag >= 2 && tetris->flag <= 3) {
						tetris->flag++;
						tetris->flag %= 2;
						tetris->flag += 2;
					}
					if (tetris->flag >= 4 && tetris->flag <= 7) {
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 4;
					}
					if (tetris->flag >= 8 && tetris->flag <= 11) {
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 8;
					}
					if (tetris->flag >= 12 && tetris->flag <= 15) {
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 12;
					}
					if (tetris->flag >= 16 && tetris->flag <= 19) {
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 16;
					}
				}
				if (ch == 32)     //按空格键，暂停
				{
					print_tetris(hOut, tetris);
					while (1) {
						if (kbhit())   //再按空格键，继续游戏
						{
							ch = getch();
							if (ch == 32) {
								goto label;
							}
						}
					}
				}
				if (if_moveable(tetris) == 0) //如果不可动，上面操作无效
				{
					tetris->x = temp1;
					tetris->flag = temp2;
				} else      //如果可动，执行操作
				{
					goto label;
				}
			}
			tetris->y++;     //如果没有操作指令，方块向下移动
			if (if_moveable(tetris) == 0)  //如果向下移动且不可动，方块放在此处
			{
				tetris->y--;
				print_tetris(hOut, tetris);
				del_full(hOut, tetris);
				break;
			}
		}

		for (i = tetris->y - 2; i < tetris->y + 2; i++) {//游戏结束条件：方块触到框顶位置
			if (i == FrameY) {
				j = 0;      //如果游戏结束，j=0
			}
		}
		if (j == 0) {
			system("cls");
			getch();
			break;
		}
		//清除下一个俄罗斯方块的图形(右边窗口)
		tetris->flag = tetris->next;
		tetris->x = FrameX + 2 * Frame_width + 6;
		tetris->y = FrameY + 10;
		clear_tetris(hOut, tetris);
	}
}

这是一个简单的猜拳游戏（剪子包子锤），让你与电脑对决。你出的拳头由你自己决定，电脑则随机出拳，最后判断胜负。

下面的代码会实现一个猜拳游戏，让你与电脑对决。你出的拳头由你自己决定，电脑则随机出拳，最后判断胜负。

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	char gamer;  // 玩家出拳
	int computer;  // 电脑出拳
	int result;  // 比赛结果

	// 为了避免玩一次游戏就退出程序，可以将代码放在循环中
	while (1) {
		printf("这是一个猜拳的小游戏，请输入你要出的拳头：\n");
		printf("A:剪刀\nB:石头\nC:布\nD:不玩了\n");
		scanf("%c%*c", &gamer);
		switch (gamer) {
			case 65:  //A
			case 97:  //a
				gamer = 4;
				break;
			case 66:  //B
			case 98:  //b
				gamer = 7;
				break;
			case 67:  //C
			case 99:  //c
				gamer = 10;
				break;
			case 68:  //D
			case 100:  //d
				return 0;

			default:
				printf("你的选择为 %c 选择错误,退出...\n", gamer);
				getchar();
				system("cls"); // 清屏
				return 0;
				break;
		}

		srand((unsigned) time(NULL));  // 随机数种子
		computer = rand() % 3;  // 产生随机数并取余，得到电脑出拳
		result = (int) gamer + computer;  // gamer 为 char 类型，数学运算时要强制转换类型
		printf("电脑出了");
		switch (computer) {
			case 0:
				printf("剪刀\n");
				break; //4    1
			case 1:
				printf("石头\n");
				break; //7  2
			case 2:
				printf("布\n");
				break;   //10 3
		}
		printf("你出了");
		switch (gamer) {
			case 4:
				printf("剪刀\n");
				break;
			case 7:
				printf("石头\n");
				break;
			case 10:
				printf("布\n");
				break;
		}
		if (result == 6 || result == 7 || result == 11) printf("你赢了!");
		else if (result == 5 || result == 9 || result == 10) printf("电脑赢了!");
		else printf("平手");
		system("pause>nul&&cls");  // 暂停并清屏
	}
	return 0;
}


代码分析
1) 首先，
我们需要定义3个变量来储存玩家出的拳头(gamer)
、
电脑出的拳头(computer)
和最后的结果(result)
，然后给出文字提示，让玩家出拳。

接下来接收玩家输入：

scanf("%c%*c",&gamer);

注意：由于每次输入以回车结束，缓冲区中除了玩家输入的字母，还有回车符。回车符要跳过，以免影响下次输入。

Scanf()

函数的格式控制字符串个数可以多于参数个数，scanf("%c%*c",&gamer);的作用是从缓冲区多输出一个字符（回车符），却不赋给任何变量。

玩家输入结束，使用 switch 语句判断输入内容，65(A)、97(a)、66(B)、98(b)、67(C)、99(c)、68(D)、100(d)为相应字符的ASCII码。

注意：system("cls"); 语句的作用是清屏。

System()

函数用来执行 dos
命令，
这里相当于在 dos
里输入 cls
命令。

2) 玩家出拳结束，电脑开始出拳。

电脑通过产生随机数来出拳：

srand((unsigned)
time(NULL)
);  //为了避免多次运行结果相同，故在前面加入上（需要time.h）
computer = rand() % 3;  //获取0~2的随机数

最后通过玩家和电脑出拳的和来判断输赢：

result = (int) gamer + computer;
// ...
if (result==6||result==7||result==11) printf("你赢了!");
else if (result==5||result==9||result==10) printf("电脑赢了!");
else printf("平手");

这是一个很巧妙的算法，玩家和电脑出拳不同，
result 的值就不同
，且不会重复，见下表：

电脑 --

玩家 石头(

4)    剪刀(7)    布(10)
石头(0)    4    7    10
剪刀(1)    5    8    11
布(2)    6    9    12

3) 每次猜拳结束，暂停并清屏，进入下一次猜拳：

system("pause>nul&&cls");   //暂停运行和清屏

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>


#define MAXIMUS 15 //定义棋盘大小


int p[MAXIMUS][MAXIMUS];//存储对局信息
char buff[MAXIMUS * 2 + 1][MAXIMUS * 4 + 3];//输出缓冲器
int Cx, Cy;//当前光标位置
int Now;//当前走子的玩家，1代表黑，2代表白
int wl, wp;//当前写入缓冲器的列数和行数位置
char* showText;//在棋盘中央显示的文字信息
int count;//回合数


char* Copy(char* strDest, const char* strSrc)//修改过的字符串复制函数，会忽略末端的\0
{
	char* strDestCopy = strDest;
	while (*strSrc != '\0') {
		*strDest++ = *strSrc++;
	}
	return strDestCopy;
}

void Initialize()//初始化一个对局函数
{
	int i, j;//循环变量
	showText = "";//重置显示信息
	count = 0;//回合数归零
	for (i = 0; i < MAXIMUS; i++)//重置对局数据
	{
		for (j = 0; j < MAXIMUS; j++) {
			p[i][j] = 0;
		}
	}
	Cx = Cy = MAXIMUS / 2;//重置光标到中央
	Now = 1;//重置当前为黑方
}

char* getStyle(int i, int j)//获得棋盘中指定坐标交点位置的字符，通过制表符拼成棋盘
{
	if (p[i][j] == 1)//1为黑子
		return "●";
	else if (p[i][j] == 2)//2为白子
		return "○";
	else if (i == 0 && j == 0)//以下为边缘棋盘样式
		return "┏";
	else if (i == MAXIMUS - 1 && j == 0)
		return "┓";
	else if (i == MAXIMUS - 1 && j == MAXIMUS - 1)
		return "┛";
	else if (i == 0 && j == MAXIMUS - 1)
		return "┗";
	else if (i == 0)
		return "┠";
	else if (i == MAXIMUS - 1)
		return "┨";
	else if (j == 0)
		return "┯";
	else if (j == MAXIMUS - 1)
		return "┷";
	return "┼";//中间的空位
}

char* getCurse(int i, int j) {//获得指定坐标交点位置左上格的样式，通过制表符来模拟光标的显示
	if (i == Cx) {
		if (j == Cy)
			return "┏";
		else if (j == Cy + 1)
			return "┗";
	} else if (i == Cx + 1) {
		if (j == Cy)
			return "┓";
		else if (j == Cy + 1)
			return "┛";
	}
	return "　";//如果不在光标附近则为空
}

void write(char* c)//向缓冲器写入字符串
{
	Copy(buff[wl] + wp, c);
	wp += strlen(c);
}

void ln()//缓冲器写入位置提行
{
	wl += 1;
	wp = 0;
}

void Display()//将缓冲器内容输出到屏幕
{
	int i, l = strlen(showText);//循环变量，中间文字信息的长度
	int Offset = MAXIMUS * 2 + 2 - l / 2;//算出中间文字信息居中显示所在的横坐标位置
	if (Offset % 2 == 1)//如果位置为奇数，则移动到偶数，避免混乱
	{
		Offset--;
	}
	Copy(buff[MAXIMUS] + Offset, showText);//讲中间文字信息复制到缓冲器
	if (l % 2 == 1)//如果中间文字长度为半角奇数，则补上空格，避免混乱
	{
		*(buff[MAXIMUS] + Offset + l) = 0x20;
	}
	system("cls");//清理屏幕，准备写入
	for (i = 0; i < MAXIMUS * 2 + 1; i++) {//循环写入每一行
		printf("%s", buff[i]);
		if (i < MAXIMUS * 2)//写入完每一行需要换行
			printf("\n");
	}
}

void Print()//将整个棋盘算出并储存到缓冲器，然后调用Display函数显示出来
{
	int i, j;//循环变量
	wl = 0;
	wp = 0;
	for (j = 0; j <= MAXIMUS; j++)//写入出交点左上角的字符，因为需要打印棋盘右下角，所以很以横纵各多一次循环
	{
		for (i = 0; i <= MAXIMUS; i++) {
			write(getCurse(i, j));//写入左上角字符
			if (j == 0 || j == MAXIMUS)//如果是棋上下盘边缘则没有连接的竖线，用空格填充位置
			{
				if (i != MAXIMUS)
					write("　");
			} else//如果在棋盘中间则用竖线承接上下
			{
				if (i == 0 || i == MAXIMUS - 1)//左右边缘的竖线更粗
					write("┃");
				else if (i != MAXIMUS)//中间的竖线
					write("│");
			}
		}
		if (j == MAXIMUS)//如果是最后一次循环，则只需要处理边侧字符，交点要少一排
		{
			break;
		}
		ln();//提行开始打印交点内容
		write("　");//用空位补齐位置
		for (i = 0; i < MAXIMUS; i++)//按横坐标循环正常的次数
		{
			write(getStyle(i, j));//写入交点字符
			if (i != MAXIMUS - 1)//如果不在最右侧则补充一个横线承接左右
			{
				if (j == 0 || j == MAXIMUS - 1) {
					write("━");//上下边缘的横线更粗
				} else {
					write("—");//中间的横线
				}
			}
		}
		ln();//写完一行后提行
	}
	Display();//将缓冲器内容输出到屏幕
}

int Put() {//在当前光标位置走子，如果非空，则返回0表示失败
	if (p[Cx][Cy] == 0) {
		p[Cx][Cy] = Now;//改变该位置数据
		return 1;//返回1表示成功
	} else {
		return 0;
	}
}

int Check()//胜负检查，即判断当前走子位置有没有造成五连珠的情况
{
	int w = 1, x = 1, y = 1, z = 1, i;//累计横竖正斜反邪四个方向的连续相同棋子数目
	for (i = 1; i < 5; i++)if (Cy + i < MAXIMUS && p[Cx][Cy + i] == Now)w++; else break;//向下检查
	for (i = 1; i < 5; i++)if (Cy - i > 0 && p[Cx][Cy - i] == Now)w++; else break;//向上检查
	if (w >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i < 5; i++)if (Cx + i < MAXIMUS && p[Cx + i][Cy] == Now)x++; else break;//向右检查
	for (i = 1; i < 5; i++)if (Cx - i > 0 && p[Cx - i][Cy] == Now)x++; else break;//向左检查
	if (x >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i < 5; i++)if (Cx + i < MAXIMUS && Cy + i < MAXIMUS && p[Cx + i][Cy + i] == Now)y++; else break;//向右下检查
	for (i = 1; i < 5; i++)if (Cx - i > 0 && Cy - i > 0 && p[Cx - i][Cy - i] == Now)y++; else break;//向左上检查
	if (y >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i < 5; i++)if (Cx + i < MAXIMUS && Cy - i > 0 && p[Cx + i][Cy - i] == Now)z++; else break;//向右上检查
	for (i = 1; i < 5; i++)if (Cx - i > 0 && Cy + i < MAXIMUS && p[Cx - i][Cy + i] == Now)z++; else break;//向左下检查
	if (z >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	return 0;//若没有检查到五连珠，则返回0表示还没有玩家达成胜利
}

int RunGame()//进行整个对局，返回赢家信息(虽然有用上)
{
	int input;//输入变量
	int victor;//赢家信息
	Initialize();//初始化对局
	while (1) {//开始无限回合的死循环，直到出现胜利跳出
		Print();//打印棋盘
		input = getch();//等待键盘按下一个字符
		if (input == 27)//如果是ESC则退出程序
		{
			exit(0);
		} else if (input == 0x20)//如果是空格则开始走子
		{
			if (Put())//如果走子成功则判断胜负
			{
				victor = Check();
				Now = 3 - Now;//轮换当前走子玩家
				count++;
				if (victor == 1)//如果黑方达到胜利，显示提示文字并等待一次按键，返回胜利信息
				{
					showText = "黑方获得了胜利！";
					Print();
					if (getch() == 0xE0) {
						getch();
					}
					return Now;
				} else if (victor == 2)//如果白方达到胜利，显示提示文字并等待一次按键，返回胜利信息
				{
					showText = "白方获得了胜利！";
					Display();
					if (getch() == 0xE0) {
						getch();
					}
					return Now;
				} else if (count == MAXIMUS * MAXIMUS)//如果回合数达到了棋盘总量，即棋盘充满，即为平局
				{
					showText = "平局！";
					Display();
					if (getch() == 0xE0) {
						getch();
					}
					return 0;
				}
			}
		} else if (input == 0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
		{
			input = getch();//获得第二次输入信息
			switch (input)//判断方向键方向并移动光标位置
			{
				case 0x4B://
					Cx--;
					break;
				case 0x48:
					Cy--;
					break;
				case 0x4D:
					Cx++;
					break;
				case 0x50:
					Cy++;
					break;
			}
			if (Cx < 0)Cx = MAXIMUS - 1;//如果光标位置越界则移动到对侧
			if (Cy < 0)Cy = MAXIMUS - 1;
			if (Cx > MAXIMUS - 1)Cx = 0;
			if (Cy > MAXIMUS - 1)Cy = 0;
		}
	}
}

int main()//主函数
{
	system("title 简易五子棋");//设置标题
	system("mode con cols=63 lines=32");//设置窗口大小
	system("color E0");//设置颜色
	while (1) {//循环执行游戏
		RunGame();
	}
}

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>


#define MAXIMUS 15 //定义棋盘大小


int p[MAXIMUS][MAXIMUS];//存储对局信息
char buff[MAXIMUS * 2 + 1][MAXIMUS * 4 + 3];//输出缓冲器
int Cx, Cy;//当前光标位置
int Now;//当前走子的玩家，1代表黑，2代表白
int wl, wp;//当前写入缓冲器的列数和行数位置
char* showText;//在棋盘中央显示的文字信息
int count;//回合数


char* Copy(char* strDest, const char* strSrc)//修改过的字符串复制函数，会忽略末端的\0
{
	char* strDestCopy = strDest;
	while (*strSrc != '\0') {
		*strDest++ = *strSrc++;
	}
	return strDestCopy;
}

void Initialize()//初始化一个对局函数
{
	int i, j;//循环变量
	showText = "";//重置显示信息
	count = 0;//回合数归零
	for (i = 0; i < MAXIMUS; i++)//重置对局数据
	{
		for (j = 0; j < MAXIMUS; j++) {
			p[i][j] = 0;
		}
	}
	Cx = Cy = MAXIMUS / 2;//重置光标到中央
	Now = 1;//重置当前为黑方
}

char* getStyle(int i, int j)//获得棋盘中指定坐标交点位置的字符，通过制表符拼成棋盘
{
	if (p[i][j] == 1)//1为黑子
		return "●";
	else if (p[i][j] == 2)//2为白子
		return "○";
	else if (i == 0 && j == 0)//以下为边缘棋盘样式
		return "┏";
	else if (i == MAXIMUS - 1 && j == 0)
		return "┓";
	else if (i == MAXIMUS - 1 && j == MAXIMUS - 1)
		return "┛";
	else if (i == 0 && j == MAXIMUS - 1)
		return "┗";
	else if (i == 0)
		return "┠";
	else if (i == MAXIMUS - 1)
		return "┨";
	else if (j == 0)
		return "┯";
	else if (j == MAXIMUS - 1)
		return "┷";
	return "┼";//中间的空位
}

char* getCurse(int i, int j) {//获得指定坐标交点位置左上格的样式，通过制表符来模拟光标的显示
	if (i == Cx) {
		if (j == Cy)
			return "┏";
		else if (j == Cy + 1)
			return "┗";
	} else if (i == Cx + 1) {
		if (j == Cy)
			return "┓";
		else if (j == Cy + 1)
			return "┛";
	}
	return "　";//如果不在光标附近则为空
}

void write(char* c)//向缓冲器写入字符串
{
	Copy(buff[wl] + wp, c);
	wp += strlen(c);
}

void ln()//缓冲器写入位置提行
{
	wl += 1;
	wp = 0;
}

void Display()//将缓冲器内容输出到屏幕
{
	int i, l = strlen(showText);//循环变量，中间文字信息的长度
	int Offset = MAXIMUS * 2 + 2 - l / 2;//算出中间文字信息居中显示所在的横坐标位置
	if (Offset % 2 == 1)//如果位置为奇数，则移动到偶数，避免混乱
	{
		Offset--;
	}
	Copy(buff[MAXIMUS] + Offset, showText);//讲中间文字信息复制到缓冲器
	if (l % 2 == 1)//如果中间文字长度为半角奇数，则补上空格，避免混乱
	{
		*(buff[MAXIMUS] + Offset + l) = 0x20;
	}
	system("cls");//清理屏幕，准备写入
	for (i = 0; i < MAXIMUS * 2 + 1; i++) {//循环写入每一行


int p[MAXIMUS][MAXIMUS];//存储对局信息
char buff[MAXIMUS * 2 + 1][MAXIMUS * 4 + 3];//输出缓冲器
int Cx, Cy;//当前光标位置
int Now;//当前走子的玩家，1代表黑，2代表白
int wl, wp;//当前写入缓冲器的列数和行数位置
char* showText;//在棋盘中央显示的文字信息
int count;//回合数


char* Copy(char* strDest, const char* strSrc)//修改过的字符串复制函数，会忽略末端的\0
{
	char* strDestCopy = strDest;
	while (*strSrc != '\0') {
		*strDest++ = *strSrc++;
	}
	return strDestCopy;
}

void Initialize()//初始化一个对局函数
{
	int i, j;//循环变量
	showText = "";//重置显示信息
	count = 0;//回合数归零
	for (i = 0; i < MAXIMUS; i++)//重置对局数据
	{
		for (j = 0; j < MAXIMUS; j++) {
			p[i][j] = 0;
		}
	}
	Cx = Cy = MAXIMUS / 2;//重置光标到中央
	Now = 1;//重置当前为黑方
}


#define MAXIMUS 15 //定义棋盘大小


int p[MAXIMUS][MAXIMUS];//存储对局信息
char buff[MAXIMUS * 2 + 1][MAXIMUS * 4 + 3];//输出缓冲器
int Cx, Cy;//当前光标位置
int Now;//当前走子的玩家，1代表黑，2代表白

}

void Print()//将整个棋盘算出并储存到缓冲器，然后调用Display函数显示出来
{
	int i, j;//循环变量
	wl = 0;
	wp = 0;
	for (j = 0; j <= MAXIMUS; j++)//写入出交点左上角的字符，因为需要打印棋盘右下角，所以很以横纵各多一次循环
	{
		for (i = 0; i <= MAXIMUS; i++) {
			write(getCurse(i, j));//写入左上角字符
			if (j == 0 || j == MAXIMUS)//如果是棋上下盘边缘则没有连接的竖线，用空格填充位置
			{
				if (i != MAXIMUS)
					write("　");
			} else//如果在棋盘中间则用竖线承接上下
			{
				if (i == 0 || i == MAXIMUS - 1)//左右边缘的竖线更粗
					write("┃");
				else if (i != MAXIMUS)//中间的竖线
					write("│");
			}
		}
		if (j == MAXIMUS)//如果是最后一次循环，则只需要处理边侧字符，交点要少一排
		{
			break;
		}
		ln();//提行开始打印交点内容
		write("　");//用空位补齐位置
		for (i = 0; i < MAXIMUS; i++)//按横坐标循环正常的次数
		{
			write(getStyle(i, j));//写入交点字符
			if (i != MAXIMUS - 1)//如果不在最右侧则补充一个横线承接左右
			{
				if (j == 0 || j == MAXIMUS - 1) {
					write("━");//上下边缘的横线更粗
				} else {
					write("—");//中间的横线
				}
			}
		}
		ln();//写完一行后提行
	}
	Display();//将缓冲器内容输出到屏幕
}

int Put() {//在当前光标位置走子，如果非空，则返回0表示失败
	if (p[Cx][Cy] == 0) {
		p[Cx][Cy] = Now;//改变该位置数据
		return 1;//返回1表示成功
	} else {
		return 0;
	}
}

int Check()//胜负检查，即判断当前走子位置有没有造成五连珠的情况
{
	int w = 1, x = 1, y = 1, z = 1, i;//累计横竖正斜反邪四个方向的连续相同棋子数目
	for (i = 1; i < 5; i++)if (Cy + i < MAXIMUS && p[Cx][Cy + i] == Now)w++; else break;//向下检查
	for (i = 1; i < 5; i++)if (Cy - i > 0 && p[Cx][Cy - i] == Now)w++; else break;//向上检查
	if (w >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i < 5; i++)if (Cx + i < MAXIMUS && p[Cx + i][Cy] == Now)x++; else break;//向右检查
	for (i = 1; i < 5; i++)if (Cx - i > 0 && p[Cx - i][Cy] == Now)x++; else break;//向左检查
	if (x >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i < 5; i++)if (Cx + i < MAXIMUS && Cy + i < MAXIMUS && p[Cx + i][Cy + i] == Now)y++; else break;//向右下检查
	for (i = 1; i < 5; i++)if (Cx - i > 0 && Cy - i > 0 && p[Cx - i][Cy - i] == Now)y++; else break;//向左上检查
	if (y >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i < 5; i++)if (Cx + i < MAXIMUS && Cy - i > 0 && p[Cx + i][Cy - i] == Now)z++; else break;//向右上检查
	for (i = 1; i < 5; i++)if (Cx - i > 0 && Cy + i < MAXIMUS && p[Cx - i][Cy + i] == Now)z++; else break;//向左下检查
	if (z >= 5)return Now;//若果达到5个则判断当前走子玩家为赢家
	return 0;//若没有检查到五连珠，则返回0表示还没有玩家达成胜利
}

int RunGame()//进行整个对局，返回赢家信息(虽然有用上)
{
	int input;//输入变量
	int victor;//赢家信息
	Initialize();//初始化对局
	while (1) {//开始无限回合的死循环，直到出现胜利跳出
		Print();//打印棋盘
		input = getch();//等待键盘按下一个字符
		if (input == 27)//如果是ESC则退出程序
		{
			exit(0);
		} else if (input == 0x20)//如果是空格则开始走子
		{
			if (Put())//如果走子成功则判断胜负
			{
				victor = Check();
				Now = 3 - Now;//轮换当前走子玩家
				count++;
				if (victor == 1)//如果黑方达到胜利，显示提示文字并等待一次按键，返回胜利信息
				{
					showText = "黑方获得了胜利！";
					Print();
					if (getch() == 0xE0) {
						getch();
					}
					return Now;
				} else if (victor == 2)//如果白方达到胜利，显示提示文字并等待一次按键，返回胜利信息
				{
					showText = "白方获得了胜利！";
					Display();
					if (getch() == 0xE0) {
						getch();
					}
					return Now;
				} else if (count == MAXIMUS * MAXIMUS)//如果回合数达到了棋盘总量，即棋盘充满，即为平局
				{
					showText = "平局！";
					Display();
					if (getch() == 0xE0) {
						getch();
					}
					return 0;
				}
			}
		} else if (input == 0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
		{
			input = getch();//获得第二次输入信息
			switch (input)//判断方向键方向并移动光标位置
			{
				case 0x4B://
					Cx--;
					break;
				case 0x48:
					Cy--;
					break;
				case 0x4D:
					Cx++;
					break;
				case 0x50:
					Cy++;
					break;
			}
			if (Cx < 0)Cx = MAXIMUS - 1;//如果光标位置越界则移动到对侧
			if (Cy < 0)Cy = MAXIMUS - 1;
			if (Cx > MAXIMUS - 1)Cx = 0;
			if (Cy > MAXIMUS - 1)Cy = 0;
		}
	}
}

int main()//主函数
{
	system("title 简易五子棋");//设置标题
	system("mode con cols=63 lines=32");//设置窗口大小
	system("color E0");//设置颜色
	while (1) {//循环执行游戏
		RunGame();
	}
}