/* SIMPLE SNAKE GAME */
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>			/* for sprintf() */
#include <windows.h>		/* for Sleep() and other Windows stuffs */
#include "screen.h"

#define	MAXLEN	2000	/* maximum snake length */
#define	CHEAD	'o'
#define	CBODY	'o'
#define	CFRUIT	'#'

/* -- GAME LOGIC -- */
typedef struct _fruit {
	int x, y, color;
} FRUIT;

typedef struct _cell {
	int x, y;
} CELL;

typedef enum _navi {
	up, down, left, right
} NAVI;

typedef struct _snake {
	CELL	body[MAXLEN];
	NAVI	dir;
	int		length;
	int		score;
} SNAKE;

int main()
{
	SNAKE	snake = {{{0, 4}, {0, 5}}, down, 2, 0};
	FRUIT	fruit = {0, 0, 0};
	int		i, quit = 0, maxx, maxy, maxclr;
	char	key, score[32];
	
	maxx = getmaxx();
	maxy = getmaxy();
	maxclr = getmaxcolor();
	
	cursor(0);							/* hide the cursor back */
	srand(time(NULL));					/* initialize random generator */
	 
	fruit.x = (rand()%maxx) & ~1;		/* force x even and within [0, MAXX-1] */
	fruit.y = 4+rand()%(maxy-5);		/* y always within [4,MAXY-1] */
	fruit.color = 1+rand()%(maxclr-1);	/* avoid color 0, since it's black */
	
	do {
		clrscr();					/* clear screen */
		
		writesat(0, 0, 15,"   ____          __      ");
		writesat(0, 1, 15,"  / __/__  ___ _/ /_____ ");
		writesat(0, 2,  7," _\\ \\/ _ \\/ _ `/  '_/ -_)");
		writesat(0, 3,  8,"/___/_//_/\\_,_/_/\\_\\\\__/ ");

		/* display score */
		writesat(30, 2, 15, "SCORE:");
		sprintf(score, "%d", snake.score);
		writesat(37, 2, 7, score);

		/* instructions */
		writesat(30, 3, 11, "WASD: Move  Q: Quit");
		
		/* update the snake body based on its head */
		for (i = snake.length-1; i > 0; i--) {
			snake.body[i]= snake.body[i-1];
		}
		
		/* keyboard handling */
		if (kbhit())
		{
			key = toupper(getch());	/* read the key */
			switch(key) {			/* and process it */
			/* ESC, Q: quit game */
			case 27 :
			case 'Q': quit = 1; break;
			/* W: Up, S: Down, A: Left, D: Right */
			case 'W': if (snake.dir != down) snake.dir = up; break;
			case 'S': if (snake.dir != up) snake.dir = down; break;
			case 'A': if (snake.dir != right) snake.dir = left; break;
			case 'D': if (snake.dir != left) snake.dir = right; break;
			default : break;
			}
		}
		
		/* update the head's coordinates */
		switch(snake.dir) {
			case up   : snake.body[0].y--; break;
			case down : snake.body[0].y++; break;
			/* x always a multiple of 2, since it was inited at 0 */
			case left : snake.body[0].x-=2; break;	
			case right: snake.body[0].x+=2; break;
		}
			
		/* wrap the snake at screen boundaries */
		if (snake.body[0].y < 4)      snake.body[0].y = maxy-2;
		if (snake.body[0].y > maxy-1) snake.body[0].y = 4;
		if (snake.body[0].x < 0)      snake.body[0].x = maxx-2;
		if (snake.body[0].x > maxx-1) snake.body[0].x = 0;
			
		/* snake eats fruits? */
		if (snake.body[0].x == fruit.x && snake.body[0].y == fruit.y) {
			snake.length++;		/* it grows */
			snake.score++;		/* and update the score */
			/* regenerate a new fruit */
			fruit.x = (rand()%maxx) & ~1;
			fruit.y = 4+rand()%(maxy-5);
			fruit.color = 1+rand()%(maxclr-1);
		}
		
		/* screen painting occurred here */
		writecat(fruit.x, fruit.y, fruit.color, CFRUIT);			/* fruit */
		writecat(snake.body[0].x, snake.body[0].y, 15, CHEAD);	/* snake's head */	
		/* snake's body */
		for (i = 1; i < snake.length; i++) {
			writecat(snake.body[i].x, snake.body[i].y, 8, CBODY);
		}
		
		Sleep(50);				/* slow down a bit */
	} while(!quit);
	
	cursor(1);					/* turn the cursor back on */
	clrscr();

    return 0;
}
