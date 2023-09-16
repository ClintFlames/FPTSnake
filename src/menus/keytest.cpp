#include "keytest.h"

#include <ncurses.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include "../ui/ui.h"

void keytest() {
	Point center = ui::center();

	wint_t c = 0;
	do {
		auto v = key_name(c);
		wchar_t w = L'0';
		{
			
		}

		ui::decotitle(1, COLOR_CYAN, L"Меню тестировки", 1);
		ui::decotitle(
			ui::size().h - 2,
			COLOR_RED,
			L"Key: " + std::wstring({ui::wcharname(c)}) + L" Code: " + std::to_wstring(c),
			1
		);

		
		get_wch(&c);
		
		erase();
	} while (c != 27) ;
	
	erase();
}