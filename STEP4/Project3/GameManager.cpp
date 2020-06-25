#include "GameManager.h"



GameManager::GameManager()
{
	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map[y][x] = IMMUNE_WALL;
				else
					Map[y][x] = WALL;
			}
			else
				Map[y][x] = NULL;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		ItemList[i].x = -1;
		ItemList[i].y = -1;
	}
	for (int i = 0; i < 2; i++)
	{
		Gate[i].x = -1;
		Gate[i].y = -1;
	}
	OldItemClock = clock();
	OldGateClock = clock();
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
			else if (Map[y][x] == GROWTH)
			{
				GREEN
					cout << "бс";
				ORIGINAL
			}
			else if (Map[y][x] == POISON)
			{
				RED
					cout << "бс";
				ORIGINAL
			}
			else if (Map[y][x] == IMMUNE_WALL)
			{
				BLOOD
					cout << "бс";
				ORIGINAL
			}
			else if(Map[y][x] == GATE)
			{
				PUPPLE
					cout << "бс";
				ORIGINAL
			}
		}
		cout << endl;
	}
}


void GameManager::Update()
{
	if (clock() - OldItemClock >= CREATE_ITEM_TIME)
	{
		SetItem();
		OldItemClock = clock();
	}
	if (clock() - OldGateClock >= CREATE_GATE_TIME)
	{
		SetGate();
		OldGateClock = clock();
	}
}

void GameManager::SetGate()
{
	for (int i = 0; i < 2; i++)
	{
		if (Gate[i].x != -1 && Gate[i].y != -1)
			Map[Gate[i].y][Gate[i].x] = WALL;
		if (i == 0)
		{
			Gate[i].x = rand() % 2 == 2 ? 0 : MAX - 1;
			Gate[i].y = rand() % (MAX - 2) + 1;
		}
		else
		{
			Gate[i].x = rand() % (MAX - 2) + 1;
			Gate[i].y = rand() % 2 == 2 ? 0 : MAX - 1;
		}
		Map[Gate[i].y][Gate[i].x] = GATE;
	}
}

void GameManager::SetItem()
{
	for (int i = 0; i < 3; i++)
	{
		if (ItemList[i].x != -1 && ItemList[i].y != -1)
			Map[ItemList[i].y][ItemList[i].x] = NULL;
		ItemList[i].x = rand() % (MAX - 2) + 1;
		ItemList[i].y = rand() % (MAX - 2) + 1;
		if (snake.CheckNode(ItemList[i].x, ItemList[i].x))
		{
			i--;
			continue;
		}
		ItemList[i].Growth = rand() % 2 == 0 ? true : false;
		if (ItemList[i].Growth)
			Map[ItemList[i].y][ItemList[i].x] = GROWTH;
		else
			Map[ItemList[i].y][ItemList[i].x] = POISON;
	}
}

void GameManager::GamePlay()
{
	snake.SetSnake(MAX / 2 - 2, MAX / 2);
	snake.UpdateMap(Map);
	SetItem();
	while (true)
	{
		Update();
		if(snake.Update(Map,Gate))
			MapDraw();
		snake.Input();
	}
}

GameManager::~GameManager()
{

}