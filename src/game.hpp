#pragma once
#include "game/animatronics.h"
#include "displaying.hpp"

class Game
{
private:
	Player	player;
	BonChi	bonnie;
	Freddy	freddy;
	Foxy	foxy;
	BonChi	chica;

	Displaying dis;

	int night;
	bool isCustomNight = false;
	void Init();
	uint8_t scenes = 0;

	void mainMenu();
	void inGame();
public:
	Game(/* args */);
	~Game();
	void Main();
};


