#include "settingmenu.h"

#include <ncurses.h>
#include <cstdio>
#include <string>
#include <cstring>
#include "../namespace/ui.h"
#include "../namespace/stg.h"

void namesel(const uint8_t & vpid, stg::PlayerSetting & ps) {
	Point center = ui::center();

	ui::decotitle(1, COLOR_CYAN, L"Настройки | Имя | Игрок " + std::to_wstring(vpid), 69);

	ui::decotitle(ui::size().h - 2, COLOR_YELLOW, L"Длинна: 2 - 17 символов", 1);

	std::wstring nname = ui::itextinput(
		{ static_cast<uint8_t>(center.x - 8 / ui::pxw), center.y },
		ps.name,
		2,
		17,
		true
	);

	ps.name = nname;

	erase();
}

void colorsel(const uint8_t & vpid, stg::PlayerSetting & ps) {
	Point center = ui::center();

	uint8_t c = 0;
	switch (ps.color) {
		case COLOR_RED    : c = 0; break;
		case COLOR_GREEN  : c = 1; break;
		case COLOR_BLUE   : c = 2; break;
		case COLOR_MAGENTA: c = 3; break;
		case COLOR_CYAN   : c = 4; break;
	}

	ui::Label select[] = {
		{ COLOR_RED    , L"Красный  ", 1 },
		{ COLOR_GREEN  , L"Зеленый  ", 1 },
		{ COLOR_BLUE   , L"Синий    ", 1 },
		{ COLOR_MAGENTA, L"Пурпурный", 1 },
		{ COLOR_CYAN   , L"Голубой  ", 0 }
	};

	ui::decotitle(1, COLOR_CYAN, L"Настройки | Цвет | Игрок " + std::to_wstring(vpid), 69);

	c = ui::ilist(
		{ static_cast<uint8_t>(center.x - 3 - select[0].text.length() / ui::pxw / 2), static_cast<uint8_t>(center.y - 4) },
		L" [ ",
		L" ] ",
		select,
		5,
		c,
		true
	);

	switch (c) {
		case 1: ps.color = COLOR_RED    ; break;
		case 2: ps.color = COLOR_GREEN  ; break;
		case 3: ps.color = COLOR_BLUE   ; break;
		case 4: ps.color = COLOR_MAGENTA; break;
		case 5: ps.color = COLOR_CYAN   ; break;
		default:;
	}

	erase();
}

void keysel(const Direction & dir, const uint8_t & vpid, stg::PlayerSetting & ps) {
	Point center = ui::center();
	Size size = ui::size();

	std::wstring ndir = L"";
	switch (dir) {
		case Up   : ndir = L"вверх" ; break;
		case Down : ndir = L"вниз"  ; break;
		case Right: ndir = L"вправо"; break;
		case Left : ndir = L"влево" ; break;
	}

	ui::decotitle(1, COLOR_CYAN, L"Настройки | Клавиша " + ndir + L" | Игрок " + std::to_wstring(vpid), 69);

	ui::title(size.h - 3, COLOR_YELLOW, L"Удостовертесь что раскладка на английском ");
	ui::title(size.h - 2, COLOR_YELLOW, L"Выключите Caps Lock и включите Num Lock   ");
	ui::decoframe(
		{ static_cast<uint8_t>(center.x - (ui::pxw % 2 == 1 ? 1 : 2) - 21 / ui::pxw), static_cast<uint8_t>(size.h - 4) },
		{ static_cast<uint8_t>((42 / ui::pxw) + (ui::pxw % 2 == 1 ? 2 : 3)), 4 }
	);

	int c = 0;

	bool exit = false;
	while (!exit && (c = getch()) != KEY_ESC) switch (dir) {
		case Up   : ps.keyup    = c; exit = true; break;
		case Down : ps.keydown  = c; exit = true; break;
		case Right: ps.keyright = c; exit = true; break;
		case Left : ps.keyleft  = c; exit = true; break;
	}

	erase();
}

