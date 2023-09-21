#pragma once

#include <stdint.h>
#include <string>
#include <filesystem>



namespace stg {
	struct PlayerSetting {
		uint8_t color;
		std::wstring name;
		int keyup;
		int keydown;
		int keyright;
		int keyleft;
	};

	extern uint8_t favmode;
	extern std::string path;
	extern uint16_t sign;

	enum GameMode : bool { Standart, Effect };
	enum WallMode : uint8_t { Box, RandomBox, Void, RandomVoid };

	struct FavMode { GameMode gamemode; WallMode wallmode; };

	std::wstring wsfavmode(const stg::FavMode &);

	void initdef(stg::PlayerSetting *);

	bool exists();

	bool load(stg::PlayerSetting *);

	void save(stg::PlayerSetting *);

	FavMode getfavmode(const uint8_t &);

	void setfavmode(const uint8_t &, const FavMode &);
}