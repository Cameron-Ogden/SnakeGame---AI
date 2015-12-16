// C Lewis Ogden

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <math.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <queue>
#include <stack>
#include <concurrent_priority_queue.h>

using namespace std;

// GLOBAL VARIABLES
enum { moveUP, moveRIGHT, moveDOWN, moveLEFT };
stack<int> paths;

int snakeHead_X = 15, snakeHead_Y = 18;
int snakeBody1_X = 15, snakeBody1_Y = 19;
int snakeBody2_X = 15, snakeBody2_Y = 20;
int snakeBody3_X = 16, snakeBody3_Y = 20;
int snakeTail_X = 17, snakeTail_Y = 20;

int foodPosX, foodPosY;

char* worldArray[30][30] = 
{ { "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X" },
  { "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "X" },
{ "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X" }, };


// NODE CLASS STUFF

class Node
{
public:
	Node *parent;
	int cost;
	int depth;

	int path, posX, posY; 
	
	void initNode(Node*, int, int, int);
	int returnPosX();
	int returnPosY();
	bool isValid();
	bool isGoalState();
	bool hasBeenUsed();

};

list<Node> nodeList;

void Node::initNode(Node* par, int pat, int px, int py)
{
	parent = par;
	path = pat;
	posX = px;
	posY = py;
}

bool Node::isValid()
{
	if (worldArray[posX][posY] == " " || worldArray[posX][posY] == "F") return true;
	else																return false;
}

bool Node::isGoalState()
{
	if (worldArray[posX][posY] == "F")	return true;
	else								return false;
}

bool Node::hasBeenUsed()
{
	list<Node>::iterator i;

	for (i = nodeList.begin(); i != nodeList.end(); ++i)
		if (i->posX == posX && i->posY == posY) return true;

	return false;
}


// SEARCHING

void breadthFirstSearch()
{
	queue<Node> fringe;

	nodeList.clear();

	Node *root = new Node();
	root->initNode(NULL, NULL, snakeHead_X, snakeHead_Y);

	nodeList.push_back(*root);
	fringe.push(*root);

	while (!fringe.empty())
	{
		Node *active = new Node();

		*active = fringe.front();
		fringe.pop();

		if (active->isGoalState())
		{
			while (active->parent != NULL)
			{
				paths.push(active->path);
				active = active->parent;

			}
			
			return;
		}

		Node *up = new Node();
		up->initNode(active, moveUP, active->posX, active->posY - 1);

		if (up->isValid() && !up->hasBeenUsed())
		{
			nodeList.push_back(*up);
			fringe.push(*up);
		}

		Node *right = new Node();
		right->initNode(active, moveRIGHT, active->posX + 1, active->posY);

		if (right->isValid() && !right->hasBeenUsed())
		{
			nodeList.push_back(*right);
			fringe.push(*right);
		}

		Node *down = new Node();
		down->initNode(active, moveDOWN, active->posX, active->posY + 1);

		if (down->isValid() && !down->hasBeenUsed())
		{
			nodeList.push_back(*down);
			fringe.push(*down);
		}

		Node *left = new Node();
		left->initNode(active, moveLEFT, active->posX - 1, active->posY);

		if (left->isValid() && !left->hasBeenUsed())
		{
			nodeList.push_back(*left);
			fringe.push(*left);
		}

	}
}

void depthFirstSearch()
{
	stack<Node> fringe;

	nodeList.clear();

	Node *root = new Node();
	root->initNode(NULL, NULL, snakeHead_X, snakeHead_Y);

	nodeList.push_back(*root);
	fringe.push(*root);

	while (!fringe.empty())
	{
		Node *active = new Node();

		*active = fringe.top();
		fringe.pop();

		if (active->isGoalState())
		{
			while (active->parent != NULL)
			{
				paths.push(active->path);
				active = active->parent;

			}

			return;
		}

		Node *up = new Node();
		up->initNode(active, moveUP, active->posX, active->posY - 1);

		if (up->isValid() && !up->hasBeenUsed())
		{
			nodeList.push_back(*up);
			fringe.push(*up);
		}

		Node *right = new Node();
		right->initNode(active, moveRIGHT, active->posX + 1, active->posY);

		if (right->isValid() && !right->hasBeenUsed())
		{
			nodeList.push_back(*right);
			fringe.push(*right);
		}

		Node *down = new Node();
		down->initNode(active, moveDOWN, active->posX, active->posY + 1);

		if (down->isValid() && !down->hasBeenUsed())
		{
			nodeList.push_back(*down);
			fringe.push(*down);
		}

		Node *left = new Node();
		left->initNode(active, moveLEFT, active->posX - 1, active->posY);

		if (left->isValid() && !left->hasBeenUsed())
		{
			nodeList.push_back(*left);
			fringe.push(*left);
		}

	}
}

struct CompareCost {
	bool operator()(Node const & n1, Node const & n2) 
	{
		return n1.cost > n2.cost;
	}
};

void aStarSearch()
{
	priority_queue<Node, vector<Node>, CompareCost>  fringe;

	nodeList.clear();

	Node *root = new Node();
	root->initNode(NULL, NULL, snakeHead_X, snakeHead_Y);

	root->depth = 0;
	root->cost = root->depth + sqrt( (foodPosX - root->posX)*(foodPosX - root->posX) + (foodPosY - root->posY)*(foodPosY - root->posY) );

	nodeList.push_back(*root);
	fringe.push(*root);
	
	while (!fringe.empty())
	{
		Node *active = new Node();

		*active = fringe.top();
		fringe.pop();

		if (active->isGoalState())
		{
			while (active->parent != NULL)
			{
				paths.push(active->path);
				active = active->parent;

			}

			return;
		}

		Node *up = new Node();
		up->initNode(active, moveUP, active->posX, active->posY - 1);

		up->depth = active->depth + 1;
		up->cost = up->depth + sqrt((foodPosX - up->posX)*(foodPosX - up->posX) + (foodPosY - up->posY)*(foodPosY - up->posY));

		if (up->isValid() && !up->hasBeenUsed())
		{
			nodeList.push_back(*up);
			fringe.push(*up);
		}

		Node *right = new Node();
		right->initNode(active, moveRIGHT, active->posX + 1, active->posY);

		right->depth = active->depth + 1;
		right->cost = right->depth + sqrt((foodPosX - right->posX)*(foodPosX - right->posX) + (foodPosY - right->posY)*(foodPosY - right->posY));

		if (right->isValid() && !right->hasBeenUsed())
		{
			nodeList.push_back(*right);
			fringe.push(*right);
		}

		Node *down = new Node();
		down->initNode(active, moveDOWN, active->posX, active->posY + 1);

		down->depth = active->depth + 1;
		down->cost = down->depth + sqrt((foodPosX - down->posX)*(foodPosX - down->posX) + (foodPosY - down->posY)*(foodPosY - down->posY));

		if (down->isValid() && !down->hasBeenUsed())
		{
			nodeList.push_back(*down);
			fringe.push(*down);
		}

		Node *left = new Node();
		left->initNode(active, moveLEFT, active->posX - 1, active->posY);

		left->depth = active->depth + 1;
		left->cost = left->depth + sqrt((foodPosX - left->posX)*(foodPosX - left->posX) + (foodPosY - left->posY)*(foodPosY - left->posY));

		if (left->isValid() && !left->hasBeenUsed())
		{
			nodeList.push_back(*left);
			fringe.push(*left);
		}

	}

}

// FUNCTIONS

void printWorld()
{
	system("CLS");
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			printf("%s", worldArray[j][i]);
		}
		printf("\n");
	}

}

