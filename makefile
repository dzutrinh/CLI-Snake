#####
# Makefile for SNAKE
# how to use: just type 'mingw32-make' and ENTER
#####

CC=gcc
CFLAGS=
PROJECT=snake

all: $(PROJECT).exe

$(PROJECT).exe: main.c
	$(CC) $(CFLAGS) $< -o $(PROJECT).exe
	strip $(PROJECT).exe

clean:
	del main.o
	del $(PROJECT).exe
