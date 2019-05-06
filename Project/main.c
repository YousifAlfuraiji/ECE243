
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

volatile int pixel_buffer_start; // global variable
 volatile short * pixelbuf = 0xc8000000;
extern short MYIMAGE [240][320];

int abs(int a);
void clear_screen();
void plot_pixel(int x, int y, short int line_color);
void swap(int * a, int * b);
void draw_line(int x0, int y0, int x1, int y1, short int color);
void wait_for_vsync();
void draw_rectangle(int x0, int x1, int y0, int y1, int color);

struct Ball {
 int x;
 int y;
 int dx;
 int dy;
};
struct Player{
 int x;
 int y;
 int score;
};
void draw_zero(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0 + 2, x0 + 3, y0 + 2, y0 + 7, 0x0);
 
}
void draw_one(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0, x0 + 3, y0, y0 + 9, 0x0);
 
}
void draw_two(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0, x0 + 3, y0 + 2, y0 + 3, 0x0);
 
 draw_rectangle(x0 + 2, x0 + 5, y0 + 6, y0 + 7, 0x0);
}
void draw_three(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0, x0 + 3, y0 + 2, y0 + 3, 0x0);
 
 draw_rectangle(x0, x0 + 3, y0 + 6, y0 + 7, 0x0);
}
void draw_four(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0 + 2, x0 + 3, y0, y0 + 3, 0x0);
 
 draw_rectangle(x0, x0 + 3, y0 + 6, y0 + 9, 0x0);
}
void draw_five(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0 + 2, x0 + 5, y0 + 2, y0 + 3, 0x0);
 
 draw_rectangle(x0, x0 + 3, y0 + 6, y0 + 7, 0x0);
 
 
}
void draw_six(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0 + 2, x0 + 5, y0, y0 + 3, 0x0);
 
 draw_rectangle(x0 + 2, x0 + 3, y0 + 6, y0 + 7, 0x0);
 
}
void draw_seven(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0, x0 + 3, y0 + 2, y0 + 9, 0x0);
 
}

void draw_eight(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0 + 2, x0 + 3, y0 + 2, y0 + 3, 0x0);
 
 draw_rectangle(x0 + 2, x0 + 3, y0 + 6, y0 + 7, 0x0);
 
}
void draw_nine(int x0, int y0){
 
 draw_rectangle(x0, x0 + 5, y0, y0 + 9, 0xFFFFFFFF);
 
 draw_rectangle(x0 + 2, x0 + 3, y0 + 2, y0 + 3, 0x0);
 
 draw_rectangle(x0, x0 + 3, y0 + 6, y0 + 9, 0x0);
 
}

void draw_score_player1(int score){
 
 int x = 150;
 int y = 50;
 
 switch(score){
 
  case 0:
  draw_zero(x, y);
  break;
 
  case 1:
  draw_one(x, y);
  break;
 
  case 2:
  draw_two(x, y);
  break;
 
  case 3:
  draw_three(x, y);
  break;
 
  case 4:
  draw_four(x, y);
  break;
 
  case 5:
  draw_five(x, y);
  break;
 
  case 6:
  draw_six(x, y);
  break;
 
  case 7:
  draw_seven(x, y);
  break;
 
  case 8:
  draw_eight(x, y);
  break;
 
  case 9:
  draw_nine(x, y);
  break;
 
 }
}
void draw_score_player2(int score){
 
 int x = 170;
 int y = 50;
 
 switch(score){
 
  case 0:
  draw_zero(x, y);
  break;
 
  case 1:
  draw_one(x, y);
  break;
 
  case 2:
  draw_two(x, y);
  break;
 
  case 3:
  draw_three(x, y);
  break;
 
  case 4:
  draw_four(x, y);
  break;
 
  case 5:
  draw_five(x, y);
  break;
 
  case 6:
  draw_six(x, y);
  break;
 
  case 7:
  draw_seven(x, y);
  break;
 
  case 8:
  draw_eight(x, y);
  break;
 
  case 9:
  draw_nine(x, y);
  break;
 
 }
}

