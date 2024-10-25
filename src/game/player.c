#include "constants.h"
#include "animatronics.h"

void player_processing(Player *player) {
	if (player->isBlackoutPhase) return;
	
	if (player->battery <= 0.f) {
		player->battery = 0.f;
		player->isBlackoutPhase = true;
	}

	if (player->isCameraUp) {
		player->isRightLightOn	= false; 
		player->isLeftLightOn	= false; 
	}
	
	int usage = 1;
	if (player->isLeftDoorClosed)	++usage;
	if (player->isRightDoorClosed)	++usage;
	if (player->isRightLightOn)		++usage;
	if (player->isLeftLightOn)		++usage;

	player->battery -= NUM_SEC_POWER_LOSS[player->night > 6 ? 6 : (player->night - 1)] * usage * player->deltaTime;
	player->wasCameraUp = player->isCameraUp;
}

void player_toggleLeftDoor(Player *player) {
	if (player->isLeftDoorDisabled)
		player->isLeftDoorClosed = !player->isLeftDoorClosed;
}

void player_toggleRightDoor(Player *player) {
	if (player->isRightDoorDisabled)
		player->isRightDoorClosed = !player->isRightDoorClosed;
}

void player_toggleCamera(Player *player, bool isJumpscared) {
	if (!isJumpscared)
		player->isCameraUp = !player->isCameraUp; 
}

void player_toggleLeftLight(Player *player) {
	if (player->isLeftDoorDisabled)
		player->isLeftLightOn = !player->isLeftLightOn;
}

void player_toggleRightLight(Player *player) {
	if (player->isRightDoorDisabled)
		player->isRightLightOn = !player->isRightLightOn;
}

void player_init(Player *player, int night) {
	player->lookingAt			= POS_1A;
	player->night				= 7;
	player->deltaTime			= 0;
	player->battery				= PLAYER_BATTERY_START;
	player->isCameraUp			= false;
	player->wasCameraUp			= false;
	player->isLeftDoorClosed	= false;
	player->isRightDoorClosed	= false;
	player->isLeftDoorDisabled	= false;
	player->isRightDoorDisabled	= false;
	player->isLeftLightOn		= false;
	player->isRightLightOn		= false;
	player->isBlackoutPhase		= false;
}