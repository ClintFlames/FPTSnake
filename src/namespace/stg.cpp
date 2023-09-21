#include "stg.h"

#include <ncurses.h>
#include <filesystem>
#include <fstream>
#include <stdint.h>
#include "ui.h"



// Helper functions
uint8_t read_uint8(std::ifstream & file) {
	char c;
	file.read(&c, 1);
	return static_cast<uint8_t>(c);
}

uint16_t read_uint16(std::ifstream & file) {
	char c[2];
	file.read(c, 2);
	return (static_cast<uint8_t>(c[0]) << 8) + static_cast<uint8_t>(c[1]);
}

void write_uint8(std::ofstream & file, const uint8_t & v) {
	char c = v;
	file.write(&c, 1);
}

void write_uint16(std::ofstream & file, const uint16_t & v) {
	char c[2] = { static_cast<char>(v >> 8), static_cast<char>(v & 0xFF) };
	file.write(c, 2);
}



uint8_t stg::favmode = 0;
std::string stg::path = "";
uint16_t stg::sign = 0b100111001;

std::wstring stg::wsfavmode(const stg::FavMode & fm) {
	std::wstring s = L"";
	
	switch (fm.gamemode) {
		case stg::Standart: s += L"Стандартная "; break;
		case stg::Effect  : s += L"Эффектная "  ; break;
	}

	switch (fm.wallmode) {
		case stg::Box       : s += L"коробка"          ; break;
		case stg::RandomBox : s += L"рандомная коробка"; break;
		case stg::Void      : s += L"пустота"          ; break;
		case stg::RandomVoid: s += L"рандомная пустота"; break;
	}

	return s;
}

void stg::initdef(stg::PlayerSetting * ps) {
	ps[0] = { COLOR_BLUE   , L"Игрок 1", 'w'   , 's'     , 'd'      , 'a'      };
	ps[1] = { COLOR_RED    , L"Игрок 2", 'i'   , 'k'     , 'l'      , 'j'      };
	ps[2] = { COLOR_GREEN  , L"Игрок 3", KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT };
	ps[3] = { COLOR_MAGENTA, L"Игрок 4", 56    , 53      , 54       , 52       };

	stg::favmode = 0;
}

// TODO: Fix crashes/file length
// TODO: check colors on load
bool stg::load(stg::PlayerSetting * ps) {
	// Reject if file not exists or if path is directory
	if (!std::filesystem::exists(stg::path) || std::filesystem::is_directory(stg::path)) return false;

	std::ifstream file(stg::path, std::ios_base::binary);

	// Reject if file for some reason is not open
	if (!file.is_open()) return false;

	uint16_t head = read_uint16(file);

	// Check file signature
	if (stg::sign != head >> 7) return false;

	// Extract pixel size and favmode
	uint8_t pixel_size = 1 + ((head >> 6) & 0b1);
	uint8_t favmodeint = head & 0b111111;

	head = read_uint16(file);

	uint8_t namelen[4] = {
		static_cast<uint8_t>((head >> 12) & 0xF),
		static_cast<uint8_t>((head >> 8) & 0xF),
		static_cast<uint8_t>((head >> 4) & 0xF),
		static_cast<uint8_t>(head & 0xF)
	};
	std::wstring psname[4];
	uint8_t pscolor[4];
	uint16_t pskey[4 * 4];

	for (uint8_t pid = 0; pid < 4; pid++) {
		{
			char rl = namelen[pid] + 2;
			char c[rl * 4 + 4];
			file.read(c, rl * 4);
			c[rl * 4    ] = 0;
			c[rl * 4 + 1] = 0;
			c[rl * 4 + 2] = 0;
			c[rl * 4 + 3] = 0;
			wchar_t s[rl + 1];
			mbstowcs(s, c, rl * 4 + 4);
			psname[pid] = std::wstring(s);
		}

		pscolor[pid] = read_uint8(file);

		pskey[pid * 4    ] = read_uint16(file);
		pskey[pid * 4 + 1] = read_uint16(file);
		pskey[pid * 4 + 2] = read_uint16(file);
		pskey[pid * 4 + 3] = read_uint16(file);
	}

	// Saving data only if everything is fine
	ui::initpx(pixel_size);
	stg::favmode = favmodeint;

	for (uint8_t pid = 0; pid < 4; pid++) {
		ps[pid].name = psname[pid];
		ps[pid].color = pscolor[pid];
		ps[pid].keyup    = pskey[pid * 4    ];
		ps[pid].keydown  = pskey[pid * 4 + 1];
		ps[pid].keyright = pskey[pid * 4 + 2];
		ps[pid].keyleft  = pskey[pid * 4 + 3];
	}

	return true;
}

void stg::save(stg::PlayerSetting * ps) {
	std::ofstream file(stg::path, std::ios_base::binary);

	// Write head
	write_uint16(file, (stg::sign << 7) + ((ui::pxw - 1) << 6) + stg::favmode);

	// Write player name lengths
	write_uint16(file, (
		((ps[0].name.length() - 2) << 12) +
		((ps[1].name.length() - 2) << 8 ) +
		((ps[2].name.length() - 2) << 4 ) +
		((ps[3].name.length() - 2)      )
	));

	for (uint8_t pid = 0; pid < 4; pid++) {
		{
			size_t size = ps[pid].name.length() * 4;
			char * c = new char[size];

			std::wcstombs(c, ps[pid].name.c_str(), size);
			file.write(c, size);

			delete [] c;
		}

		write_uint8(file, ps[pid].color);

		write_uint16(file, static_cast<uint16_t>(ps[pid].keyup   ));
		write_uint16(file, static_cast<uint16_t>(ps[pid].keydown ));
		write_uint16(file, static_cast<uint16_t>(ps[pid].keyright));
		write_uint16(file, static_cast<uint16_t>(ps[pid].keyleft ));
	}
	file.close();
}

stg::FavMode stg::getfavmode(const uint8_t & id) {
	uint8_t fmi = (stg::favmode >> id * 3) & 0b111;

	return { static_cast<stg::GameMode>(fmi >> 2), static_cast<stg::WallMode>(fmi & 0b11) };
}

void stg::setfavmode(const uint8_t & id, const stg::FavMode & fm) {
	if (id == 0) {
		stg::favmode = stg::favmode & 0b111000;
	} else {
		stg::favmode = stg::favmode & 0b000111;
	}

	stg::favmode += ((fm.gamemode << 2) + fm.wallmode) << id * 3;
}