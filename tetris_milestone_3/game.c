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
#include <string.h>

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
  int statusTry;//int to try and add a piece to play
  int counter = 0;
  int lines_cleared = 0;
  int score = 0;//score
  char str[80];
  int timec = 0;//actual time in seconds
  int time_c = 0;//tracker for seconds
  int co = 1;//iteration of current color pair
  int time_out = 0;
  int r = 0;
  char inita[4];
  highscore_t *scores = NULL;
  int isType1;
  int isType2;
 
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
      mvprintw(w->upper_left_y,w->upper_left_x+40, "*** NEXT ***");
      state = ADD_PIECE;
	  start_color();//start color
      break;
    case ADD_PIECE:          // Add a new piece to the game
      if (next) {
	undisplay_tetromino(next);//remove previous "next" display
	current = next;

	next = create_tetromino ((w->upper_left_x+44), w->upper_left_y+1);//create a new next
	r = ( rand() % 6) + 1;
        next->color[0] = co+1;
        next->color[1] = r;
        next->color[2] = r;
        init_pair(co+1, next->color[1], next->color[2]);
      }
      else {
	current = create_tetromino ((w->upper_left_x+(w->width/2)), w->upper_left_y);
	r = ( rand() % 6) + 1;	
        current->color[0] = co;//assign color to color properties of tet
	current->color[1] = r;
	current->color[2] = r;
	init_pair(co, current->color[1], current->color[2]);

	next = create_tetromino ((w->upper_left_x+44), w->upper_left_y+1);
	r = ( rand() % 6) + 1;
	next->color[0] = co+1;
	next->color[1] = r;
	next->color[2] = r;	
	init_pair(co+1, next->color[1], next->color[2]);
      }
      move_tet(current, w->upper_left_x+(w->width/2), w->upper_left_y);//reset next to play field

      statusTry = move_tet(current,current->upper_left_x,current->upper_left_y+1);

      if(statusTry == MOVE_FAILED || current->upper_left_x == (w->upper_left_x+44)){//try to add a piece
      state = ENTER_NAME;//if can't add without collision, end game
      break;
      }
      else{
      statusTry = move_tet(current,current->upper_left_x,current->upper_left_y-1);//else undo move
      }
      attron(COLOR_PAIR(co));//turn on/off color
      display_tetromino(current);
      attroff(COLOR_PAIR(co));

      attron(COLOR_PAIR(co+1));
      display_tetromino(next);
      attroff(COLOR_PAIR(co+1));
      move_tet(next, w->upper_left_x+(w->width/2), w->upper_left_y);//reset next to play field
      r = (rand() % 500);

      isType1 = strcmp("u", current->type_str);
      isType2 = strcmp("x", current->type_str);

      if(isType1 == 0 || isType2 == 0){

		move_timeout = BASE_FALL_RATE-r;
	
	}
	else{
		move_timeout = BASE_FALL_RATE;
	}

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
	    state = ENTER_NAME;
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
	  lines_cleared += prune_well(w);//clear lines
	  score = compute_score(score, (lines_cleared));//calculate score
	  lines_cleared = 0;//reset lines cleared
	  state = ADD_PIECE;
	  co++;
	  move_timeout = BASE_FALL_RATE;
	}

        display_score(score, w->upper_left_x-15,w->upper_left_y);//display score every tick

	move_counter = 0;
      }
      if (time_c++ == 1000){//counter for seconds
	timec++;//if 1000ms, add 1 second to count
	display_time(timec, w->upper_left_x-15,w->upper_left_y+5);//update the time 
	time_c = 0;//reset tracker
	}
      if (time_out++ == 300000){//if 5 mins have passed

	state = ENTER_NAME;//end game

      }
      break;
    case ENTER_NAME:
	
      nodelay(stdscr,FALSE);
      clear();
      getmaxyx(stdscr,y,x);

      mvprintw(1,x/2-5,"  GAME_OVER  ");
      mvprintw(2,x/2-5,"#############");

      mvprintw(5,x/2-10,"Please Enter Your Initals: ");

      echo();
      mvgetstr(6, x/2, inita); 
      noecho();

      state = GAME_OVER;  
      break;
    case GAME_OVER:
      nodelay(stdscr,FALSE);
      clear();
      getmaxyx(stdscr,y,x);
      mvprintw(1,x/2-5,"  GAME_OVER  ");
      mvprintw(2,x/2-5,"#############");
      mvprintw(5,x/2-5,"    SCORE    ");
      mvprintw(6,x/2-5,"      %d     ", score);
      mvprintw(21,x/2-5,"Hit q to exit");
      mvprintw(8,x/2-5," HIGHSCORES  ");
      scores = load_scores("hs.txt");
      //scores = insert_score(scores, inita, score); //IF we use this, the user's score this game shows, but may not actually be inserted due to invalid length 
      print_score_list(scores, x/2-2, 10, 10);
      scores = insert_score(scores, inita, score); //If we use this, the user's current score will not show, but invalid entries will not show as well.
      store_scores("hs.txt", scores);
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
