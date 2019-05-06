#include <stdbool.h>
#include <stdio.h>


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
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();

    int y = 0;
    int increment = 1;
    int y_erase_line = 239;
    while(1){

        draw_line(106, y, 213, y, 0xF800); // this line is red

        draw_line(0, y_erase_line, 319, y_erase_line, 0x0); // blank the previous line
        wait_for_vsync();

        if(y == 239) increment = -1;
        if(y == 0) increment = 1;

        y_erase_line = y;

        y = y + increment;

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