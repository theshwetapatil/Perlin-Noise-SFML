// main.cpp : Defines the entry point for the windows application.
// Generative System: Perlin Noise
// Used in Games: FPS, RPG, Platformers, MOBA
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#include "TileMap.h"

#define ROWS 32
#define COLS 32
#define TILENUM 32*32

int myMap[ROWS][COLS];
int trans[TILENUM];
noise::module::Perlin myModule;

sf::RenderWindow window(sf::VideoMode(500, 500), "Perlin Noise!");

int mapping(double value)
{
	if (value < -.2)	//water
		return 23;
	if (value >= -.2 && value < 0)	//sand
		return 20;
	if (value >= 0 && value < .4)	//grassland
		return 17;
	if (value >= .4 && value < .6)	//hills
		return 177;
	if (value >= .6 && value < .8)	//bigger hills
		return 180;
	if (value >= .8)	//mountains
		return 183;
}

void update_state(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		myModule.SetSeed(myModule.GetSeed() + 1);
	int u = 0;
}

void render_frame()
{
	window.clear();

	int hh = 10;
	for (int i = 0; i < ROWS; i = i + 2)
	{
		for (int j = 0; j < COLS; j = j + 2)
		{
			myMap[i][j] = mapping(myModule.GetValue((double)(i) / 16., (double)(j) / 16., .5));
		}
	}

	int gg = 10;
	for (int i = 1; i < ROWS; i = i + 2)
	{
		for (int j = 1; j < COLS; j = j + 2)
		{
			myMap[i][j] = mapping(myModule.GetValue((double)(i) / 16., (double)(j) / 16., .5));
		}
	}

	int h = 10;
	//Check space in-between two terrains and fill the gap
	int g = 0;
	for (int i = 0; i < ROWS; i = i + 2)
	{
		for (int j = 1; j <= COLS - 1; j = j + 2)
		{
			if (myMap[i][j - 1] != myMap[i][j + 1])	//adjecent terrains are not the same
			{
				if (myMap[i][j - 1] == 23)	// Left terrain is water
				{
					switch (myMap[i][j + 1])
					{
					case 20: myMap[i][j] = 20;		//water->sand
						break;
					case 17: myMap[i][j] = 30;		//water->grassland
						break;
					case 177: myMap[i][j] = 177;	//water->hills
						break;
					case 180: myMap[i][j] = 180;	//water->bigger hills
						break;
					case 183: myMap[i][j] = 183;	//water->mountains
						break;
					}
				}
				else
				if (myMap[i][j - 1] == 20)	// Left terrain is sand
				{
					switch (myMap[i][j + 1])
					{
						case 23: myMap[i][j] = 23;		//sand->water
							break;
						case 17: myMap[i][j] = 27;		//sand->grassland
							break;
						case 177: myMap[i][j] = 177;	//sand->hills
							break;
						case 180: myMap[i][j] = 180;	//sand->bigger hills
							break;
						case 183: myMap[i][j] = 183;	//sand->mountains
							break;
					}
				}
				else
				if (myMap[i][j - 1] == 17)	// Left terrain is grassland
				{
					switch (myMap[i][j + 1])
					{
						case 20: myMap[i][j] = 25;		//grassland->sand
							break;
						case 23: myMap[i][j] = 28;		//grassland->water
							break;
						case 177: myMap[i][j] = 177;	//grassland->hills
							break;
						case 180: myMap[i][j] = 180;		//grassland->bigger hills
							break;
						case 183: myMap[i][j] = 183;		//grassland->mountains
							break;
					}
				}
				else
				if (myMap[i][j - 1] == 177)	// Left terrain is hills
				{
					myMap[i][j] = 177;		//hills->any terrain
				}
				else
				if (myMap[i][j - 1] == 180)	// Left terrain is bigger hills
				{
					myMap[i][j] = 180;		//hills->any terrain
				}
				else
				if (myMap[i][j - 1] == 183)	// Left terrain is mountains
				{
					myMap[i][j] = 183;		//mountains->any terrain
				}
			}
			else
			{
				myMap[i][j] = myMap[i][j + 1];
			}
		}
	}

	int p = 0;
	for (int i = 1; i <= ROWS - 1; i = i + 2)
	{
		for (int j = 0; j < COLS; j = j + 2)
		{
			if (myMap[i - 1][j] != myMap[i + 1][j])	//adjecent terrains are not the same (in column)
			{
				if (myMap[i - 1][j] == 23)	// Top terrain is water
				{
					switch (myMap[i + 1][j])
					{
						case 20: myMap[i][j] = 20;		//water->sand
							break;
						case 17: myMap[i][j] = 45;		//water->grassland
							break;
						case 177: myMap[i][j] = 177;	//water->hills
							break;
						case 180: myMap[i][j] = 180;	//water->bigger hills
							break;
						case 183: myMap[i][j] = 183;	//water->mountains
							break;
					}

				}
				else
				if (myMap[i - 1][j] == 20)	// Top terrain is sand
				{
					switch (myMap[i + 1][j])
					{
						case 23: myMap[i][j] = 23;		//sand->water
							break;
						case 17: myMap[i][j] = 42;		//sand->grassland
							break;
						case 177: myMap[i][j] = 177;	//sand->hills
							break;
						case 180: myMap[i][j] = 180;	//sand->bigger hills
							break;
						case 183: myMap[i][j] = 183;	//sand->mountains
							break;
					}
				}
				else
				if (myMap[i - 1][j] == 17)	// Top terrain is grassland
				{
					switch (myMap[i + 1][j])
					{
						case 20: myMap[i][j] = 10;		//grassland->sand
							break;
						case 23: myMap[i][j] = 13;		//grassland->water
							break;
						case 177: myMap[i][j] = 177;	//grassland->hills
							break;
						case 180: myMap[i][j] = 180;		//grassland->bigger hills
							break;
						case 183: myMap[i][j] = 183;		//grassland->mountains
							break;
					}
				}
				else
				if (myMap[i - 1][j] == 177)	// Top terrain is hills
				{
					myMap[i][j] = 177;		//hills->any terrain
				}
				else
				if (myMap[i - 1][j] == 180)	// Top terrain is bigger hills
				{
					myMap[i][j] = 180;		//hills->any terrain
				}
				else
				if (myMap[i - 1][j] == 183)	// Top terrain is mountains
				{
					myMap[i][j] = 183;		//mountains->any terrain
				}
			}
			else
			{
				myMap[i][j] = myMap[i + 1][j];
			}
		}
	}

	//Render integer array into visual representation on screen
	int k = 0;

	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			{
				trans[k] = myMap[j][i];
				k++;
			}
		}
	}

	for (int k = 0; k < TILENUM; k++)
	{
		if (trans[k] == 0)
			trans[k] = 29;
	}

	if (!map.load("tileset.png", sf::Vector2u(16, 16), trans, ROWS, COLS))
		std::cout << -1;
}

TileMap map;

int main()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();

		window.clear();

		update_state(dt);
		render_frame();

		window.draw(map);
		window.display();
	}

	return 0;
}




