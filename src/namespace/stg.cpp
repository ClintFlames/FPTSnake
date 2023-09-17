#include "stg.h"

#include <ncurses.h>
#include <filesystem>
#include <fstream>
#include <stdint.h>
/*
настройки:
подпись (9 бит)
размер пикселя (бит)
избранный режим {
	режим игры (бит)
	режим стен (2 бита)
} x 2
длинна имени игрока 1, 2, 3, 4 (по 4 бита)
игрок {
	имя (2-17 символов- 4 байта символ)
	цвет (байт)
	клавишы вверх, вниз, право, влево (по байту на каждую)
} x 4
итого в лучше случае: 56 байт
в худшем: 296 байт
*/

// Read later
// https://stackoverflow.com/questions/1528298/get-path-of-executable

void stg::initdef(stg::PlayerSetting * ps) {
	ps[0] = { COLOR_BLUE   , L"Игрок 1", 'w'   , 's'     , 'd'      , 'a'      };
	ps[1] = { COLOR_RED    , L"Игрок 2", 'i'   , 'k'     , 'l'      , 'j'      };
	ps[2] = { COLOR_GREEN  , L"Игрок 3", KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT };
	ps[3] = { COLOR_MAGENTA, L"Игрок 4", 56    , 53      , 54       , 52       };
}

void stg::load(PlayerSetting *) {
	std::ifstream stgfile(std::filesystem::canonical("/proc/self/exe").append("fptsnake.stg.b"), std::ios_base::binary);

	if (!stgfile.is_open()) return;
	// stgfile

}