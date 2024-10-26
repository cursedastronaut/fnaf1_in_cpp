#include "constants.h"
#include "animatronics.h"

void foxy_init(Foxy *foxy, int ai) {
	foxy->ai						= ai;
	foxy->hasMovementOpportunity	= false;
	foxy->isLocked					= false;
	foxy->shouldPerformJumpscare	= false;
	foxy->isRunning					= false;
	foxy->timer						= 0.0f;
	foxy->lockedCooldown			= 0.0f;
	foxy->attackTimer				= 0.0f;
	foxy->stage						= 0;
	foxy->timesBlocked				= 0;
}

void foxy_attack(Player *player, Foxy *foxy) {
	if (!player->isLeftDoorClosed) {
		foxy->shouldPerformJumpscare = true;
	} else {
		player->battery -= FOXY_BATTERY_STEAL[my_min(foxy->timesBlocked, 3)];
		foxy->stage = randB(0, 2);
	}
}

void foxy_LastStage(Player *player, Foxy *foxy) {
	if (!foxy->isRunning && foxy->stage == 3) {
		if (player->lookingAt == POS_2A) {
			foxy->isRunning = true;
			foxy->attackTimer = 0.0f;
		} else if (foxy->timer > FOXY_ATTACK_TIMER) {
			foxy_attack(player, foxy);
		}
	}

	if (foxy->isRunning) {
		foxy->attackTimer += player->deltaTime;
		if (foxy->attackTimer > FOXY_ATTACK_DURATION) {
			foxy_attack(player, foxy);
		}
	}
}

void foxy_processing(Player *player, Foxy *foxy) {
	if (foxy->ai == 0)	{
		return;
	}
	
	if (player->isCameraUp) {
		foxy->isLocked = true;
		foxy->lockedCooldown = 0.f;
	}
	
	if (foxy->isLocked && !player->isCameraUp) {
		foxy->lockedCooldown -= player->deltaTime;
		if (foxy->lockedCooldown > FOXY_CAMERA_LOCK_COOLDOWN[1] ||
			(
				foxy->lockedCooldown > FOXY_CAMERA_LOCK_COOLDOWN[0]
				&& randB(0, 2) == 1
			)
		) {
			foxy->isLocked = false;
			foxy->lockedCooldown = 0.f;
		}
	}

	foxy->timer += player->deltaTime;
	if (foxy->timer > MOVEMENT_OPPORTUNITY_TIMES[FOXY] && foxy->stage != 3) {
		foxy->timer = 0.f;
		if (randB(0, AI_MAX) <= foxy->ai) {
			foxy->hasMovementOpportunity = true;
		}
	}

	if (foxy->hasMovementOpportunity) {
		foxy->hasMovementOpportunity = false;
		++foxy->stage;
	}

	foxy_LastStage(player, foxy);
}