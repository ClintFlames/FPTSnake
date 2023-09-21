#pragma once

#include <cstdint>
#include "../namespace/stg.h"

void begingame(stg::FavMode, stg::PlayerSetting *);

stg::FavMode selectwallmode(stg::PlayerSetting *, stg::GameMode, bool t);

stg::FavMode selectgamemode(stg::PlayerSetting *, bool t);

void sgsetupfavmode(stg::PlayerSetting *);

uint8_t sgloop(uint8_t);

void selectgame(stg::PlayerSetting *);