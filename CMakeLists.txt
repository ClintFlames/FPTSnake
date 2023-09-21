cmake_minimum_required(VERSION 3.5)



project(
	FPTSnake
	VERSION 1.0.0
	LANGUAGES C CXX
	DESCRIPTION "FPTSnake - is four player terminal snake."
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_executable(
	fptsnake
	"src/main.cpp"
	"src/charmath.h"
	
	"src/namespace/ui.h"
	"src/namespace/ui.cpp"
	"src/namespace/stg.h"
	"src/namespace/stg.cpp"
	
	"src/menus/keytest.h"
	"src/menus/keytest.cpp"
	"src/menus/firstsetup.h"
	"src/menus/firstsetup.cpp"
	"src/menus/mainmenu.h"
	"src/menus/mainmenu.cpp"
	"src/menus/selectgame.h"
	"src/menus/selectgame.cpp"
	"src/menus/settingmenu.h"
	"src/menus/settingmenu.cpp"
)

target_compile_options(fptsnake PRIVATE -Wall -Wextra -Wold-style-cast -Wuninitialized -O4)


set(CURSES_NEED_NCURSES, TRUE)
include("FindNcursesw.cmake")
find_package(Ncursesw QUIET)

if (NOT DEFINED CURSES_HAVE_NCURSESW_NCURSES_H)
	message(FATAL_ERROR "ncursesw/ncurses.h is not available.")
endif()

include_directories(${CURSES_INCLUDE_DIRS})

target_link_libraries(fptsnake ${CURSES_LIBRARIES})
