#include "constants.h"
#include "animatronics.h"
void Update(Player *player, Freddy *freddy, Foxy *foxy, BonChi *bonnie, BonChi *chica) {
	if (player->deltaTime < RUNNING_TPS) return;
	freddy_processing(player, freddy);
	bonnie_processing(player, bonnie);
	foxy_processing(player, foxy);
	player_processing(player);
}

int randB(unsigned int min, unsigned int max) {
	return (rand() * (max - min + 1) + min);
}