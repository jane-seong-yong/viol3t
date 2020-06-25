#pragma once
#include<iostream>
#include<Windows.h>
#include"Mecro.h"
using namespace std;

struct Node
{
	int x;
	int y;
	Node* Next;
};

class Snake
{
private:
	Node* Head;
public:
	void DeleteSnake(Node* Node);
	void SetSnake(int x,int y);
	void Update(int Map[][MAX]);
	Snake();
	~Snake();
};

