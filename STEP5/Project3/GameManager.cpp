#include "GameManager.h"



GameManager::GameManager()
{
	Stage = 1;
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
			{
				if (rand() % 100 == 0)
					Map[y][x] = WALL;
				else
					Map[y][x] = NULL;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map1[y][x] = IMMUNE_WALL;
				else
					Map1[y][x] = WALL;
			}
			else
			{
				if (rand() %70 == 0)
					Map1[y][x] = WALL;
				else
					Map1[y][x] = NULL;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map2[y][x] = IMMUNE_WALL;
				else
					Map2[y][x] = WALL;
			}
			else
			{
				if (rand() % 50 == 0)
					Map2[y][x] = WALL;
				else
					Map2[y][x] = NULL;
			}
		}
	}

	for (int y = 0; y < MAX; y++)
	{
		for (int x = 0; x < MAX; x++)
		{
			if (x == 0 || x == MAX - 1 || y == 0 || y == MAX - 1)
			{
				if ((x == 0 && y == 0) || (x == 0 && y == MAX - 1) || (x == MAX - 1 && y == 0) || (x == MAX - 1 && y == MAX - 1))
					Map3[y][x] = IMMUNE_WALL;
				else
					Map3[y][x] = WALL;
			}
			else
			{
				if (rand() % 30 == 0)
					Map3[y][x] = WALL;
				else
					Map3[y][x] = NULL;
			}
		}
	}
	mission[0].MaxLevel = 1;
	mission[0].LevelCheck = false;
	mission[0].MaxGrowth = 1;
	mission[0].GrowthCheck = false;
	mission[0].MaxPoison = 1;
	mission[0].PoisonCheck = false;
	mission[0].MaxGate = 1;
	mission[0].GateCheck = false;


	mission[1].MaxLevel = 16;
	mission[1].LevelCheck = false;
	mission[1].MaxGrowth = 15;
	mission[1].GrowthCheck = false;
	mission[1].MaxPoison = 11;
	mission[1].PoisonCheck = false;
	mission[1].MaxGate = 9;
	mission[1].GateCheck = false;


	mission[2].MaxLevel = 19;
	mission[2].LevelCheck = false;
	mission[2].MaxGrowth = 18;
	mission[2].GrowthCheck = false;
	mission[2].MaxPoison = 14;
	mission[2].PoisonCheck = false;
	mission[2].MaxGate = 12;
	mission[2].GateCheck = false;


	mission[3].MaxLevel = 22;
	mission[3].LevelCheck = false;
	mission[3].MaxGrowth = 21;
	mission[3].GrowthCheck = false;
	mission[3].MaxPoison = 16;
	mission[3].PoisonCheck = false;
	mission[3].MaxGate = 15;
	mission[3].GateCheck = false;

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


void GameManager::MapDraw(int Map[MAX][MAX])
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
		if (y == 0)
			cout << "\tScore Board" << "  " << Stage << " Stage";
		else if (y == 1)
			cout << "\tB : " << snake.GetLevel() << "/" << mission[Stage - 1].MaxLevel;
		else if (y == 2)
			cout << "\t+ : " << snake.GetGrowth();
		else if (y == 3)
			cout << "\t- : " << snake.GetPosion();
		else if (y == 4)
			cout << "\tG : " << snake.GetGate();
		else if (y == 7)
			cout << "\t Mission";
		else if (y == 8)
			cout << "\tB : " << mission[Stage - 1].MaxLevel << " (" << (mission[Stage - 1].LevelCheck ? "v" : " ") << ")";
		else if (y == 9)
			cout << "\t+ : " << mission[Stage - 1].MaxGrowth << " (" << (mission[Stage - 1].GrowthCheck ? "v" : " ") << ")";
		else if (y == 10)
			cout << "\t- : " << mission[Stage - 1].MaxPoison << " (" << (mission[Stage - 1].PoisonCheck ? "v" : " ") << ")";
		else if (y == 11)
			cout << "\tG : " << mission[Stage - 1].MaxGate << " (" << (mission[Stage - 1].GateCheck ? "v" : " ") << ")";
		cout << endl;
	}
}


void GameManager::Update(int Map[MAX][MAX])
{
	if (clock() - OldItemClock >= CREATE_ITEM_TIME)
	{
		SetItem(Map);
		OldItemClock = clock();
	}
	if (clock() - OldGateClock >= CREATE_GATE_TIME)
	{
		SetGate(Map);
		OldGateClock = clock();
	}
}

void GameManager::SetGate(int Map[MAX][MAX])
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

void GameManager::SetItem(int Map[MAX][MAX])
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


bool GameManager::MissionCheck()
{
	if (mission[Stage - 1].MaxLevel <= snake.GetLevel())
		mission[Stage - 1].LevelCheck = true;
	if (mission[Stage - 1].MaxGrowth <= snake.GetGrowth())
		mission[Stage - 1].GrowthCheck = true;
	if (mission[Stage - 1].MaxPoison <= snake.GetPosion())
		mission[Stage - 1].PoisonCheck = true;
	if (mission[Stage - 1].MaxGate <= snake.GetGate())
		mission[Stage - 1].GateCheck = true;
	if (mission[Stage - 1].GateCheck && mission[Stage - 1].GrowthCheck && mission[Stage - 1].LevelCheck && mission[Stage - 1].PoisonCheck)
		return true;
	return false;
}

void GameManager::GamePlay()
{
	snake.SetSnake(MAX / 2 - 2, MAX / 2);
	snake.UpdateMap(Map);
	while (true)
	{
		bool Check;
		if (Stage == 1)
		{
			Update(Map);
			Check = snake.Update(Map, Gate);
		}
		else if (Stage == 2)
		{
			Update(Map1);
			Check = snake.Update(Map1, Gate);
		}
		else if (Stage == 3)
		{
			Update(Map2);
			Check = snake.Update(Map2, Gate);
		}
		else
		{
			Update(Map3);
			Check = snake.Update(Map3, Gate);
		}
		if (Check)
		{
			if (MissionCheck())
			{
				Stage++;
				if (Stage > 4)
					exit(1);
				else
				{
					for (int y = 0; y < MAX; y++)
					{
						for (int x = 0; x < MAX; x++)
						{
							if (Map[y][x] == HEAD || Map[y][x] == TAIL)
								Map[y][x] = NULL;
						}
					}
					snake.SetSnake(MAX / 2 - 2, MAX / 2);
					snake.UpdateMap(Map);
					OldItemClock = clock();
					OldGateClock = clock();
					Map[Gate[0].y][Gate[0].x] = WALL;
					Map[Gate[1].y][Gate[1].x] = WALL;
				}
			}
			if (Stage == 1)
				MapDraw(Map);
			else if (Stage == 2)
				MapDraw(Map1);
			else if (Stage == 3)
				MapDraw(Map2);
			else
				MapDraw(Map3);
		}
		snake.Input();
	}
}

GameManager::~GameManager()
{

}