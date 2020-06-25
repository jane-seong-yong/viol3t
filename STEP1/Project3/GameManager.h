#pragma once
#include<iostream>
#include<Windows.h>
#include"Mecro.h"
#include"Snake.h"
using namespace std;
class GameManager
{
private:
	Snake snake;
	int Map[MAX][MAX];
public:
	void MapDraw();
	void GamePlay();
	GameManager();
	~GameManager();
};

