#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ncurses.h>

#define DELAY 30000

int main(int argc, char *argv[]) {

	int x=0, y=0;
	int maxX=0, maxY=0;
	int nextX=0;
	int direction=1;
    
	initscr(); //sets up screen 
 	noecho(); //tells terminal to not echo keypresses
	curs_set(FALSE); //hides cursor in window

	while(1){
		getmaxyx(stdscr, maxY, maxX); //gets screen size in xy coords. stdscr is initialized by initscr()
		clear(); //clears screen
		mvprintw(y,x,"o"); //prints in y,x coordinates
		refresh(); //refreshes screen
		usleep(DELAY);
		nextX = x + direction;

		if (nextX >= maxX || nextX < 0){ //for loop that checks wall limits and swaps ball direction
			direction*= -1;
		} 
		else{
			x+= direction;
		}
	}
	endwin(); //after program is finished returns to normal terminal
}
