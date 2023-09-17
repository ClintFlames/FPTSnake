#include "ui.h"

#include <string>
#include <cstring>
#include <ncurses.h>
#include <locale.h>

uint8_t ui::pxw = 1;
std::wstring ui::px = L"█";

void ui::init(int errdelay) {
	// Включаем всю локализацию (Unicode)
	setlocale(LC_ALL, "");

	initscr();
	// Включаем режим посимвольного ввода (программа получает клавишы сразу, а не после нажатия Enter)
	raw();
	// Позволяет читать функциональные клавиши
	keypad(stdscr, true);
	// Введенные символы больше не печатаются в консоли
	noecho();
	// Отключаем мигание курсора
	curs_set(0);
	// Включает режим полу-задержки (выкидывает ERR после KEY_EENTER секунд)
	halfdelay(errdelay);

	// Убирает задержку клавише Escape
	ESCDELAY = 0;

	if (!has_colors()) exit(0);

	start_color();

	init_pair(COLOR_WHITE  , COLOR_WHITE  , COLOR_BLACK);
	init_pair(COLOR_RED    , COLOR_RED    , COLOR_BLACK);
	init_pair(COLOR_BLUE   , COLOR_BLUE   , COLOR_BLACK);
	init_pair(COLOR_YELLOW , COLOR_YELLOW , COLOR_BLACK);
	init_pair(COLOR_GREEN  , COLOR_GREEN  , COLOR_BLACK);
	init_pair(COLOR_CYAN   , COLOR_CYAN   , COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);

	attron(COLOR_PAIR(0));
}

void ui::initpx(uint8_t w) {
	ui::pxw = w;
	ui::px = std::wstring(w, L'█');
}

void ui::close() {
	// attroff(COLOR_PAIR(0));
	endwin();
}

Size ui::size() {
	return {
		static_cast<uint8_t>((COLS / ui::pxw) - (ui::pxw % 2)),
		static_cast<uint8_t>(LINES)
	};
}

Point ui::center() {
	Size s = ui::size();
	return {
		static_cast<uint8_t>(s.w / 2),
		static_cast<uint8_t>(s.h / 2)
	};
}



wchar_t ui::wcharname(wint_t i) {
	if (i > 0xFFFFFFF) return ERR;
	if (i <= 0xFF) return keyname(i)[0];
	return i;
}



void ui::title(const uint8_t & y, const uint8_t & color, const std::wstring & text) { ui::wtitle(stdscr, y, color, text); }
void ui::wtitle(WINDOW * win, const uint8_t & y, const uint8_t & color, const std::wstring & text) {
	uint8_t x = (COLS - text.length()) / 2;
	attron(COLOR_PAIR(color));
	mvwaddwstr(win, y, x, text.c_str());
	attron(COLOR_PAIR(COLOR_WHITE));
}

void ui::decotitle(const uint8_t & y, const uint8_t & color, const std::wstring & text, const uint8_t & gap) { ui::wdecotitle(stdscr, y, color, text, gap); }
void ui::wdecotitle(WINDOW * win, const uint8_t & y, const uint8_t & color, const std::wstring & text, const uint8_t & gap) {
	uint8_t rx = (COLS - text.length()) / 2;
	uint8_t w = 0;
	ui::wtitle(win, y, color, text);

	if (gap == 69) rx = 0;
	else rx = (rx - gap - 1) / ui::pxw;

	if (gap == 69) w = ui::size().w;
	else w = (text.length() / ui::pxw) + (text.length() % ui::pxw == 1 ? 0 : 1) + 2 + gap - 1;

	ui::wdecoframe(
		win,
		{ rx, static_cast<uint8_t>(y - 1) },
		{ w, 3 }
	);
}

void ui::frame(const Point & p, const Size & s) { ui::wframe(stdscr, p, s); }
void ui::wframe(WINDOW * win, const Point & p, const Size & s) {
	ui::whhline(win, p, s.w);
	ui::whhline(win, { p.x, static_cast<uint8_t>(p.y + s.h - 1) }, s.w);
	ui::wvvline(win, p, s.h);
	ui::wvvline(win, { static_cast<uint8_t>(p.x + s.w - 1), p.y }, s.w);
}