void placeFood()
{
	srand(time(NULL));

	int foodX, foodY;
	bool foodPlaced = false;

	while (!foodPlaced)
	{
		//put in the range 1 to 23
		foodX = rand() % 24 + 1;
		foodY = rand() % 24 + 1;

		//if the random spot is valid, place food and break
		if (worldArray[foodX][foodY] == " ")
		{
			worldArray[foodX][foodY] = "F";
			foodPlaced = true;
		}

	}
	foodPosX = foodX;
	foodPosY = foodY;
	
}

void addObstacles()
{
	srand(time(NULL));

	int X, Y, count = 0;
	bool placed = false;

	while (!placed)
	{
		X = rand() % 30 + 1;
		Y = rand() % 30 + 1;

		if (worldArray[X][Y] == " ")
		{
			worldArray[X][Y] = "x";
			count++;

			if (count > 30) placed = true;
		}
	}
}

void moveSnake(int move)
{
	worldArray[snakeTail_X][snakeTail_Y] = " ";

	snakeTail_X = snakeBody3_X;		snakeTail_Y = snakeBody3_Y;
	snakeBody3_X = snakeBody2_X;	snakeBody3_Y = snakeBody2_Y;
	snakeBody2_X = snakeBody1_X;	snakeBody2_Y = snakeBody1_Y;
	snakeBody1_X = snakeHead_X;		snakeBody1_Y = snakeHead_Y;

	worldArray[snakeBody1_X][snakeBody1_Y] = "o";

	switch (move) {
		//remember [0][0] is the top left 
	case moveUP:
		snakeHead_Y--;
		break;

	case moveRIGHT:
		snakeHead_X++;
		break;

	case moveDOWN:
		snakeHead_Y++;
		break;

	case moveLEFT:
		snakeHead_X--;
		break;

	default:
		break;
	}

	worldArray[snakeHead_X][snakeHead_Y] = "@";
	printWorld();

}


// MAIN LOOP
 
int main()
{
	// set up the world
	moveSnake(moveUP);
	moveSnake(moveRIGHT);
	moveSnake(moveDOWN);
	moveSnake(moveLEFT);

	placeFood();
	addObstacles();
	printWorld();


	//display to 
	while (true) 
	{
		//breadthFirstSearch();
		depthFirstSearch();
		//aStarSearch();
		while (!paths.empty())
		{
			moveSnake(paths.top());
			paths.pop();
		}
		placeFood();
		printWorld();
	}

	return 0;
}