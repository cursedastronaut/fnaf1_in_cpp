#pragma once
#define bool short int
#include <stdlib.h>
#include <stdbool.h>
#define max(x,y) (((x) >= (y)) ? (x) : (y))
#define min(x,y) (((x) <= (y)) ? (x) : (y))

int randB(unsigned int min, unsigned int max);

void freddy_processing(Player *player, Freddy *freddy);
void bonnie_processing(Player *player, BonChi *bonnie);
void chica_processing(Player *player, BonChi *chica);
void foxy_processing(Player *player, Foxy *foxy);

void freddy_init(Freddy *freddy, int ai);
void foxy_init(Foxy *foxy, int ai);
void bonnie_init(BonChi *bonnie, int ai);

void freddy_blackout_sequence(Player *player, Freddy *freddy);

typedef struct Player {
	bool isCameraUp;
	bool wasCameraUp;
	int lookingAt;
	float deltaTime;
	float battery;
	bool isLeftDoorClosed;
	bool isRightDoorClosed;
	bool isLeftDoorDisabled;
	bool isRightDoorDisabled;
} Player;

typedef struct Freddy
{
	bool canMove;
	bool startCountDown;
	float countDown;
	float timer;
	int ai;
	int position;
	bool shouldPerformJumpscare;

	//blackout sequence
	bool bl_hasShowedUp;
	bool bl_hasMusicStarted;
	bool bl_hasBlacketOut;
	int bl_showUpFails;
	int bl_BLFails;
	int bl_JSFails;
} Freddy;

typedef struct Foxy
{
	bool hasMovementOpportunity;
	float timer;
	float lockedCooldown;
	float attackTimer;
	bool isLocked;
	int ai;
	int stage;
	bool shouldPerformJumpscare;
	bool isRunning;
	int timesBlocked;
} Foxy;

typedef struct BonChi {
	bool hasMovementOpportunity;
	bool shouldPerformJumpscare;
	float timer;
	int position;
	int ai;
	bool prepareForJumpscare;

} BonChi;