void ui::decoframe(const Point & p, const Size & s) { ui::wdecoframe(stdscr, p, s); }
void ui::wdecoframe(WINDOW * win, const Point & p, const Size & s) {
	uint8_t rx = p.x * ui::pxw;
	uint8_t rw = s.w * ui::pxw - ui::pxw + 1;

	for (uint8_t y = 0; y < s.h; y++) {
		if (y == 0 || y == s.h - 1) {
			for (uint8_t x = 1; x < rw; x++) mvwaddch(win, p.y + y, rx + x, '-');
			if (y == 0) {
				mvwaddch(win, p.y + y, rx, '/');
				mvwaddch(win, p.y + y, rx + rw, '\\');
			} else {
				mvwaddch(win, p.y + y, rx, '\\');
				mvwaddch(win, p.y + y, rx + rw, '/');
			}
		} else {
			mvwaddch(win, p.y + y, rx, '|');
			mvwaddch(win, p.y + y, rx + rw, '|');
		}
	}
}

void ui::hhline(const Point & p, uint8_t w) { ui::whhline(stdscr, p, w); }
void ui::whhline(WINDOW * win, const Point & p, uint8_t w) {
	for (uint8_t i = 0; i < w; i++) mvwaddwstr(win, p.y, (p.x + i) * ui::pxw, ui::px.c_str());
}

void ui::vvline(const Point & p, uint8_t h) { ui::wvvline(stdscr, p, h); }
void ui::wvvline(WINDOW * win, const Point & p, uint8_t h) {
	for (uint8_t i = 0; i < h; i++) mvwaddwstr(win, p.y + i, p.x * ui::pxw, ui::px.c_str());
}

void ui::square(const Point & p, const Size & s) { ui::wsquare(stdscr, p, s); }
void ui::wsquare(WINDOW * win, const Point & p, const Size & s) {
	for (uint8_t y = 0; y < s.h; y++) ui::whhline(win, { p.x, static_cast<uint8_t>(p.y + y) }, s.w);
}

void ui::listprint(const Point & p, const std::wstring & lsel, const std::wstring & rsel, ui::Label * labels, const uint8_t & labelCount) { ui::wlistprint(stdscr, p, lsel, rsel, labels, labelCount); }
void ui::wlistprint(WINDOW * win, const Point & p, const std::wstring & lsel, const std::wstring & rsel, ui::Label * labels, const uint8_t & labelCount) {
	attron(COLOR_PAIR(COLOR_WHITE));

	uint8_t gap = 0;

	for (uint8_t i = 0; i < labelCount; i++) {
		mvwaddwstr(win, p.y + i + gap, p.x * ui::pxw, lsel.c_str());

		attron(COLOR_PAIR(labels[i].color));

		mvwaddwstr(win, p.y + i + gap, p.x * ui::pxw + lsel.length(), labels[i].text.c_str());

		attron(COLOR_PAIR(COLOR_WHITE));

		mvwaddwstr(win, p.y + i + gap, p.x * ui::pxw + lsel.length() + labels[i].text.length(), rsel.c_str());

		gap += labels[i].gap;
	}
}

void ui::ilistprint(const Point & p, const std::wstring & lsel, const std::wstring & rsel, ui::Label * labels, const uint8_t & labelCount, const uint8_t & sel) { ui::wilistprint(stdscr, p, lsel, rsel, labels, labelCount, sel); }
void ui::wilistprint(WINDOW * win, const Point & p, const std::wstring & lsel, const std::wstring & rsel, ui::Label * labels, const uint8_t & labelCount, const uint8_t & sel) {
	std::wstring nolsel = std::wstring(lsel.length(), ' ');
	std::wstring norsel = std::wstring(rsel.length(), ' ');

	uint8_t gap = 0;

	attron(COLOR_PAIR(COLOR_WHITE));

	for (uint8_t i = 0; i < labelCount; i++) {
		if (lsel.length()) mvwaddwstr(win, p.y + i + gap, p.x * ui::pxw, (i == sel) ? lsel.c_str() : nolsel.c_str());

		attron(COLOR_PAIR(labels[i].color));

		mvwaddwstr(win, p.y + i + gap, p.x * ui::pxw + lsel.length(), labels[i].text.c_str());

		attron(COLOR_PAIR(COLOR_WHITE));

		if (rsel.length()) mvwaddwstr(win, p.y + i + gap, p.x * ui::pxw + lsel.length() + labels[i].text.length(), (i == sel) ? rsel.c_str() : norsel.c_str());

		gap += labels[i].gap;
	}
}