void game()
{
 
 
 
	volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
	// declare other variables(not shown)
	// initialize location and direction of rectangles(not shown)
	/* set front pixel buffer to start of FPGA On-chip memory */
	*(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the
	// back buffer
	/* now, swap the front/back buffers, to set the front buffer location */
	wait_for_vsync();
	/* initialize a pointer to the pixel buffer, used by drawing functions */
	pixel_buffer_start = *pixel_ctrl_ptr;
	clear_screen(); // pixel_buffer_start points to the pixel buffer
	/* set back pixel buffer to start of SDRAM memory */
	*(pixel_ctrl_ptr + 1) = 0xC0000000;
	pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer

	// Take in the key values
	volatile int *key_ptr = 0xff200050;
	volatile int *sw_ptr = 0xff200040;

	/* Coloring canvas */
	//int color[8] = {0x001F, 0x07E0, 0xF800, 0xF81F, 0x001F, 0x07E0, 0xF800, 0xF81F};
 int color = 0x0;
	/* Make the balls */
	int ballNum = 4;
 struct Ball ball [ballNum];

	int i = 0;
	for(i = 0; i < ballNum; i++){
 
  ball[i].dx = rand() %2 * 2 - 1;
  ball[i].dy = rand() %2 * 2 - 1;
  //ball[i].color = color[rand() % 8];
  //ball[i].x = rand() % 320;
  //ball[i].y = rand() % 240;
	ball[i].x = 319/2 - rand() %4 * 2;
	ball[i].y = 239/2 - rand() %4 * 2;
 
	}
 
	int ball_radius = 2;

	/* Make the players */
 struct Player player1;
 struct Player player2;
 player1.x = 320/10;
 player2.x = 320 - 320/10;
 player1.y = 240/2;
 player2.y = 240/2;
 player1.score = 0;
 player2.score = 0;
 
	int players_width = 5;
	int players_height = 240 / 5;

	while (player2.score < 10 && player1.score < 10)
	{
  
  
  
  
    	/* Erase any boxes and lines that were drawn in the last iteration */
    	clear_screen();
  /* Keys to move each player */
  // Player can only move if the right button is pressed and they are within screen bounds
    	if( (*key_ptr & 1) == 1 && player1.y + players_height/2 < 239) player1.y = player1.y + 2;
  if( (*key_ptr & 2) == 2 && player1.y - players_height/2 > 0) player1.y = player1.y - 2;
  if( (*key_ptr & 4) == 4 && player2.y + players_height/2 < 239) player2.y = player2.y + 2;
  if( (*key_ptr & 8) == 8 && player2.y - players_height/2 > 0) player2.y = player2.y - 2;
  color = rand() % 0xFFFFFFFF;
  //color = 0x00FFFF00;
 
    	// Draw ballz
    	for(i = 0; i < ballNum; i++) {
   draw_rectangle(ball[i].x - ball_radius, ball[i].x + ball_radius,
   	ball[i].y - ball_radius, ball[i].y + ball_radius,
   	color);
    	}
    	// Draw player 1
  draw_rectangle(player1.x - players_width / 2, player1.x + players_width / 2,
                    	player1.y - players_height / 2, player1.y + players_height / 2,
                   	color);

    	// Draw player 2
  draw_rectangle(player2.x - players_width / 2, player2.x + players_width / 2,
                   	player2.y - players_height / 2, player2.y + players_height / 2,
                   	color);
    	
  // Draw the score
  draw_score_player2(player2.score);
  draw_score_player1(player1.score);
 
  // Checking if a score is made
  for(i = 0; i < ballNum; i++){
   if(ball[i].x == 0 + ball_radius){
	player2.score++;
	ball[i].x = 319/2 - rand() %4 * 2;
	ball[i].y = 239/2 - rand() %4 * 2;
	ball[i].dx = rand() %2 * 2 - 1;
	ball[i].dy = rand() %2 * 2 - 1;
   }
   else if(ball[i].x == 319 - ball_radius) {
	player1.score++;
	ball[i].x = 319/2 - rand() %4 * 2;
	ball[i].y = 239/2 - rand() %4 * 2;
	ball[i].dx = rand() %2 * 2 - 1;
	ball[i].dy = rand() %2 * 2 - 1;
   }
  }
    	
    	// Updating the locations of the ball
    	for(i = 0; i < ballNum; i ++){
   if( /*(ball[i].x == 0 + ball_radius)
	||*/ (ball[i].x == player1.x + players_width/2 + ball_radius && (ball[i].y <= player1.y + players_height/2 && ball[i].y >= player1.y - players_height/2) )
	|| (ball[i].x == player2.x + players_width/2 + ball_radius && (ball[i].y <= player2.y + players_height/2 && ball[i].y >= player2.y - players_height/2) ) ) {
 	
 	ball[i].dx = 1;
 	
   }
   else if( /*(ball[i].x == 319 - ball_radius)
	||*/ (ball[i].x == player1.x - players_width/2 - ball_radius && (ball[i].y <= player1.y + players_height/2 && ball[i].y >= player1.y - players_height/2) )
	|| (ball[i].x == player2.x - players_width/2 - ball_radius && (ball[i].y <= player2.y + players_height/2 && ball[i].y >= player2.y - players_height/2) ) ) {
 	
 	ball[i].dx = -1;
 	
   }
	
        	if(ball[i].y <= 0 + ball_radius /*+ ball[i].y /2*/
	|| (ball[i].y == player1.y + players_height/2 + ball_radius && (ball[i].x <= player1.x + players_width/2 && ball[i].x >= player1.x - players_width/2) )
	|| (ball[i].y == player2.y + players_height/2 + ball_radius && (ball[i].x <= player2.x + players_width/2 && ball[i].x >= player2.x - players_width/2) ) ) {
	
	ball[i].dy = 1;
	
   }
        	else if (ball[i].y >= 239 - ball_radius /*- ball[i].y /2*/
	|| (ball[i].y == player1.y - players_height/2 - ball_radius && (ball[i].x <= player1.x + players_width/2 && ball[i].x >= player1.x - players_width/2) )
	|| (ball[i].y == player2.y - players_height/2 - ball_radius && (ball[i].x <= player2.x + players_width/2 && ball[i].x >= player2.x - players_width/2) ) ) {
 	
 	ball[i].dy = -1;
   } 	
 
 
 
 
   ball[i].x += ball[i].dx;
   ball[i].y += ball[i].dy;
    	}
  
  

    	wait_for_vsync(); // swap front and back buffers on VGA vertical sync
    	pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
  
  
         

	}
 
 
 //clear_screen();
 wait_for_vsync();
	pixel_buffer_start = *(pixel_ctrl_ptr + 1);
	int k, m;
	for (k=0; k<240; k++){
    	for (m=0; m<320; m++)
   *( (short int *)pixel_buffer_start + (m<<0) + (k<<9)) = MYIMAGE[k][m];
  //*(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
 }
 wait_for_vsync();
	
 while( (*key_ptr & 1) != 1);
 while( (*key_ptr & 1) != 0);
	
}

int main(void)
{
 
 while(1){
  
  game();
  //volatile int *key_ptr = 0xff200050;
  //while( (*key_ptr & 1) != 1);
  
  
 }
 
 return 0;
 
}
//clear screen
void clear_screen(){
	int x = 0, y = 0;

	for(x = 0; x < 320; x++){
    	for(y = 0; y < 240; y++){
        	plot_pixel(x, y, 0x0);
    	}
	}
}

int abs(int a){
	if( a < 0) return a*-1;
	return a;
}

void swap(int * a, int * b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

// draw_line()

void draw_line(int x0, int y0, int x1, int y1, short int color) {
	bool isSteep = false;

	if(abs(y1 - y0) > abs(x1 - x0)){
    	isSteep = true;
	}

	if(isSteep == true ){
    	swap(&x0, &y0);
    	swap(&x1, &y1);
	}

	if(x0 > x1) {
    	swap(&x0, &x1);
    	swap(&y0, &y1);
	}

	int deltaX = x1 - x0;
	int deltaY = abs(y1 - y0);

	int error = -(deltaX/2);
	int y_step = y0 < y1 ? 1 : -1;

	int y = y0;
	int x = x0;

	for(x = x0; x <= x1; x++){
    	if(isSteep == true) plot_pixel(y, x, color);
    	else plot_pixel(x, y, color);

    	error = error + deltaY;

    	if(error>=0){
        	y = y + y_step;
        	error = error - deltaX;
    	}
	}
}

// code not shown for clear_screen() and draw_line() subroutines

void plot_pixel(int x, int y, short int line_color)
{
	*(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void wait_for_vsync() {
	volatile int * pixel_ctrl_ptr = 0xFF203020; // pixel controller
	register int status;

	*pixel_ctrl_ptr = 1; // start the synchronization process

	status = *(pixel_ctrl_ptr + 3);
	while ((status & 0x01) != 0) {
    	status = *(pixel_ctrl_ptr + 3);
	}
}

void draw_rectangle(int x0, int x1, int y0, int y1, int color) {
	int x, y;

	for(x = x0; x <= x1; x++) {
    	for(y = y0; y <= y1; y++) {
        	plot_pixel(x, y, color);
    	}
	}
}





