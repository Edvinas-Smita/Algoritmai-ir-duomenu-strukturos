#include <stdlib.h>
#include <stdio.h>

char board[8][8];

void clearBoard();
void clearVision();
void drawVision();
void printBoard();

char countBlindSpots();
char withinBounds(char x, char y);

void placeHorse(char x, char y);
void removeHorse(char x, char y);

void placeMirrored(char x, char y);
void removeMirrored(char x, char y);

void bruteforceMirrored();



void clearBoard()
{
	char i;
	for (i = 0; i < 64; ++i)
	{
		board[i % 8][i / 8] = 0;
	}
}

void clearVision()
{
	char x;
	for (x = 0; x < 64; ++x)
	{
		if (board[x / 8][x % 8] == 2)
		{
			board[x / 8][x % 8] = 0;
		}
	}
}

void drawVision()
{
	char x, y;
	for (y = 0; y < 8; ++y)
	{
		for (x = 0; x < 8; ++x)
		{
			if (board[x][y] == 1)
			{
				if (withinBounds(x - 2, y - 1))
				{
					if (board[x - 2][y - 1] == 0)
					{
						board[x - 2][y - 1] = 2;
					}
				}
				if (withinBounds(x - 2, y + 1))
				{
					if (board[x - 2][y + 1] == 0)
					{
						board[x - 2][y + 1] = 2;
					}
				}

				if (withinBounds(x + 2, y - 1))
				{
					if (board[x + 2][y - 1] == 0)
					{
						board[x + 2][y - 1] = 2;
					}
				}
				if (withinBounds(x + 2, y + 1))
				{
					if (board[x + 2][y + 1] == 0)
					{
						board[x + 2][y + 1] = 2;
					}
				}

				if (withinBounds(x - 1, y - 2))
				{
					if (board[x - 1][y - 2] == 0)
					{
						board[x - 1][y - 2] = 2;
					}
				}
				if (withinBounds(x + 1, y - 2))
				{
					if (board[x + 1][y - 2] == 0)
					{
						board[x + 1][y - 2] = 2;
					}
				}

				if (withinBounds(x - 1, y + 2))
				{
					if (board[x - 1][y + 2] == 0)
					{
						board[x - 1][y + 2] = 2;
					}
				}
				if (withinBounds(x + 1, y + 2))
				{
					if (board[x + 1][y + 2] == 0)
					{
						board[x + 1][y + 2] = 2;
					}
				}
			}
		}
	}
}


char withinBounds(char x, char y)
{
	return (x > 7 || x < 0 || y > 7 || y < 0) ? 0 : 1;
}

char countBlindSpots()
{
	char i, spots = 0;
	drawVision();
	for (i = 0; i < 64; ++i)
	{
		if (board[i % 8][i / 8] == 0)
		{
			++spots;
		}
	}
	clearVision();
	return spots;
}

void printBoard()
{
	char cp, x, y;
	drawVision();
	printf("---0--1--2--3--4--5--6--7---\n");
	for (y = 0; y < 8; ++y)
	{
		printf("|                          |\n%x  ", y);
		for (x = 0; x < 8; ++x)
		{
			cp = board[x][y];
			//printf("%s  ", cp == 0 ? "\u25A1" : cp == 1 ? "\u265E" : cp == 2 ? "\u25A3" : "?");
			printf("%c  ", cp == 0 ? '.' : cp == 1 ? '2' : cp == 2 ? 'x' : '?');
		}
		printf("|\n");
	}
	printf("|                          |\n----------------------------\n");
	clearVision();
}


void removeHorse(char x, char y)
{
	if (!withinBounds(x, y))
	{
		return;
	}
	if (board[x][y] != 1)
	{
		return;
	}
	board[x][y] = 0;
}

void placeHorse(char x, char y)
{
	if (!withinBounds(x, y))
	{
		return;
	}
	if (board[x][y] == 1)
	{
		return;
	}
	board[x][y] = 1;
}


void placeMirrored(char x, char y)
{
	placeHorse(x, y);			placeHorse(7 - y, x);

	placeHorse(y, 7 - x);		placeHorse(7 - x, 7 - y);
}

void removeMirrored(char x, char y)
{
	removeHorse(x, y);			removeHorse(7 - y, x);

	removeHorse(y, 7 - x);		removeHorse(7 - x, 7 - y);
}


void bruteforceMirrored()
{
	char i, j, k;
	for (i = 0; i < 14; ++i)
	{
		placeMirrored(i % 4, i / 4);
		for (j = i + 1; j < 15; ++j)
		{
			placeMirrored(j % 4, j / 4);
			for (k = j + 1; k < 16; ++k)
			{
				placeMirrored(k % 4, k / 4);
				if (!countBlindSpots())
				{
					printBoard();
					//return;
				}
				removeMirrored(k % 4, k / 4);
			}
			removeMirrored(j % 4, j / 4);
		}
		removeMirrored(i % 4, i / 4);
	}
}

int main()
{
	clearBoard();

	bruteforceMirrored();
	return 0;
}
