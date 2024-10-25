// constants.c
#include "constants.h"

const int NIGHT[NIGHT_COUNT][ANIMATRONIC_COUNT] = {
    {0, 0, 0, 0},
    {0, 3, 1, 1},
    {1, 0, 5, 2},
    {-2, 2, 4, 6},
    {3, 5, 7, 5},
    {4, 10, 12, 16}
};

const int AI_INCREASE[HOURS_COUNT][ANIMATRONIC_COUNT] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 1, 1},
    {0, 0, 0, 0}
};

const int NUM_SEC_POWER_LOSS[NIGHT_COUNT] = {5, 6, 4, 3, 3, 3};
const float MOVEMENT_OPPORTUNITY_TIMES[ANIMATRONIC_COUNT] = {3.02f, 4.97f, 4.98f, 5.01f};
const float FOXY_CAMERA_LOCK_COOLDOWN[2] = {0.83f, 16.67f};
const float FOXY_ATTACK_TIMER = 25.f;
const float FOXY_BATTERY_STEAL[3] = {1.f, 6.f, 11.f};
const float FOXY_ATTACK_DURATION = 3.0f;
const float FREDDY_MOVEMENT_COUNTDOWN[2] = {1000.f, 100.f};
const float FREDDY_BLACKOUT_SHOWUP[2] = {5.f, 20.f};
const float FREDDY_BLACKOUT_JP_TIMER[2] = {2.f, 20.f};
const int FREDDY_BLACKOUT_SHOWUP_CHANCES[2] = {0, 4};
const int FREDDY_BLACKOUT_JP_CHANCES[2] = {0, 5};
const float BONCHI_FORCE_CAMERA_ATTACK_TIMER = 30.f;
const float PLAYER_BATTERY_START = 100.f;

const int AI_MAX;
const int RUNNING_TPS;