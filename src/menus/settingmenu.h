#pragma once

#include <stdint.h>
#include "../charmath.h"
#include "../namespace/stg.h"

void namesel(const uint8_t &, stg::PlayerSetting &);

void colorsel(const uint8_t &, stg::PlayerSetting &);

void keysel(const Direction &, const uint8_t &, stg::PlayerSetting &);

void playersel(const uint8_t, stg::PlayerSetting *);

void settingmenu(stg::PlayerSetting *);