#include "constants.h"
#include "animatronics.h"

void bonnie_init(BonChi *bonnie, int ai) {
	bonnie->hasMovementOpportunity	= false;
	bonnie->shouldPerformJumpscare	= false;
	bonnie->prepareForJumpscare		= false;
	bonnie->timer					= 0.0f;
	bonnie->position				= POS_1A;
	bonnie->ai						= ai;
}

void bonnie_processing(Player *player, BonChi *bonnie) {
	if (bonnie->ai == 0) return;
	
	bonnie->timer += player->deltaTime;
	if ( !bonnie->prepareForJumpscare &&
		bonnie->timer > MOVEMENT_OPPORTUNITY_TIMES[BONNIE] &&
		randB(0, AI_MAX) <= bonnie->ai
	) {
		switch (bonnie->position)
		{
			case POS_1A:
				if (randB(0, 2) == 1) {
					bonnie->position = POS_5;
				} else {
					bonnie->position = POS_1B;
				}
				break;

			case POS_1B:
				if (randB(0, 2) == 1) {
					bonnie->position = POS_5;
				} else {
					bonnie->position = POS_2A;
				}
				break;
			
			case POS_5:
				bonnie->position = POS_2A;
				break;

			case POS_2A:
				if (randB(0, 2) == 1) {
					bonnie->position = POS_3;
				} else {
					bonnie->position = POS_2B;
				}
				break;

			case POS_3:
				if (randB(0, 2) == 1) {
					bonnie->position = POS_5;
				} else {
					bonnie->position = POS_OFFICE;
				}
				break;

			case POS_2B:
				if (randB(0, 2) == 1) {
					bonnie->position = POS_3;
				} else {
					bonnie->position = POS_OFFICE;
				}

			case POS_OFFICE:
				if (player->isLeftDoorClosed) {
					bonnie->position = POS_1B;

				} else {
					player->isLeftDoorDisabled = true;
					bonnie->prepareForJumpscare;
					bonnie->timer = false;
				}

			default:
				break;
		}
	}

	if (bonnie->prepareForJumpscare &&
		(
			player->wasCameraUp != player->isCameraUp ||
			bonnie->timer > BONCHI_FORCE_CAMERA_ATTACK_TIMER
		)
	) {
			bonnie->shouldPerformJumpscare = true;
	}
}
