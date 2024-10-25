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

	player->battery -= NUM_SEC_POWER_LOSS[player->night > 7 ? 7 : player->night] * usage * player->deltaTime;
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