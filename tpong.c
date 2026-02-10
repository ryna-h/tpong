#include<unistd.h>
#include<ncurses.h>
#include<locale.h>

#define DELAY 30000

typedef struct{ //sets up struct for window borders.
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct{ //sets up sizing & position for box
	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

typedef struct{
	int ballX, ballY;
	char ballChar;
}BALL;

void init_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "");	
	//initialize needed objects
	WIN lWin;
	WIN rWin;
	BALL ball;

	int xBall, yBall; // serve as active coordinates for ball
	int xMax, yMax; //max x & y coords. may need to reinitialize these in case user changes screen size.
	int ch;
	int nextX, nextY; // should probably set these to middle of screen. 
	int xDirection=1; //sets direction of ball if positive right negative left.
	int yChange=0; //set initial y movement of ball. may want to randomize this val.
    
	initscr(); //sets up screen 
 	noecho(); //tells terminal to not echo keypresses
	getmaxyx(stdscr, yMax, xMax); //gets screen size in xy coords. stdscr is initialized by initscr()
	curs_set(FALSE); //hides cursor in window
	
	timeout(30); //cycle time for entire game currently 30ms 
				 
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	init_win_params(&lWin);
	init_win_params(&rWin);
	refresh();

	//starting x position for each paddle
	lWin.startx = 2;
	rWin.startx = xMax-4;

	//starting point for ball
	xBall = xMax/2;
	yBall = yMax/2;


	while(TRUE){
		//paddle hit conditions
		bool botHit = (yBall >= yMax);
		bool topHit = (yBall <= 0);

		ch = getch();
		//lBar logic
		if (ch != ERR){
			switch(ch){
				case 'w':
				create_box(&lWin, FALSE);
				--lWin.starty;
				create_box(&lWin, TRUE);
				break;
			case 's':
				create_box(&lWin, FALSE);
				++lWin.starty;
				create_box(&lWin, TRUE);
				break;
			}
		}
		//rBar logic
		if (ch != ERR){
			switch(ch){
				case 'i':
				create_box(&rWin, FALSE);
				--rWin.starty;
				create_box(&rWin, TRUE);
				break;
			case 'k':
				create_box(&rWin, FALSE);
				++rWin.starty;
				create_box(&rWin, TRUE);
				break;
			}
		}
		bool leftHit = ((nextX == lWin.startx+3) && (yBall >= lWin.starty && yBall <=lWin.starty+5));
		bool rightHit = ((nextX == rWin.startx-1) && (yBall >= rWin.starty && yBall <= rWin.starty+5));
		//ball logic
		nextX = xBall + xDirection;
		nextY = yBall + yChange;

		//handles x ball movement TODO: add scoring logic here as well.
		if(rightHit){
			xDirection = xDirection *-1;
			xBall += xDirection;
		}
		else if(leftHit){
			xDirection = xDirection *-1;
			xBall += xDirection;
		}
		else{
			xBall += xDirection;
		}

		//handles ball y movement
		int yLeftRelation = yBall - lWin.starty;
		int yRightRelation =yBall - rWin.starty;

		if (topHit || botHit){
			yChange = yChange *-1;	
		}
		else if (leftHit){
			switch(yLeftRelation){
				case 0: 
					yChange = -2;
					break;
				case 1:
					yChange = -1;
					break;
				case 2:
					yChange = 0;
					break;
				case 3:
					yChange = 0;
					break;
				case 4:
					yChange = 2;
					break;
				default:
					break;
			}
		}
		yBall += yChange;
		clear();
   		create_box(&lWin, TRUE);            // or draw paddle here
   		create_box(&rWin, TRUE);            // or draw paddle here
   		mvprintw(yBall, xBall, "o");
    	refresh();
	}
	endwin(); //after program is finished returns to normal terminal
}

// window parameter setup
void init_win_params(WIN *p_win){
	p_win->height = 5;
	p_win->width = 2;
	p_win->starty = (LINES - p_win->height)/2; //need to look into this	
	p_win->startx = (COLS - p_win->width)/2; // need to look into this
	p_win->border.ls = ACS_VLINE;
	p_win->border.rs = ACS_VLINE;
	p_win->border.ts = ACS_HLINE;
	p_win->border.bs = ACS_HLINE;
	p_win->border.tl = ACS_ULCORNER;
	p_win->border.tr = ACS_URCORNER;
	p_win->border.bl = ACS_LLCORNER;
	p_win->border.br = ACS_LRCORNER;
}
void create_box(WIN *p_win, bool flag){
	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
	refresh();
}