void playersel(const uint8_t pid, stg::PlayerSetting * ps) {
	Point center = ui::center();

	uint8_t sel = 1;

	do {
		{
		ui::Label select[] = {
			{ ps[0].color, L"Игрок 1", 1 },
			{ ps[1].color, L"Игрок 2", 1 },
			{ ps[2].color, L"Игрок 3", 1 },
			{ ps[3].color, L"Игрок 4", 2 },
			{ COLOR_RED  , L"Сброс  ", 0 }
		};

		ui::decotitle(1, COLOR_CYAN, L"Настройки", 69);

		ui::ilistprint(
			{ static_cast<uint8_t>(center.x / 2 - 3 - select[0].text.length() / ui::pxw / 2), static_cast<uint8_t>(center.y - 5) },
			L" [ ",
			L" ] ",
			select,
			5,
			pid
		);
	}

	const char * keyup    = keyname(ps[pid].keyup);
	const char * keydown  = keyname(ps[pid].keydown);
	const char * keyright = keyname(ps[pid].keyright);
	const char * keyleft  = keyname(ps[pid].keyleft);

	std::wstring names[] = {
		L"Имя: " + ps[pid].name,
		L"Цвет: ",
		L"Клавиша вверх : " + std::wstring(keyup   , keyup    + strlen(keyup)),
		L"Клавиша вниз  : " + std::wstring(keydown , keydown  + strlen(keydown)),
		L"Клавиша вправо: " + std::wstring(keyright, keyright + strlen(keyright)),
		L"Клавиша влево : " + std::wstring(keyleft , keyleft  + strlen(keyleft))
	};

	switch (ps[pid].color) {
		case COLOR_RED    : names[1] += L"красный"; break;
		case COLOR_GREEN  : names[1] += L"зеленый"; break;
		case COLOR_BLUE   : names[1] += L"синий"; break;
		case COLOR_MAGENTA: names[1] += L"пурпурный"; break;
		case COLOR_CYAN   : names[1] += L"голубой"; break;
	}

	uint8_t mlen = 0;
	for (uint8_t i = 0; i < 6; i++) if (mlen < names[i].length()) mlen = names[i].length();
	for (uint8_t i = 0; i < 6; i++) if (mlen > names[i].length()) names[i] + std::wstring(mlen - names[i].length(), ' ');
	
	ui::Label select[] = {
		{ COLOR_WHITE  , names[0], 1 },
		{ ps[pid].color, names[1], 1 },
		{ COLOR_WHITE  , names[2], 1 },
		{ COLOR_WHITE  , names[3], 1 },
		{ COLOR_WHITE  , names[4], 1 },
		{ COLOR_WHITE  , names[5], 1 }
	};

	sel = ui::ilist(
		{ static_cast<uint8_t>(center.x + center.x / 2 - 3 - select[0].text.length() / ui::pxw / 2), static_cast<uint8_t>(center.y - 5) },
		L"> ",
		L"",
		select,
		6,
		sel - 1,
		true
	);

	erase();

	switch (sel) {
		case 1:       namesel(pid + 1, ps[pid]); break;
		case 2:      colorsel(pid + 1, ps[pid]); break;
		case 3: keysel(Up   , pid + 1, ps[pid]); break;
		case 4: keysel(Down , pid + 1, ps[pid]); break;
		case 5: keysel(Right, pid + 1, ps[pid]); break;
		case 6: keysel(Left , pid + 1, ps[pid]); break;
		default:;
	}

	} while(sel != 0);
}

void reset() {
	Point center = ui::center();

	ui::Label select[] = {
		{ COLOR_RED  , L"УДАЛИТЬ", 1 },
		{ COLOR_GREEN, L"ОТМЕНА ", 0 }
	};

	ui::decotitle(1, COLOR_RED, L"Настройки | Сброс", 69);
	ui::decotitle(ui::size().h - 2, COLOR_YELLOW, L"Это сбросит ваши настройки!", 1);

	uint8_t c = ui::ilist(
		{ static_cast<uint8_t>(center.x - 3 - select[0].text.length() / ui::pxw / 2), static_cast<uint8_t>(center.y - 1) },
		L" > ",
		L" < ",
		select,
		2,
		0,
		false
	);

	if (c == 1) {
		std::remove(stg::path.c_str());
		erase();
		ui::close();
		exit(0);
	}

	erase();
}

void settingmenu(stg::PlayerSetting * ps) {
	uint8_t c = 1;

	do {
		Point center = ui::center();

		ui::Label select[] = {
			{ ps[0].color, L"Игрок 1", 1 },
			{ ps[1].color, L"Игрок 2", 1 },
			{ ps[2].color, L"Игрок 3", 1 },
			{ ps[3].color, L"Игрок 4", 2 },
			{ COLOR_RED  , L"Сброс  ", 0 }
		};

		ui::decotitle(1, COLOR_CYAN, L"Настройки", 69);

		c = ui::ilist(
			{ static_cast<uint8_t>(center.x / 2 - 3 - select[0].text.length() / ui::pxw / 2), static_cast<uint8_t>(center.y - 5) },
			L" [ ",
			L" ] ",
			select,
			5,
			c - 1,
			true
		);

		erase();

		if (c == 5) reset(); else if (c != 0) playersel(c - 1, ps);
	} while (c);

	stg::save(ps);
}