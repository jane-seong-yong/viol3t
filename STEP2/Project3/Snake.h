#pragma once
#include"Mecro.h"

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Node
{
	int x;
	int y;
	int LastX;
	int LastY;
	Node* Next;
};

class Snake
{
private:
	Node* Head;
	DIRECTION Direction;
	int OldClock;
public:
	void Input();
	void DeleteMap(int Map[][MAX]);
	void DeleteSnake(Node* Node);
	void SetSnake(int x, int y);
	bool Update(int Map[][MAX]);
	void UpdateMap(int Map[][MAX]);
	void Move(int Map[][MAX]);
	void MoveTail(Node* Node);
	Snake();
	~Snake();
};