uint8_t ui::ilist(const Point & p, const std::wstring & lsel, const std::wstring & rsel, ui::Label * labels, const uint8_t & labelCount, const uint8_t & csel, bool ableExit) { return ui::wilist(stdscr, p, lsel, rsel, labels, labelCount, csel, ableExit); }
uint8_t ui::wilist(WINDOW * win, const Point & p, const std::wstring & lsel, const std::wstring & rsel, ui::Label * labels, const uint8_t & labelCount, const uint8_t & csel, bool ableExit) {
	uint8_t sel = csel;

	wilistprint(win, p, lsel, rsel, labels, labelCount, sel);

	bool exit = false;
	while (!exit) {
		int c = getch();
		switch (c) {
			case KEY_ESC: {
				if (ableExit) {
					sel = 0;
					exit = true;
				}
				break;
			}
			case KEY_EENTER: {
				sel++;
				exit = true;
				break;
			}
			case KEY_UP: case 56: {
				if (sel == 0) sel = labelCount;
				wilistprint(win, p, lsel, rsel, labels, labelCount, --sel);
				break;
			}
			case KEY_DOWN: case 50: {
				if (++sel == labelCount) sel = 0;
				wilistprint(win, p, lsel, rsel, labels, labelCount, sel);
				break;
			}
		}
	}

	return sel;
}

std::wstring ui::itextinput(const Point & p, const std::wstring & text, const uint8_t & minlen, const uint8_t & maxlen, bool ableExit) { return ui::witextinput(stdscr, p, text, minlen, maxlen, ableExit); }
std::wstring ui::witextinput(WINDOW * win, const Point & p, const std::wstring & text, const uint8_t & minlen, const uint8_t & maxlen, bool ableExit) {
	curs_set(2);
	uint8_t rx = p.x * ui::pxw;
	
	std::wstring s = text;
	wint_t inp = 0;
	uint8_t pos = s.length();
	

	mvwaddwstr(win, p.y, rx, s.c_str());
	wmove(win, p.y, rx + pos);

	bool exit = false;
	while (!exit) {
		int status = wget_wch(win, &inp);

		switch (inp) {
			case KEY_ESC: if (ableExit) { exit = true; s = text; } break;
			case KEY_EENTER: if (s.length() >= minlen && s.length() <= maxlen) { exit = true; } break;
			case KEY_BACKSPACE: if (s.length() != 0) {
				if (pos == s.length()) {
					s.pop_back();
				} else {
					s.erase(pos - 1, 1);
					mvwaddwstr(win, p.y, rx, s.c_str());
				}
				
				mvwaddch(win, p.y, rx + s.length(), ' ');
				wmove(win, p.y, rx + --pos);
				wrefresh(win);
			} break;
			case KEY_LEFT: if (pos > 1) {
				wmove(win, p.y, rx + --pos);
				wrefresh(win);
			} break;
			case KEY_RIGHT: if (pos < s.length()) {
				wmove(win, p.y, rx + ++pos);
				wrefresh(win);
			} break;
			default: if (s.length() < maxlen && status == OK) {
				if (pos == s.length()) s += ui::wcharname(inp); else s.insert(pos, { ui::wcharname(inp) });
				
				mvwaddwstr(win, p.y, rx, s.c_str());
				wmove(win, p.y, rx + ++pos);
				wrefresh(win);
				break;
			}
		}
	}

	curs_set(0);

	return s;
}