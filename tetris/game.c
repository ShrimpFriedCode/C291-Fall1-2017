/* game.c --- 
 * 
 * Filename: game.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Tue Sep  6 11:08:59 2016
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2016 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <unistd.h> 
#include <ncurses.h>
#include <time.h>
#include "game.h"
#include "well.h"
#include "tetris.h"
#include "tetromino.h"
#include "key.h"

void init_game(void) {
  int x,y;
}

int game(void) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  well_t *w;
  int x,y;
  int c;
  int co = 1;//iteration of current color pair
  int arrow;
  struct timespec tim = {0,1000000};  // Each execution of while(1) is approximately 1mS
  struct timespec tim_ret;
  int move_counter = 0;
  int move_timeout = BASE_FALL_RATE;            

  while(1) {
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      noecho();              // Do not echo input characters 
      getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),1,WELL_WIDTH,WELL_HEIGHT);
      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      state = ADD_PIECE;
      start_color();//start color
      break;
    case ADD_PIECE:          // Add a new piece to the game
      if (next) {
	current = next;
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      else {
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	next = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
      }
      int r = ( rand() % 6) + 1; //random selector for color
      current->color[0] = co;//assign color to color properties of tet
      current->color[1] = r;
      current->color[2] = r;
      init_pair(co, current->color[1], current->color[2]);//initialize pair
      attron(COLOR_PAIR(co));//turn on/off color
      display_tetromino(current);
      attroff(COLOR_PAIR(co));
      move_timeout = BASE_FALL_RATE;//reset fall rate
      state = MOVE_PIECE;
      break;
    case MOVE_PIECE:         // Move the current piece 
      if ((arrow = read_escape(&c)) != NOCHAR) {
	switch (arrow) {
	case UP:
	  mvprintw(10,10,"UP            ");
	  undisplay_tetromino(current);
	  rotate_cw(current);//rotate
	  attron(COLOR_PAIR(co));//color
	  display_tetromino(current);
	  attroff(COLOR_PAIR(co));
	  break;
	case DOWN:
	  mvprintw(10,10,"DOWN          ");
	  undisplay_tetromino(current);
          rotate_ccw(current);//rotate
          attron(COLOR_PAIR(co));//color
          display_tetromino(current);
          attroff(COLOR_PAIR(co));
	  break;
	case LEFT:
	  mvprintw(10,10,"LEFT          ");
   	  undisplay_tetromino(current);
	  move_tet(current, (current->upper_left_x - 1), (current->upper_left_y));//move left
	  attron(COLOR_PAIR(co));//color
	  display_tetromino(current); 
	  attroff(COLOR_PAIR(co));
	  break;
	case RIGHT:
	  mvprintw(10,10,"RIGHT         ");
          undisplay_tetromino(current);
          move_tet(current, (current->upper_left_x + 1), (current->upper_left_y));//move right
	  attron(COLOR_PAIR(co));//color
          display_tetromino(current);
	  attroff(COLOR_PAIR(co));
	  break;
	case REGCHAR: 
	  mvprintw(10,10,"REGCHAR 0x%02x",c);
	  if (c == 'q') {
	    state = EXIT;
 	  }
	  else if(c == ' '){
	    move_timeout = DROP_RATE;//if spacebar increase drop rate
	}
	}
      } 
      if (move_counter++ >= move_timeout) {
	undisplay_tetromino(current);
	int check = move_tet(current, (current->upper_left_x), (current->upper_left_y + 1));//move down
	attron(COLOR_PAIR(co));//color
	display_tetromino(current);
	attroff(COLOR_PAIR(co));
	move_counter = 0;//reset move counter
	if(check == MOVE_FAILED){//if at bottom
		state = ADD_PIECE;//change state
		co++;//increase color pair itterator
	}
      }
      break;
    case EXIT:
      endwin();
      return(0);
      break;
    }
    refresh();
    nanosleep(&tim,&tim_ret);
  }
}

/* game.c ends here */
