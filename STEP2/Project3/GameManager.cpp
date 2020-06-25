#include "GameManager.h"



GameManager::GameManager()
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
				Map[y][x] = WALL;
			else
				Map[y][x] = NULL;
		}
	}
}


void GameManager::MapDraw()
{
	system("cls");
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (Map[y][x] == NULL)
				cout << "  ";
			else if (Map[y][x] == WALL)
			{
				GRAY
					cout << "бс";
				ORIGINAL
			}
			else if (Map[y][x] == HEAD)
			{
				YELLOW
					cout << "бс";
				ORIGINAL
			}
			else if (Map[y][x] == TAIL)
			{
				PLUM
					cout << "бс";
				ORIGINAL
			}
		}
		cout << endl;
	}
}

void GameManager::GamePlay()
{
	snake.SetSnake(MAX / 2 - 2, MAX / 2);
	snake.UpdateMap(Map);
	while (true)
	{
		if(snake.Update(Map))
			MapDraw();
		snake.Input();
	}
}

GameManager::~GameManager()
{

}