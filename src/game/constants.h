// constants.h
#pragma once

#define ANIMATRONIC_COUNT 4
#define NIGHT_COUNT 6
#define HOURS_COUNT 6

extern const int AI_MAX;
extern const int RUNNING_TPS;

extern const int NIGHT[NIGHT_COUNT][ANIMATRONIC_COUNT];
extern const int AI_INCREASE[HOURS_COUNT][ANIMATRONIC_COUNT];
extern const int NUM_SEC_POWER_LOSS[NIGHT_COUNT];
extern const float MOVEMENT_OPPORTUNITY_TIMES[ANIMATRONIC_COUNT];
extern const float FOXY_CAMERA_LOCK_COOLDOWN[2];
extern const float FOXY_ATTACK_TIMER;
extern const float FOXY_BATTERY_STEAL[3];
extern const float FOXY_ATTACK_DURATION;
extern const float FREDDY_MOVEMENT_COUNTDOWN[2];
extern const float FREDDY_BLACKOUT_SHOWUP[2];
extern const float FREDDY_BLACKOUT_JP_TIMER[2];
extern const int FREDDY_BLACKOUT_SHOWUP_CHANCES[2];
extern const int FREDDY_BLACKOUT_JP_CHANCES[2];
extern const float BONCHI_FORCE_CAMERA_ATTACK_TIMER;
extern const float PLAYER_BATTERY_START;

enum ANIMATRONICS {
    FREDDY, BONNIE, CHICA, FOXY
};

enum POSITIONS {
    POS_1A, POS_1B, POS_1C, POS_2A, POS_2B, POS_3,
    POS_4A, POS_4B, POS_5, POS_6, POS_7, POS_RD, POS_LD, POS_OFFICE
};