#include "mainmenu.h"

#include <ncurses.h>
#include <stdint.h>
#include <string>
#include "../ui/ui.h"

uint8_t mainmenu() {
	Point center = ui::center();

	ui::Label select[] = {
		{ COLOR_GREEN , L"Начать игру", 1 },
		{ COLOR_YELLOW, L"Настройки  ", 1 },
		{ COLOR_RED   , L"Выход      ", 0 }
	};

	ui::decotitle(1, COLOR_CYAN, L"FPTSnake", 69);

	uint8_t sel = ui::ilist(
		{ static_cast<uint8_t>(center.x - 3 - select[0].text.length() / ui::pxw / 2), static_cast<uint8_t>(center.y - 1) },
		L" [ ",
		L" ] ",
		select,
		3,
		0,
		false
	);

	erase();

	return sel;
}