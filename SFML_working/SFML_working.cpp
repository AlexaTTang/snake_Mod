// SFML_working.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SFML/Graphics.hpp> //using namepsace sf
#include <time.h>

//globals dimensions for window
int num_vertBox = 30, num_horiBox = 20;
int size = 16; //numer of pixels
int w = size * num_horiBox;//background number of pixels  in width
int h = size * num_vertBox;//background number of pixels in height

//create the snake
int direction; //direction the snake is moving

//*******************************************
//*******************************************
int direction2; //direction snake 2 is moving
//*******************************************
//*******************************************

int snake_length = 4;

//*************************************
//*************************************
/*SNAKE 2*/
int snake2_length = 4;
//*************************************
//*************************************

//*************************************
//*************************************
/*MOVED FROM MAIN*/
float timer = 0.0f, delay = 0.1f;
//*************************************
//*************************************

//snake is a collection of sprites
struct snake
{
	int x, y; //each sprite of snake needs an x,y coordinate

} s[100];//Maximum snake size

//***********************************
//***********************************
/*ADDED SECOND SNAKE*/
struct snake2
{
	int x, y; //each sprite of snake needs an x,y coordinate

} s2[100];
//***********************************
//***********************************


//fruit that the snake will eat
struct fruit
{
	int x, y; //only need one sprite needed for one food item
}food;


//updating as snake moves
//move snake head based on user input and body by incrementing 
//forward by iterating through arrays previous position
void move()
{
	//1st update body so everything updates in proper order
	//move the body only!  s[0] = head will not be changed here
	for (int i = snake_length; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	//second update the head
	//head of the snake, s[0] depends on direction user inputs
	//if user presses up
	if (direction == 0)
	{
		s[0].y -= 1;
	}
	//if user presses down
	if (direction == 1)
	{
		s[0].y += 1;
	}
	//if user presses left
	if (direction == 2)
	{
		s[0].x -= 1;
	}
	//if user presses right
	if (direction == 3)
	{
		s[0].x += 1;
	}

	//***NEW*** If Snake eats food it should grow
//check if snake head = food location
	if (((s[0].x) == food.x) && ((s[0].y) == food.y))
	{
		//increment snake
		snake_length++;

		//Randomly place food somewhere else
		food.x = rand() % num_horiBox;
		food.y = rand() % num_vertBox;
	}


	//***NEW*** Boundary Checking snake as is hits screen end
	//loop snake back on other side
	//LEFT and RIGHT
	if (s[0].x > num_horiBox)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = num_horiBox;
	//TOP and BOTTOM
	if (s[0].y > num_vertBox)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].y = num_vertBox;

	//***NEW*** Check if you eat body of snake
	for (int i = 1; i < snake_length; i++)
	{
		//Cut Snake body from place eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			snake_length = i;
	}
}



//updating as snake2 moves
//move snake head based on user input and body by incrementing 
//forward by iterating through arrays previous position
void move2()
{
	//1st update body so everything updates in proper order
	//move the body only!  s[0] = head will not be changed here
	for (int i = snake2_length; i > 0; --i)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}
	//second update the head
	//head of the snake, s[0] depends on direction user inputs
	//if user presses up
	if (direction2 == 0)
	{
		s2[0].y -= 1;
	}
	//if user presses down
	if (direction2 == 1)
	{
		s2[0].y += 1;
	}
	//if user presses left
	if (direction2 == 2)
	{
		s2[0].x -= 1;
	}
	//if user presses right
	if (direction2 == 3)
	{
		s2[0].x += 1;
	}

	//***NEW*** If Snake eats food it should grow
//check if snake head = food location
	if (((s2[0].x) == food.x) && ((s2[0].y) == food.y))
	{
		//increment snake
		snake2_length++;

		//Randomly place food somewhere else
		food.x = rand() % num_horiBox;
		food.y = rand() % num_vertBox;
	}


	//***NEW*** Boundary Checking snake as is hits screen end
	//loop snake back on other side
	//LEFT and RIGHT
	if (s2[0].x > num_horiBox)
		s2[0].x = 0;
	if (s2[0].x < 0)
		s2[0].x = num_horiBox;
	//TOP and BOTTOM
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;
	if (s2[0].y < 0)
		s2[0].y = num_vertBox;

	//***NEW*** Check if you eat body of snake
	for (int i = 1; i < snake2_length; i++)
	{
		//Cut Snake body from place eaten
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y)
			snake2_length = i;
	}
}




int main()
{
	//setting pseudorandom time
	srand(time(0));

	//Window that we can play the game in
	sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

	//Textures load an image into the GPU
	sf::Texture t1, t2, t3, t4;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	//***********************************
	//***********************************
	/*ADDED T4*/
	//***********************************
	//***********************************
	t4.loadFromFile("images/apple.png");

	//Sprite has physical dimensions
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	//***********************************
	//***********************************
	/*ADDED SPRITE4*/
	//***********************************
	//***********************************
	sf::Sprite sprite4(t4);

	//***NEW*** initially place food somewhere on screen
	food.x = 10;
	food.y = 10;

	sf::Clock clock;

	/*float timer = 0.0f, delay = 0.01f;*/
	//frame rate
	while (window.isOpen())
	{
		//placed inside while loop to update timer
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//allow us to check when a user does something
		sf::Event e;

		//check when the window is closed
		while (window.pollEvent(e))
		{
			//if user presses  in the top right (Windows) close the window
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//control for Snake by user
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;

		//*************************************************************************
		//*************************************************************************
		//control for Snake2 by second player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction2 = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) direction2 = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction2 = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction2 = 3;
		//*************************************************************************
		//*************************************************************************


		if (timer > delay)
		{
			timer = 0; //reset timer
			move(); //move snake one forward
			move2();
		}

		//*************************************************************************************************************
		//*************************************************************************************************************
		/*increasing speed of game*/
		if (((((s[0].x) == food.x) && ((s[0].y) == food.y))) || ((((s2[0].x) == food.x) && ((s2[0].y) == food.y))))
		{
			delay = delay - 0.01;
		}
		//*************************************************************************************************************
		//*************************************************************************************************************

		//Draw in window
		window.clear(); //clear the window so new frame can be drawn in 

		//NOTE: Order matters as we will draw over items listed first. 
		//Hence the background should be the first thing you will always do
		//first draw background
		for (int i = 0; i < num_horiBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				//set position of sprite1 on at a time
				sprite1.setPosition(i*size, j*size);
				//draw sprite1 but do not show on screen
				window.draw(sprite1);
			}
		}

		//second draw the snake otherwise background will be drawn over snake
		for (int i = 0; i < snake_length; i++)
		{
			//position sprite2 one at a time
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			//draw sprite2 one at a time by drawing over background
			window.draw(sprite2);
		}

		//*************************************************************************************************************
		//*************************************************************************************************************
		/*DRAW SNAKE 2*/
		for (int j = 0; j < snake_length; j++)
		{
			//position sprite2 one at a time
			sprite3.setPosition(s2[j].x*size, s2[j].y*size);
			//draw sprite2 one at a time by drawing over background
			window.draw(sprite3);
		}
		//*************************************************************************************************************
		//*************************************************************************************************************

		//***NEW*** 3rd: Draw Fruit
		/*sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);*/

		//***********************************
		//***********************************
		/*CHANGED IMAGE FOR FRUIT*/
		//***********************************
		//***********************************
		sprite4.setPosition(food.x*size, food.y*size);
		window.draw(sprite4);



		//Show everything we have drawn on the screen
		window.display();
	}
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
