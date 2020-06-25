#include "Snake.h"



Snake::Snake()
{
	Head = NULL;
	Direction = LEFT;
}


void Snake::DeleteMap(int Map[][MAX])
{
	Map[Head->y][Head->x] = NULL;
	Node* temp = Head->Next;
	while (temp != NULL)
	{
		Map[temp->y][temp->x] = NULL;
		temp = temp->Next;
	}
}

void Snake::Move(int Map[][MAX])
{
	DeleteMap(Map);
	Head->LastX = Head->x;
	Head->LastY = Head->y;
	switch (Direction)
	{
	case LEFT:
		Head->x--;
		break;
	case RIGHT:
		Head->x++;
		break;
	case UP:
		Head->y--;
		break;
	case DOWN:
		Head->y++;
		break;
	}
	MoveTail(Head);
	UpdateMap(Map);
}

void Snake::MoveTail(Node* Node)
{
	if (Node->Next == NULL)
		return;
	Node->Next->LastX = Node->Next->x;
	Node->Next->LastY = Node->Next->y;
	Node->Next->x = Node->LastX;
	Node->Next->y = Node->LastY;
	MoveTail(Node->Next);
}


void Snake::DeleteSnake(Node* Node)
{
	if (Node == NULL)
		return;
	DeleteSnake(Node->Next);
	delete Node;
}

void Snake::SetSnake(int x, int y)
{
	if (Head != NULL)
	{
		DeleteSnake(Head);
		Head = NULL;
	}
	Head = new  Node;
	Head->x = x;
	Head->y = y;
	Head->Next = NULL;
	for (int i = 1; i <= 2; i++)
	{
		Node* add = new Node;
		add->x = Head->x + i;
		add->y = Head->y;
		add->Next = NULL;
		Node* temp = Head;
		while (temp->Next != NULL)
			temp = temp->Next;
		temp->Next = add;
	}
	OldClock = clock();
}

bool Snake::Update(int Map[][MAX])
{
	if (clock() - OldClock >= SPEED)
	{
		Move(Map);
		OldClock = clock();
		return true;
	}
	return false;
}

void Snake::Input()
{
	if (kbhit())
	{
		char ch = getch();
		switch (ch)
		{
		case LEFT_KEY:
			if (Direction != RIGHT)
				Direction = LEFT;
			break;
		case RIGHT_KEY:
			if (Direction != LEFT)
				Direction = RIGHT;
			break;
		case UP_KEY:
			if (Direction != DOWN)
				Direction = UP;
			break;
		case DOWN_KEY:
			if (Direction != UP)
				Direction = DOWN;
			break;
		}
	}
}

void Snake::UpdateMap(int Map[][MAX])
{
	Map[Head->y][Head->x] = HEAD;
	Node* temp = Head->Next;
	while (temp != NULL)
	{
		Map[temp->y][temp->x] = TAIL;
		temp = temp->Next;
	}
}

Snake::~Snake()
{
	if (Head != NULL)
	{
		DeleteSnake(Head);
		Head = NULL;
	}
}