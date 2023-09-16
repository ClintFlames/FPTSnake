#pragma once

#include <stdint.h>
#include <string>

struct Point { uint8_t x; uint8_t y; };

struct Size { uint8_t w; uint8_t h; };

enum Direction : uint8_t { Up, Down, Right, Left };

struct PlayerSetting {
	uint8_t color;
	std::wstring name;
	int keyup;
	int keydown;
	int keyright;
	int keyleft;
};