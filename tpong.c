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
