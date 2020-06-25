#pragma once
#include"Mecro.h"
#include"Snake.h"
using namespace std;
struct ITEM
{
	int x;
	int y;
	bool Growth;
};
class GameManager
{
private:
	Snake snake;
	int Map[MAX][MAX];
	ITEM ItemList[3];
	int OldItemClock;
public:
	void Update();
	void SetItem();
	void MapDraw();
	void GamePlay();
	GameManager();
	~GameManager();
};

