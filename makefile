#####
# Makefile for SNAKE
# how to use: just type 'mingw32-make' and ENTER
#####

CC=gcc
CFLAGS=-Wall
PROJECT=snake
SOURCES=main.c screen.c

all: $(PROJECT).exe

$(PROJECT).exe: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(PROJECT).exe
	strip $(PROJECT).exe

clean:
	if exist main.o del main.o
	if exist screen.o del screen.o
	del $(PROJECT).exe
