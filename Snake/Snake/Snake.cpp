// Snake.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <windows.h> 

using namespace std;

# pragma region Variables

/*--- BOOLEANS ---*/

// Decides when the game is over.
bool gameOver;

/*--- CONSTANTS ---*/

// The width of the game screen.
const int width = 20;
// The height of the game screen.
const int height = 10;
// The character used for walls.
const char wall = '#';
// The character used for the snake's head.
const char head = 'O';
// The character used for the snake's tail.
const char tail = 'o';
// The character used for fruit in the board.
const char fruit = 'X';

/*--- INTEGERS ---*/

// The x and y cooridnates of the snake head.
int playerX, playerY;
// The x and y coordinates of a piece of fruit.
int fruitX, fruitY;
// The total score in the game.
int score;
// The length of the tail.
int tailLength;
// The amount of segments in the tail's position. 
int tailX[100], tailY[100];

/*--- ENUMS ---*/

// Enum that contains player directions.
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
// The current movement direction of the player.
Direction currentDirection;

#pragma endregion

#pragma region Functions

// Set's up the game.
void Setup ()
{
	// The game begins in play.
	gameOver = false;
	// Set the default movement of the snake to stop.
	currentDirection = STOP;

	// Create the x position of the snake head at half the width of the game screen.
	playerX = width / 2;
	// Create the y position of the snake head half the height of the game screen.
	playerY = height / 2;

	// Spawn a fruit piece at a random point between the width and height of the game.
	fruitX = rand() % width;
	fruitY = rand() % height;

	// Set the default score to 0;
	score = 0;
}

// Draws the game's graphics.
void Draw ()
{
	// Clear the console window.
	system("cls");

	// Create the top wall.
	for (int i = 0; i < width + 2; i++)
	{
		cout << wall;
	}
	cout << endl;

	// Create the side walls by a printing a matrix.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Print the left wall.
			if (j == 0)
			{
				cout << wall;
			}

			// Is the iterated position where the player should spawn?
			if (i == playerY && j == playerX)
			{
				// Spawn the player symbol.
				cout << head;
			}
			// Is the iterated position where a fruit should be spawned?
			else if (i == fruitY && j == fruitX)
			{
				// Spawn a fruit symbol.
				cout << fruit;
			}
			else
			{
				// Has a tail been printed? (Default is no.)
				bool tailPrinted = false;

				// Loop through the tail.
				for (int k = 0; k < tailLength; k++)
				{
					// If the the current tail's coordinates are equal to the current iterated coordinates.
					if (tailX[k] == j && tailY[k] == i)
					{
						// Spawn the player symbol.
						cout << tail;
						// A tail has been printed.
						tailPrinted = true;
					}
				}

				// If no tail has been printed.
				if (!tailPrinted)
				{
					// Print a gap.
					cout << " ";
				}
			}

			// Print the right wall.
			if (j == width - 1)
			{
				cout << wall;
			}
		}
		cout << endl;
	}

	// Create the bottom wall.
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;

	// Draw the score to the screen.
	cout << "Score: " << score << endl;
}

// Checks for user input.
void Input ()
{
	// Check if a key was pressed.
	if (_kbhit())
	{
		// Check the ASCII character that was pressed by retrieving it.
		switch (_getch())
		{
		case 'w':
			currentDirection = UP;
			break;
		case 's':
			currentDirection = DOWN;
			break;
		case 'a':
			currentDirection = LEFT;
			break;
		case 'd':
			currentDirection = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

// Control's the game's logic.
void Logic ()
{
	// Store the coordinates of the last tail piece.
	int previousXOfTail = tailX[0];
	int previousYOfTail = tailY[0];
	// The second previous position of the snake's tail.
	int prev2X, prev2Y;
	// Set the first snake elements coordinates to that of the player's head.
	tailX[0] = playerX;
	tailY[0] = playerY;

	// Iterate through the tail and move it. 
	//(We start from 1 because we have already stored the 0 position of the tail's coordinates.)
	for (int i = 1; i < tailLength; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = previousXOfTail;
		tailY[i] = previousYOfTail;

		previousXOfTail = prev2X;
		previousYOfTail = prev2Y;
	}

	// Switch the movement based on the current direction.
	switch (currentDirection)
	{
	case LEFT:
		playerX--;
		break;
	case RIGHT:
		playerX++;
		break;
	case UP:
		playerY--;
		break;
	case DOWN:
		playerY++;
		break;
	default:
		break;
	}

	// If the player leaves the width of the game.
	if (playerX > width || playerX < 0)
	{
		// End the game.
		gameOver = true;
	}
	// If the player leaves the height of the game.
	else if (playerY > height || playerY < 0)
	{
		// End the game.
		gameOver = true;
	}

	// Loop through every tail piece.
	for (int i = 0; i < tailLength; i++)
	{
		// If the player overlaps a tail coordinate.
		if (playerX == tailX[i] && playerY == tailY[i])
		{
			// End the game.
			gameOver = true;
		}
	}

	// If the player overlaps a fruit piece coordinate.
	if (playerX == fruitX && playerY == fruitY)
	{
		// Increase the game's score.
		score += 10;
		// Spawn a fruit piece at a random point between the width and height of the game.
		fruitX = rand() % width;
		fruitY = rand() % height;
		// Increase the tail length.
		tailLength++;
	}
}

#pragma endregion

#pragma region Game Loop

// Entry point for the console application.
int main()
{
	// Setup the game.
	Setup();

	// Keep running the game whilst it is still in play.
	while (!gameOver)
	{
		// Draw the game to the console window.
		Draw();
		// Read input.
		Input();
		// Execute game logic.
		Logic();
		// Delay execution every 400 miliseconds. (NOTE: Windows only.)
		Sleep(400);
	}

	// Return's false and application closes.
	return 0;
}

#pragma endregion
// TODO: Draw the walls, score and fruit piece once and then redraw the player continuously.

