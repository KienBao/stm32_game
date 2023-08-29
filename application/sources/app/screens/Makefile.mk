CFLAGS		+= -I./sources/app/screens
CPPFLAGS	+= -I./sources/app/screens

VPATH += sources/app/screens

# CPP source files
SOURCES_CPP += sources/app/screens/scr_idle.cpp

SOURCES_CPP += sources/app/screens/scr_gameconca_menu.cpp
SOURCES_CPP += sources/app/screens/scr_ingame.cpp
SOURCES_CPP += sources/app/screens/scr_startup.cpp
SOURCES_CPP += sources/app/screens/scr_gameover.cpp

SOURCES_CPP += sources/app/screens/game_UI.cpp


