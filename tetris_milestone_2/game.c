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
#include "highscore.h"
#include "game.h"
#include "well.h"
#include "tetris.h"
#include "tetromino.h"
#include "key.h"

void init_game(void) {
  int x,y;
}

highscore_t *game(highscore_t *highscores) {
  static int state = INIT;
  tetromino_t *next = NULL;
  tetromino_t *current = NULL;
  well_t *w;
  int x,y;
  int c;
  int arrow;
  struct timespec tim = {0,1000000};
  struct timespec tim_ret;
  int move_counter = 0;
  int move_timeout = 500;
  int status;
  int statusTry;
  int counter = 0;
  int lines_cleared = 0;
  int score = 0;
  char str[80];
  int timec = 0;
  int time_c = 0;  
  int co = 1;//iteration of current color pair
  int time_out = 0;

  while(1) {
    switch(state) {
    case INIT:               // Initialize the game, only run one time 
      initscr();
      nodelay(stdscr,TRUE);  // Do not wait for characters using getch.  
      noecho();              // Do not echo input characters 
      getmaxyx(stdscr,y,x);  // Get the screen dimensions 
      w = init_well(((x/2)-(WELL_WIDTH/2)),3,WELL_WIDTH,WELL_HEIGHT);
      draw_well(w);
      srand(time(NULL));     // Seed the random number generator with the time. Used in create tet. 
      display_score(score, w->upper_left_x-15,w->upper_left_y);  
      display_time(timec, w->upper_left_x-15,w->upper_left_y+5);
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
      statusTry = move_tet(current,current->upper_left_x,current->upper_left_y+1);

      if(statusTry == MOVE_FAILED){
      state = GAME_OVER;
      break;
      }
      else{
      statusTry = move_tet(current,current->upper_left_x,current->upper_left_y-1);
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
	if (arrow == UP) {
	  undisplay_tetromino(current);
	  rotate_ccw(current);
	  attron(COLOR_PAIR(co));//color
	  display_tetromino(current);
	  attroff(COLOR_PAIR(co));
	}
	else if (arrow == DOWN) {
	  undisplay_tetromino(current);
	  rotate_cw(current);
	  attron(COLOR_PAIR(co));//color
	  display_tetromino(current);
	  attroff(COLOR_PAIR(co));
	}
	else if (arrow == LEFT) {
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x-1,current->upper_left_y);
	  attron(COLOR_PAIR(co));//color
	  display_tetromino(current);
	  attroff(COLOR_PAIR(co));
	}
	else if (arrow == RIGHT) {
	  undisplay_tetromino(current);
	  move_tet(current,current->upper_left_x+1,current->upper_left_y);
	  attron(COLOR_PAIR(co));//color
	  display_tetromino(current);
	  attroff(COLOR_PAIR(co));
	}
      	else if (arrow == REGCHAR) {
	  if (c == ' ') {
	    move_timeout = DROP_RATE;
 	  }
	  if (c == 'q') {
	    state = GAME_OVER;
 	  }
	}
      } 
      if (move_counter++ >= move_timeout) {
	counter++;
	undisplay_tetromino(current);
	status = move_tet(current,current->upper_left_x,current->upper_left_y+1);
	attron(COLOR_PAIR(co));//color
	display_tetromino(current);
	attroff(COLOR_PAIR(co));
	if (status == MOVE_FAILED) {
	  lines_cleared += prune_well(w);
	  score = compute_score(score, (lines_cleared));
	  lines_cleared = 0;
	  state = ADD_PIECE;
	  co++;
	  move_timeout = BASE_FALL_RATE;
	}

        display_score(score, w->upper_left_x-15,w->upper_left_y);

	move_counter = 0;
      }
      if (time_c++ == 1000){
	timec++;
	display_time(timec, w->upper_left_x-15,w->upper_left_y+5); 
	time_c = 0;
	}
      if (time_out++ == 300000){

	state = GAME_OVER;

      }
      break;
    case GAME_OVER:
      nodelay(stdscr,FALSE);
      clear();
      getmaxyx(stdscr,y,x);
      mvprintw(1,x/2-5,"  GAME_OVER  ");
      mvprintw(2,x/2-5,"#############");
      mvprintw(5,x/2-5,"    SCORE    ");
      mvprintw(6,x/2-5,"      %d     ", score);
      mvprintw(16,x/2-5,"Hit q to exit");
      getch(); // Wait for a key to be pressed. 
      state = EXIT;
      break;
    case EXIT:
      return(highscores);  // Return the highscore structure back to main to be stored on disk. 
      break;
    }
    refresh();
    nanosleep(&tim,&tim_ret);
  }
}

/* game.c ends here */
