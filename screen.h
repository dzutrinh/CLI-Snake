#ifndef _SCREEN_H_
#define _SCREEN_H_

/* hide/show cursor */
void cursor(int visible);

/* change text/background color */
void textcolor(int x);

/* move the cursor to position (x,y) */
void gotoxy(int x, int y);

/* returns the console screen width in columns */
int getmaxx();

/* returns the console screen width in rows */
int getmaxy();

/* returns the total number of color supported */
int getmaxcolor();

/* clear the screen */
void clrscr();

/* display a string at position (x,y) using color c */
void writesat(int x, int y, int c, const char * s);

/* display a character at position (x,y) using color c */
void writecat(int x, int y, int c, const char ch);

/* draw a horizontal line of with w at position (x,y), using color c */
void hline(int x, int y, int w, int c);

/* draw a frame of size w x h at position (x,y), using color c */
void frame(int x, int y, int w, int h, int c);

/* draw a box of size w x h at position (x,y), using color c */
void box(int x, int y, int w, int h, int c);

/* same as box but has a title at the top of the box */
void dialog(int x, int y, int w, int h, int c, const char * title);

#endif

