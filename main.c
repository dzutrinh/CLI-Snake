/* SIMPLE SNAKE GAME */
#include <stdio.h>			/* for printf() */
#include <windows.h>		/* for Sleep() and other Windows stuffs */

#define	MAXX		120		/* screen width in character: [0..119]*/
#define	MAXY		30		/* screen height in character: [0..29] */
#define	MAXCOLOR	16		/* maximum possible colors: [0..15] */
#define	MAXLEN		2000	/* maximum snake length */

/* -- MY CONSOLE I/O ROUTINES -- */
void cursor(int visible) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, visible};
    SetConsoleCursorInfo(handle, &cursor);
}

void textcolor(int x) {
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}

void gotoxy(int x, int y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void clrscr() {
	system("cls");	/* simplest way to clear the screen */
}

void writexy(int x, int y, int c, char * s) {
	gotoxy(x, y);
	textcolor(c);
	puts(s);
}

void writecxy(int x, int y, int c, char s) {
	gotoxy(x, y);
	textcolor(c);
	putchar(s);
}

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
	int		i, quit = 0;
	char	key;
	
	cursor(0);							/* hide the cursor back */
	srand(time(NULL));					/* initialize random generator */
	 
	fruit.x = (rand()%MAXX) & ~1;		/* force x even and within [0, MAXX-1] */
	fruit.y = 4+rand()%(MAXY-5);		/* y always within [4,MAXY-1] */
	fruit.color = 1+rand()%(MAXCOLOR-1);/* avoid color 0, since it's black */
	
	do {
		clrscr();					/* clear screen */
		writexy(0, 0, 15,"   ____          __      ");
		writexy(0, 1, 15,"  / __/__  ___ _/ /_____ ");
		writexy(0, 2,  7," _\\ \\/ _ \\/ _ `/  '_/ -_)");
		writexy(0, 3,  8,"/___/_//_/\\_,_/_/\\_\\\\__/ ");

		/* display score */
		writexy(30, 2, 15, "SCORE:");
		gotoxy(37, 2); textcolor(7); printf("%d", snake.score);

		/* instructions */
		writexy(30, 3, 11, "WASD: Move  Q: Quit");
		
		/* update the snake body based on its head */
		for (i = snake.length-1; i > 0; i--) {
			snake.body[i]= snake.body[i-1];
		}
		
		/* keyboard handling */
		if (kbhit())
		{
			key = getch();			/* read the key */
			switch(key) {			/* and process it */
			/* ESC, Q: quit game */
			case 27 :
			case 'Q':
			case 'q': quit = 1; break;
			/* W: Up, S: Down, A: Left, D: Right */
			case 'W':
			case 'w': if (snake.dir != down) snake.dir = up; break;
			case 'S':
			case 's': if (snake.dir != up) snake.dir = down; break;
			case 'A':
			case 'a': if (snake.dir != right) snake.dir = left; break;
			case 'D':
			case 'd': if (snake.dir != left) snake.dir = right; break;
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
		if (snake.body[0].y < 4)      snake.body[0].y = MAXY-2;
		if (snake.body[0].y > MAXY-1) snake.body[0].y = 4;
		if (snake.body[0].x < 0)      snake.body[0].x = MAXX-2;
		if (snake.body[0].x > MAXX-1) snake.body[0].x = 0;
			
		/* snake eats fruits? */
		if (snake.body[0].x == fruit.x && snake.body[0].y == fruit.y) {
			snake.length++;		/* it grows */
			snake.score++;		/* and update the score */
			/* regenerate a new fruit */
			fruit.x = (rand()%MAXX) & ~1;
			fruit.y = 4+rand()%(MAXY-5);
			fruit.color = 1+rand()%(MAXCOLOR-1);
		}
		
		/* screen painting occurred here */
		writecxy(fruit.x, fruit.y, fruit.color, '#');			/* fruit */
		writecxy(snake.body[0].x, snake.body[0].y, 15, 'o');	/* snake's head */	
		/* snake's body */
		for (i = 1; i < snake.length; i++) {
			writecxy(snake.body[i].x, snake.body[i].y, 8, 'o');
		}
		
		Sleep(50);				/* slow down a bit */
	} while(!quit);
	
	cursor(1);					/* turn the cursor back on */
	clrscr();

    return 0;
}
