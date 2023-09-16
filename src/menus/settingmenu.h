#pragma once

#include <stdint.h>
#include "../charmath.h"

void namesel(const uint8_t &, PlayerSetting &);

void colorsel(const uint8_t &, PlayerSetting &);

void keysel(const Direction &, const uint8_t &, PlayerSetting &);

void playersel(const uint8_t, PlayerSetting *);

void settingmenu(PlayerSetting *);