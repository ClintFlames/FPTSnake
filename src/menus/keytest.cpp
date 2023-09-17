#include "keytest.h"

#include <ncurses.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include "../namespace/ui.h"

void keytest() {
	wint_t c = 0;
	do {
		ui::decotitle(1, COLOR_CYAN, L"Меню тесировки", 1);
		ui::decotitle(
			ui::size().h - 2,
			COLOR_RED,
			L"Key: " + std::wstring({ui::wcharname(c)}) + L" Code: " + std::to_wstring(c),
			1
		);

		get_wch(&c);
		
		erase();
	} while (c != KEY_ESC) ;
	
	erase();
}