#pragma once

#include <ncurses.h>
#include <string>
#include "../charmath.h"

#define KEY_ESC 27
#define KEY_EENTER 10

namespace ui {
	extern uint8_t pxw;
	extern std::wstring px;

	struct Label {
		uint8_t color;
		const std::wstring & text;
		const uint8_t & gap;
	};
	

	void init(int);
	void initpx(uint8_t);
	void close();

	Size size();
	Point center();

	wchar_t wcharname(wint_t);

	void  title(          const uint8_t &, const uint8_t &, const std::wstring &);
	void wtitle(WINDOW *, const uint8_t &, const uint8_t &, const std::wstring &);

	void  decotitle(          const uint8_t &, const uint8_t &, const std::wstring &, const uint8_t &);
	void wdecotitle(WINDOW *, const uint8_t &, const uint8_t &, const std::wstring &, const uint8_t &);

	void  frame(          const Point &, const Size &);
	void wframe(WINDOW *, const Point &, const Size &);

	void  decoframe(          const Point &, const Size &);
	void wdecoframe(WINDOW *, const Point &, const Size &);

	void  hhline(          const Point &, uint8_t);
	void whhline(WINDOW *, const Point &, uint8_t);

	void  vvline(          const Point &, uint8_t);
	void wvvline(WINDOW *, const Point &, uint8_t);
	
	void  square(          const Point &, const Size &);
	void wsquare(WINDOW *, const Point &, const Size &);

	void  listprint(          const Point &, const std::wstring &, const std::wstring &, ui::Label *, const uint8_t &);
	void wlistprint(WINDOW *, const Point &, const std::wstring &, const std::wstring &, ui::Label *, const uint8_t &);

	void  ilistprint(          const Point &, const std::wstring &, const std::wstring &, ui::Label *, const uint8_t &, const uint8_t &);
	void wilistprint(WINDOW *, const Point &, const std::wstring &, const std::wstring &, ui::Label *, const uint8_t &, const uint8_t &);

	uint8_t  ilist(          const Point &, const std::wstring &, const std::wstring &, ui::Label *, const uint8_t &, const uint8_t &, bool);
	uint8_t wilist(WINDOW *, const Point &, const std::wstring &, const std::wstring &, ui::Label *, const uint8_t &, const uint8_t &, bool);

	std::wstring  itextinput(          const Point &, const std::wstring &, const uint8_t &, const uint8_t &, bool);
	std::wstring witextinput(WINDOW *, const Point &, const std::wstring &, const uint8_t &, const uint8_t &, bool);

}