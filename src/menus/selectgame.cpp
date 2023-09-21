#include "selectgame.h"

#include <string>
#include "../namespace/stg.h"
#include "../namespace/ui.h"



void begingame(stg::FavMode fm, stg::PlayerSetting * ps) {
	// Here it all begins
}

stg::FavMode selectwallmode(stg::PlayerSetting * ps, stg::GameMode gm, bool t) {
	Point center = ui::center();

	ui::Label select[] = {
		{ COLOR_WHITE  , L"Коробка          ", 1 },
		{ COLOR_WHITE  , L"Рандомная коробка", 1 },
		{ COLOR_MAGENTA, L"Пустота          ", 1 },
		{ COLOR_MAGENTA, L"Рандомная пустота", 0 }
	};

	ui::decotitle(1, COLOR_CYAN, L"Выберите режим стен", 1);

	uint8_t c = ui::ilist(
		{ static_cast<uint8_t>(center.x - 3 - 17 / ui::pxw / 2), static_cast<uint8_t>(center.y - 3) },
		L" [ ",
		L" ] ",
		select,
		4,
		0,
		!t
	);

	erase();

	if (c == 0) return { stg::Standart, stg::Box };

	stg::FavMode fm = { gm, static_cast<stg::WallMode>(c - 1) };

	if (t) return fm;

	begingame(fm, ps);

	return fm;
}

stg::FavMode selectgamemode(stg::PlayerSetting * ps, bool t) {
	Point center = ui::center();

	ui::Label select[] = {
		{ COLOR_WHITE, L"Стандартный", 1 },
		{ COLOR_MAGENTA, L"Эффектный  ", 0 }
	};

	ui::decotitle(1, COLOR_CYAN, L"Выберите режим игры", 1);

	uint8_t c = ui::ilist(
		{ static_cast<uint8_t>(center.x - 3 - 11 / ui::pxw / 2), static_cast<uint8_t>(center.y - 1) },
		L" [ ",
		L" ] ",
		select,
		2,
		0,
		!t
	);

	erase();

	if (c == 0) return { stg::Standart, stg::Box };

	return selectwallmode(ps, c == 1 ? stg::Standart : stg::Effect, t);
}

void sgsetupfavmode(stg::PlayerSetting * ps) {
	while (true) {
		Point center = ui::center();

		std::wstring select_text[] = {
			L"ИР 1: " + stg::wsfavmode(stg::getfavmode(0)),
			L"ИР 2: " + stg::wsfavmode(stg::getfavmode(1))
		};

		uint8_t mlen = select_text[0].length();
		for (uint8_t i = 0; i < 2; i++) if (mlen < select_text[i].length()) mlen = select_text[i].length();
		for (uint8_t i = 0; i < 2; i++) if (mlen > select_text[i].length()) select_text[i] += std::wstring(mlen - select_text[i].length(), L' ');

		ui::Label select[] = {
			{ COLOR_WHITE, select_text[0], 1 },
			{ COLOR_WHITE, select_text[1], 0 }
		};


		ui::decotitle(1, COLOR_CYAN, L"Выберите ИР", 1);

		uint8_t c = ui::ilist(
			{ static_cast<uint8_t>(center.x - 3 - mlen / ui::pxw / 2), static_cast<uint8_t>(center.y - 3) },
			L" [ ",
			L" ] ",
			select,
			2,
			0,
			true
		);

		erase();

		if (c == 0) return;

		stg::setfavmode(
			c - 1,
			selectgamemode(ps, true)
		);

		stg::save(ps);
	}
}

uint8_t sgloop(uint8_t c) {
	Point center = ui::center();

	std::wstring select_text[] = {
		L"Начать игру",
		L"ИР 1: " + stg::wsfavmode(stg::getfavmode(0)),
		L"ИР 2: " + stg::wsfavmode(stg::getfavmode(1)),
		L"Настроить избранные режимы"
	};

	uint8_t mlen = select_text[0].length();
	for (uint8_t i = 0; i < 4; i++) if (mlen < select_text[i].length()) mlen = select_text[i].length();
	for (uint8_t i = 0; i < 4; i++) if (mlen > select_text[i].length()) select_text[i] += std::wstring(mlen - select_text[i].length(), L' ');

	ui::Label select[] = {
		{ COLOR_WHITE , select_text[0], 1 },
		{ COLOR_YELLOW, select_text[1], 1 },
		{ COLOR_YELLOW, select_text[2], 1 },
		{ COLOR_WHITE , select_text[3], 0 }
	};

	ui::decotitle(1, COLOR_CYAN, L"Выберите действие", 1);

	uint8_t sel = ui::ilist(
		{ static_cast<uint8_t>(center.x - 3 - mlen / ui::pxw / 2), static_cast<uint8_t>(center.y - 3) },
		L" [ ",
		L" ] ",
		select,
		4,
		c - 1,
		true
	);

	erase();

	return sel;
}

void selectgame(stg::PlayerSetting * ps) {
	uint8_t c = 1;
	
	while (true) switch (c = sgloop(c)) {
		case 1: selectgamemode(ps, false); break;
		case 2: begingame(stg::getfavmode(0), ps); break;
		case 3: begingame(stg::getfavmode(1), ps); break;
		case 4: sgsetupfavmode(ps); break;
		default: return;
	}
}