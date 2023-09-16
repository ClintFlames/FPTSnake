#include <ncurses.h>
#include <string>
#include "ui/ui.h"
#include "menus/keytest.h"
#include "menus/firstsetup.h"
#include "menus/mainmenu.h"
#include "menus/settingmenu.h"

// TODO: добавить проверку на размер экрана
// TODO: настройки
// TODO: собственно змейка

// #define DBG

int main() {
	ui::init(100);

	PlayerSetting stg[4] = {};

	// TODO дефолт, добавить загрузку из файла
	if (true) {
		stg[0].name = L"Игрок 1";
		stg[0].color = COLOR_BLUE;
		stg[0].keyup    = 'w';
		stg[0].keydown  = 's';
		stg[0].keyright = 'd';
		stg[0].keyleft  = 'a';

		stg[1].name = L"Игрок 2";
		stg[1].color = COLOR_RED;
		stg[1].keyup    = 'i';
		stg[1].keydown  = 'k';
		stg[1].keyright = 'l';
		stg[1].keyleft  = 'j';
		
		stg[2].name = L"Игрок 3";
		stg[2].color = COLOR_GREEN;
		stg[2].keyup    = KEY_UP;
		stg[2].keydown  = KEY_DOWN;
		stg[2].keyright = KEY_RIGHT;
		stg[2].keyleft  = KEY_LEFT;
		
		stg[3].name = L"Игрок 4";
		stg[3].color = COLOR_MAGENTA;
		stg[3].keyup    = 'w';
		stg[3].keydown  = 's';
		stg[3].keyright = 'd';
		stg[3].keyleft  = 'a';
	}
	
	#ifdef DBG
	keytest();
	#endif

	firstsetup();

	while (true) {
		uint8_t code = mainmenu();
		
		if (code == 3) break;
		
		if (code == 1) {
			// начать игру
		} else {
			settingmenu(stg);
		}
	}

	ui::close();

	return 0;
}