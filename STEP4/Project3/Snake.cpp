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


bool Snake::CheckNode(int x, int y)
{

	Node* temp = Head;
	while (temp != NULL)
	{
		if (temp->x == x && temp->y == y)
			return true;
		temp = temp->Next;
	}
	return false;
}

void Snake::GateCheck(int Map[][MAX], Gate gate[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (gate[i].x == Head->x && gate[i].y == Head->y)
		{
			if (gate[!i].x == 0)
			{
				Direction = RIGHT;
				Head->x = gate[!i].x + 1;
				Head->y = gate[!i].y;
			}
			else if( gate[!i].x == MAX - 1)
			{
				Direction = LEFT;
				Head->x = gate[!i].x - 1;
				Head->y = gate[!i].y;
			}
			else if (gate[!i].y == 0)
			{
				Direction = DOWN;
				Head->x = gate[!i].x ;
				Head->y = gate[!i].y + 1;
			}
			else if (gate[!i].y == MAX - 1)
			{
				Direction = UP;
				Head->x = gate[!i].x;
				Head->y = gate[!i].y - 1;
			}
			return;
		}
	}
}

void Snake::Poison() 
{
	Node* temp = Head;
	while (temp->Next != NULL)
	{
		if (temp->Next->Next == NULL)
		{
			delete temp->Next;
			temp->Next = NULL;
			Level--;
			return;
		}
		temp = temp->Next;
	}
}

void Snake::Growth()
{
	Node* temp = Head;
	while (temp->Next != NULL)
		temp = temp->Next;
	temp->Next = new Node;
	temp->Next->x = temp->LastX;
	temp->Next->y = temp->LastY;
	temp->Next->Next = NULL;
	Level++;
}

void Snake::ItemCheck(int Map[MAX][MAX])
{
	switch (Map[Head->y][Head->x])
	{
	case GROWTH:
		Growth();
		break;
	case POISON:
		Poison();
		break;
	}
}

void Snake::Move(int Map[][MAX], Gate gate[2])
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
	GateCheck(Map, gate);
	if (Map[Head->y][Head->x] == WALL)
	{
		DeleteSnake(Head);
		exit(1);
	}
	MoveTail(Head);
	ItemCheck(Map);
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
	Level = 3;
}

bool Snake::Update(int Map[][MAX], Gate gate[2])
{
	if (clock() - OldClock >= SPEED)
	{
		Move(Map,gate);
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