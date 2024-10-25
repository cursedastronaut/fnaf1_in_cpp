#include "constants.h"
#include "animatronics.h"
void freddy_processing(Player *player, Freddy *freddy) {
	if (freddy->ai == 0) return;

	freddy->timer += player->deltaTime;

	if (freddy->timer > MOVEMENT_OPPORTUNITY_TIMES[FREDDY]) {
		freddy->timer = 0.f;
		if (
				!freddy->startCountDown &&
				(randB(0, AI_MAX) >= AI_MAX - freddy->ai) &&
				((freddy->position != POS_4B && !player->isCameraUp) || (freddy->position == POS_4B && player->lookingAt != POS_4B))
			) {
			freddy->startCountDown = true;
			freddy->countDown = FREDDY_MOVEMENT_COUNTDOWN[0] - FREDDY_MOVEMENT_COUNTDOWN[1] * freddy->ai; 
		}
	}

	if (freddy->startCountDown) {
		if (freddy->countDown < 0) {
			if ((freddy->position != POS_4B && !player->isCameraUp) || (freddy->position == POS_4B && player->lookingAt != POS_4B))
			{
				freddy->canMove = true;
				freddy->startCountDown = false;
			}
		} else {
			freddy->countDown -= player->deltaTime;
		}
	}

	if (freddy->canMove) {
		switch (freddy->position)
		{
			case POS_RD:
				if (!player->isRightDoorClosed)
					freddy->position = POS_OFFICE;
				else
					freddy->position = POS_4B;
				break;

			case POS_4B:
				freddy->position = POS_RD;
				break;

			case POS_4A:
				freddy->position = POS_4B;
				break;

			case POS_6:
				freddy->position = POS_4A;
				break;

			case POS_7:
				freddy->position = POS_6;
				break;

			case POS_1B:
				freddy->position = POS_7;
				break;

			case POS_1A:
				freddy->position = POS_1B;
				break;
			
			default:
				break;
		}
	}

	if (freddy->position == POS_OFFICE && !player->isCameraUp) {
		if (randB(0, 4) == 1) {
			freddy->shouldPerformJumpscare = true;
		}
	}
}

void freddy_init(Freddy *freddy, int ai) {
	freddy->canMove			= false;
	freddy->startCountDown	= false;
	freddy->countDown		= 0.f;
	freddy->timer			= 0.f;
	freddy->ai				= ai;
	freddy->position		= POS_1A;
	freddy->shouldPerformJumpscare = false;

	freddy->bl_hasShowedUp		= false;
	freddy->bl_hasMusicStarted	= false;
	freddy->bl_hasBlacketOut	= false;
	freddy->bl_showUpFails		= 0;
	freddy->bl_BLFails			= 0;
	freddy->bl_JSFails			= 0;
}

void freddy_blackout_sequence(Player *player, Freddy *freddy) {
	//Timer must have been reset before first execution
	freddy->timer += player->deltaTime;
	
	if (!freddy->bl_hasShowedUp) {
		if (freddy->timer > FREDDY_BLACKOUT_SHOWUP[0] * (freddy->bl_showUpFails + 1)) {

			if (
				freddy->timer > FREDDY_BLACKOUT_SHOWUP[1]
				|| randB(FREDDY_BLACKOUT_SHOWUP_CHANCES[0], FREDDY_BLACKOUT_SHOWUP_CHANCES[1]) == 1
			) {
				freddy->bl_hasShowedUp = true;
			} else {
				++freddy->bl_showUpFails;
			}
		}
		return;
	}
	

	if (!freddy->bl_hasBlacketOut) {
		if (freddy->timer > FREDDY_BLACKOUT_SHOWUP[0] * (freddy->bl_BLFails + 1)) {

			if (
				freddy->timer > FREDDY_BLACKOUT_SHOWUP[1]
				|| randB(FREDDY_BLACKOUT_SHOWUP_CHANCES[0], FREDDY_BLACKOUT_SHOWUP_CHANCES[1]) == 1
			) {
				freddy->bl_hasBlacketOut = true;
			} else {
				++freddy->bl_BLFails;
			}
		}
		
		return;
	}

	if (!freddy->bl_hasBlacketOut) {
		if (freddy->timer > FREDDY_BLACKOUT_JP_TIMER[0] * (freddy->bl_JSFails + 1)) {

			if (
				freddy->timer > FREDDY_BLACKOUT_JP_TIMER[1]
				|| randB(FREDDY_BLACKOUT_JP_CHANCES[0], FREDDY_BLACKOUT_JP_CHANCES[1]) == 1
			) {
				freddy->shouldPerformJumpscare = true;
			} else {
				++freddy->bl_JSFails;
			}
		}
		
		return;
	}
}