#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


volatile int pixel_buffer_start; // global variable

int abs(int a);
void clear_screen();
void plot_pixel(int x, int y, short int line_color);
void swap(int * a, int * b);
void draw_line(int x0, int y0, int x1, int y1, short int color);
void wait_for_vsync();

int main(void)
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

    /* Rectangle Properties */
    int N = 20;
    int rectangle_X[N], rectangle_Y[N];
    int rectangle_dx[N], rectangle_dy[N];
    int rectangle_color[N];

    /* Coloring canvas */
    int color[8] = {0x001F, 0x07E0, 0xF800, 0xF81F, 0x001F, 0x07E0, 0xF800, 0xF81F};

    int i = 0;
    for(i = 0; i < N; i++){
        rectangle_dx[i] = rand() %2 * 2 - 1;
        rectangle_dy[i] = rand() %2 * 2 - 1;
        rectangle_color[i] = color[rand() % 8];
        rectangle_X[i] = rand() % 320;
        rectangle_Y[i] = rand() % 240;
    }

    while (1)
    {
        /* Erase any boxes and lines that were drawn in the last iteration */
        clear_screen();

        // code for drawing the boxes and lines
        for(i = 0; i < N; i++) {
			// draw connecting line 
            draw_line(rectangle_X[i], rectangle_Y[i], rectangle_X[(i+1)%N], rectangle_Y[(i+1)%N], rectangle_color[i]);
			
			// draw boxes
			plot_pixel(rectangle_X[i] - 1, rectangle_Y[i] - 1, 0xFFFFFFFF);
			plot_pixel(rectangle_X[i] - 1, rectangle_Y[i], 0xFFFFFFFF);
			plot_pixel(rectangle_X[i] - 1, rectangle_Y[i] + 1, 0xFFFFFFFF);
			plot_pixel(rectangle_X[i], rectangle_Y[i] - 1, 0xFFFFFFFF);
			plot_pixel(rectangle_X[i], rectangle_Y[i], 0xFFFFFFFF);
			plot_pixel(rectangle_X[i], rectangle_Y[i] + 1, 0xFFFFFFFF);
			plot_pixel(rectangle_X[i] + 1, rectangle_Y[i] - 1, 0xFFFFFFFF);
			plot_pixel(rectangle_X[i] + 1, rectangle_Y[i], 0xFFFFFFFF);
			plot_pixel(rectangle_X[i] + 1, rectangle_Y[i] + 1, 0xFFFFFFFF);
        }
		

		
		
		

        // code for updating the locations of boxes
        for(i = 0; i < N; i ++){

            if(rectangle_X[i] == 1) rectangle_dx[i] = 1;
            else if (rectangle_X[i] == 318) rectangle_dx[i] = -1;

            if(rectangle_Y[i] == 1) rectangle_dy[i] = 1;
            else if (rectangle_Y[i] == 238) rectangle_dy[i] = -1;

            rectangle_X[i] += rectangle_dx[i];
            rectangle_Y[i] += rectangle_dy[i];
        }

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    }
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