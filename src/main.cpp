#include <ncurses.h>
#include <string>
#include "namespace/ui.h"
#include "namespace/stg.h"
#include "menus/keytest.h"
#include "menus/firstsetup.h"
#include "menus/mainmenu.h"
#include "menus/settingmenu.h"



// #define DBG

int main() {
	ui::init(100);

	stg::PlayerSetting stg[4];
	stg::initdef(stg);

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