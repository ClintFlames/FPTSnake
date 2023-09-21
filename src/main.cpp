#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <limits.h>
#include "namespace/ui.h"
#include "namespace/stg.h"
#include "menus/keytest.h"
#include "menus/firstsetup.h"
#include "menus/mainmenu.h"
#include "menus/settingmenu.h"
#include "menus/selectgame.h"



// #define DBG

int main() {
	ui::init(100);

	#ifdef DBG
	keytest();
	#endif

	// Setup settings path
	{
		// #include <string>
		// #include <windows.h>
		// 
		// std::string getexepath()
		// {
		// char result[ MAX_PATH ];
		// return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
		// }

		char result[512];
		ssize_t count = readlink("/proc/self/exe", result, 512);
		stg::path = std::string(result, (count > 0) ? count : 0);
		stg::path.erase(stg::path.find_last_of('/'));
		stg::path += "/fptsnake.stg.bin";
	}

	stg::PlayerSetting ps[4];

	if (!stg::load(ps)) {
		stg::initdef(ps);
		firstsetup();
		stg::save(ps);
	}

	uint8_t c = 1;

	// Mainmenu loop
	while (true) {
		c = mainmenu(c - 1);
		
		if (c == 3) break;
		
		if (c == 1) selectgame(ps); else settingmenu(ps);
	}

	ui::close();

	return 0;
}