CONTIKI_PROJECT = smart-plug
CONTIKI = $(CONTIKI_HOME)

PROJECT_SOURCEFILES += smart-plug-shell.c

APPS += serial-shell

all: smart-plug

include $(CONTIKI)/Makefile.include
