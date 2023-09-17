#pragma once

#include <stdint.h>
#include <string>

namespace stg {
	struct PlayerSetting {
		uint8_t color;
		std::wstring name;
		int keyup;
		int keydown;
		int keyright;
		int keyleft;
	};

	void initdef(stg::PlayerSetting *);

	void load(stg::PlayerSetting *);

	void save(stg::PlayerSetting *);
}