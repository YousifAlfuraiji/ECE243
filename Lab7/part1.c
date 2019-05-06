#define true 1
#define false 0
typedef int bool;

volatile int pixel_buffer_start; // global variable

int abs(int a);
void clear_screen();
void plot_pixel(int x, int y, short int line_color);
void swap(int * a, int * b);
void draw_line(int x0, int y0, int x1, int y1, short int color);

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();
    draw_line(0, 0, 150, 150, 0x001F);   // this line is blue
    draw_line(150, 150, 319, 0, 0x07E0); // this line is green
    draw_line(0, 239, 319, 239, 0xF800); // this line is red
    draw_line(319, 0, 0, 239, 0xF81F);   // this line is a pink color
	while(1){}
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
