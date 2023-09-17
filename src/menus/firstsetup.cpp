#include "firstsetup.h"

#include <ncurses.h>
#include <stdint.h>
#include <string>
#include "../namespace/ui.h"

void firstsetup() {
	Point center = ui::center();

	ui::Label select[] = {
		{ COLOR_WHITE, L" █", 1 },
		{ COLOR_WHITE, L"██", 0 }
	};

	ui::decotitle(1, COLOR_CYAN, L"Выберите размер пикселя", 1);

	ui::initpx(ui::ilist(
		{ static_cast<uint8_t>(center.x - 4), static_cast<uint8_t>(center.y - 1) },
		L" > ",
		L" < ",
		select,
		2,
		0,
		false
	));

	erase();
}