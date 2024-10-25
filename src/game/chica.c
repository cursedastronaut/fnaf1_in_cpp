#include "constants.h"
#include "animatronics.h"
void chica_init(BonChi *chica, int ai) {
	chica->hasMovementOpportunity	= false;
	chica->shouldPerformJumpscare	= false;
	chica->prepareForJumpscare		= false;
	chica->timer					= 0.0f;
	chica->position					= POS_1A;
	chica->ai						= ai;
}

void chica_processing(Player *player, BonChi *chica) {
	if (chica->ai == 0) return;
	
	chica->timer += player->deltaTime;
	if ( !chica->prepareForJumpscare &&
		chica->timer > MOVEMENT_OPPORTUNITY_TIMES[CHICA] &&
		randB(0, AI_MAX) <= chica->ai
	) {
		switch (chica->position)
		{
			case POS_1A:
				chica->position = POS_1B;
				break;

			case POS_1B:
				if (randB(0, 2) == 1) {
					chica->position = POS_7;
				} else {
					chica->position = POS_6;
				}
				break;
			
			case POS_4A:
				if (randB(0, 2) == 1) {
					chica->position = POS_4B;
				} else {
					chica->position = POS_1B;
				}
				break;

			case POS_7:
				if (randB(0, 2) == 1) {
					chica->position = POS_4A;
				} else {
					chica->position = POS_6;
				}
				break;

			case POS_6:
				chica->position = POS_4A;
				break;

			case POS_4B:
				chica->position = POS_OFFICE;
				break;

			case POS_OFFICE:
				if (player->isRightDoorClosed) {
					chica->position = POS_4A;
				} else {
					player->isRightDoorDisabled = true;
					chica->prepareForJumpscare;
					chica->timer = 0.f;
				}
				break;
			default:
				break;
		}
	}

	if (chica->prepareForJumpscare &&
		(
			player->wasCameraUp != player->isCameraUp ||
			chica->timer > BONCHI_FORCE_CAMERA_ATTACK_TIMER
		)
	) {
			chica->shouldPerformJumpscare = true;
	}
}