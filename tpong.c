#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ncurses.h>

#define DELAY 30000

int main(int argc, char *argv[]) {

	int xBall=0, yBall=0; // serve as active coordinates for ball
	int yLbar=0;
	int xMax=0, yMax=0; //max x & y coords. may need to reinitialize these in case user changes screen size.
	int nextX=0, nextY=0; // should probably set these to middle of screen. 
	int direction=1; //sets direction of ball if positive right negative left.
    
	initscr(); //sets up screen 
 	noecho(); //tells terminal to not echo keypresses
	curs_set(FALSE); //hides cursor in window
	
	getmaxyx(stdscr, yMax, xMax); //gets screen size in xy coords. stdscr is initialized by initscr()
	xBall = xMax/2;
	yBall = yMax/2;

	while(1){
		clear(); //clears screen
		mvprintw(yBall,xBall,"o"); //prints in y,x coordinates
		mvprintw(yLbar,0,"|");
		refresh(); //refreshes screen
		usleep(DELAY);
		nextX = xBall + direction;

		if (nextX >= xMax || nextX < 0){ //for loop that checks wall limits and swaps ball direction
			direction = direction * -1;
		} 
		else{
			xBall+= direction;
		}
	}
	endwin(); //after program is finished returns to normal terminal
}


WINDOW *create_newwin(int height, int width, int starty, int startx) //create window function. pulled from wiki
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win) //function that erases box so it can be "moved"
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
