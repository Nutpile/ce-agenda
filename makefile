# ----------------------------
# Makefile Options
# ----------------------------

NAME = AGENDA
ICON = icon.png
DESCRIPTION = "Agenda by Nutpile"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
