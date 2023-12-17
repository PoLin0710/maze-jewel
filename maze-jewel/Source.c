#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 31

int count = 0;

void find(char maze[][SIZE], int start[]) //找起點(一律在右邊)放入start[2]={X,Y} 
{
	for (int i = 0; i < SIZE; i++)
	{
		if (maze[i][0] == '.')
		{
			start[0] = 0;
			start[1] = i;
			break;
		}
	}
}
int findend(char maze[][SIZE], int start[], int x, int y, int dir) 
{
	if (maze[y][x] == 'O')count++;
	maze[y][x] = '@';
	int checkrighty[4] = { 1,0,-1,0 };
	int checkrightx[4] = { 0,-1,0,1 };
	int checktowardy[4] = { 0,1,0,-1 };
	int checktowardx[4] = { 1,0,-1,0 };
	int move = 0;

	if (maze[y + checkrighty[dir]][x + checkrightx[dir]] != '#'&& maze[y + checkrighty[dir]][x + checkrightx[dir]] != 'X')
	{
		move = 1;
		y += checkrighty[dir];
		x += checkrightx[dir];
		dir = (dir + 1) % 4;
	}
	else
	{
		if (maze[y + checktowardy[dir]][x + checktowardx[dir]] == '#'&& maze[y + checktowardy[dir]][x + checktowardx[dir]] == 'X')
			dir = dir - 1 < 0 ? 3 : dir - 1;
		dir = dir - 1 < 0 ? 3 : dir - 1;
	}
	if (move == 1 && x == 0)//繞回原點代表沒有終點
		return 0;
	findend(maze, start, x, y, dir);
}

void print(char maze[][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	FILE* Input;
	if ((Input = fopen("input.txt", "r")) == NULL)
	{
		printf("error");
		return 0;
	}
	char maze[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) //input
	{
		for (int j = 0; j < SIZE; j++)
		{
			maze[i][j] = fgetc(Input);//讀每行字
		}
		fgetc(Input);//讀換行'\n'
	}

	int start[2] = { -1,-1 };
	find(maze[0], start);
	findend(maze, start, start[0], start[1], 0);
	printf("Total jewel:%d\n",count);
	print(maze);

}