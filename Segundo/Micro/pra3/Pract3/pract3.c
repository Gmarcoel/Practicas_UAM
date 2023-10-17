/*********************************************************************
 * pract3a.c
 *
 * Microprocessor-Based Systems
 * 2020-2021
 * Laboratory Assignment 3
 * Painting geometrical figures
 * ddga
 *
 *********************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXCOL 640
#define MAXROW 480

#define MAXPOINTS 400

#define OK 0
#define ERR -1

/***** Functions declaration *****/

/*------------------------------- Task 1 ---------------------------------*/
/*******************************************************************************
* Name: drawPixel
* 
* Aim: move to video mode and draw a pixel of colour COLOUR into the screen
*				 position fixed by X and Y
* Inputs parameters:
* 				- unsigned char COLOUR : pixel's colour
*				- unsigned char X : row position on the screen
*				- unsigned char Y : column position on the screen
* Returning values:
*				-  char: -1 if position is outside the range; 0 if it is ok 
******************************************************************************/
char drawPixel(unsigned char colour, int x, int y);


/*********************************************************************************
* Name: drawSquare
* 
* Aim: move to video mode, draw a COLOUR pixel in the screen position 
*      detailed by X and Y
* Input parameters:
* 				- unsigned char COLOUR
*				- int size; length of every side of the square (in pixels).
*				- int X; row position on the screen
*				- int Y; column position on the screen
* Returning values:
*				- char: -1 if position is out of range.
					   0 if it is ok.
*******************************************************************************/
char drawSquare(unsigned char colour, int size, int x, int y);


/*------------------------------- Ejercicio 2 ---------------------------------*/

/*******************************************************************************
* Name: drawPixelsList
* 
* Aim: draw on the screen all the pixes given in input vectors in positions X and Y
* Input parameters:
* 				- unsigned int numPixeles: total elements in the input vector
* 				- unsigned char bgcolour: background colour
* 				- long int waitingTime: waiting time in milliseconds after any drawing
*				- int* pixelList_x : pointer to the array of X positions (rows) on the screen
*				- int* pixelList_y : pointer to the array of Y positions (columns) on the screen
*				- unsigned char* pixelList_colour : pointer to the array of colours of every single pixel
* Valores retorno:
*				-  no return value
******************************************************************************/
void drawPixelsList(unsigned int numPixeles, unsigned char bgcolour, 
						long int waitingTime, int* pixelList_x, int* pixelList_y,
						unsigned char* pixelList_colour); 


//////////////////////////////////////////////////////////////////////////
///// -------------------------- MAIN ------------------------------ /////
//////////////////////////////////////////////////////////////////////////
int main( void ){
	// Variable declaration
	unsigned char option = 'e';
	unsigned char op_mov = 1;
	int pos_x = 0, pos_y = 0, size = 0;
	unsigned int num_pix_array = 1;
	int i = 1;
	char ret = 2;

	unsigned char colour = 15, background_colour = 2;
	long int waitMS = 6000000;
	//int ArrayPixelsX[MAXPOINTS]={11,12,13,14,15,16,17,18,19,20,100}, ArrayPixelsY[MAXPOINTS]={21,22,23,24,25,26,27,28,29,30,31}; //ArrayPixeles[0] = X, ArrayPixeles[1] = Y
	//unsigned char ArrayColours[MAXPOINTS]={1,2,3,4,5,6,7,8,9,10,11};
	int ArrayPixelsX[MAXPOINTS]={0}, ArrayPixelsY[MAXPOINTS]={0}; 
	unsigned char ArrayColours[MAXPOINTS]={0};
	
	//Print instructions to the users
	printf("General instructions:\n");
	printf(" - Video mode is set to 640x480 screens\n");
	printf(" - X position must be in range [0, 640]\n");
	printf(" - Y position must be in range [0, 480]\n");
	printf(" - Colour must be in range from 0 to 15\n\n");
	
	
	//Ask the user for a choice
	printf("Choose the option you want to test: \n");
	printf("a - Draw 1 pixel \n");
	printf("b - Draw 1 square  \n");
	printf("c - Draw several pixels \n");
	printf("d - Draw and move one square \n");
	scanf("%c", &option);
	
	//Comprueba es una opcion valida del menu
	if (option >= 'a' && option <= 'd'){
		printf("-Option chosen --> %c -\n",option);
	}else{
		printf("-Option %c: incorrect. Outside from [a,b,c,d]\n Bye\n",option);
		return ERR;
	}
	
	//Depending of the chosen option we execute in assembler one function or another
	switch(option){
		
		
		//draw a pixel
		case 'a': 
				printf("Introduce X and Y position next to the colour separated by spaces (i.e. 40 50 2): \n");
				scanf("%d %d %u", &pos_x, &pos_y, &colour);
				ret = drawPixel(colour,pos_x, pos_y); //CALLS the assembler function
				if(ret == ERR)
					printf("Pixel position outside of the range 640x480\n");
				break;
				
				
		//Option drawSquare
		case 'b': 
				printf("Introduce X and Y position next to the size and colour separated by spaces\n(e.g. 40 50 10 2): \n");
				scanf("%d %d %d %u", &pos_x, &pos_y, &size, &colour);
				ret = drawSquare(colour, size, pos_x, pos_y);  //CALLS the assembler function
				//printf("Pixel %d %d %d %d %u\n",pos_x,pos_y,tam,size,colour);
				if(ret == ERR)
					printf("Pixel position outside of the range 640x480\n");
				break;	
				
				
		//Option to draw a list of pixels (it could be used to draw a text file with a image)
		case 'c': 
				printf("From 1 to %d, how many pixels do you want to draw?\n", MAXPOINTS);
				scanf("%ud", &num_pix_array);
				if(num_pix_array > MAXPOINTS){
					printf("Error: Number of elements is greater than allowed\n");
					break;
				}
				for(i=0;i<num_pix_array;i++){
					//printf("%d. ",i+1);
					ArrayPixelsX[i] = i+11;
					ArrayPixelsY[i] = sen(ArrayPixelsX[i]) + cos(ArrayPixelsX[i])/*(i+21)*/; /*(3x/2)4 + (3x)4 + z4 = 1*/
					ArrayColours[i] = i % 16;
					printf("%d %d %d\n", ArrayPixelsX[i], ArrayPixelsY[i], ArrayColours[i]);
					printf("%d %d %d\n", ArrayPixelsX, ArrayPixelsY, ArrayColours);
				}
				printf("Introduce the background colour (value from 0 to 15): \n");
				scanf("%u", &background_colour);
				// CALLS the assembler function to draw the pixels vector
				drawPixelsList(num_pix_array, background_colour, waitMS, ArrayPixelsX, ArrayPixelsY, ArrayColours);   
				break;	
								
		//Option draw and move a square
		case 'd': 
				printf("Instructions: When a movement is asked, use arrows from numeric keyboard to move the square\n");
				printf("       8      \n");
				printf("       ^      \n");
				printf("       |      \n");
				printf("4 <--- * ---> 6\n");
				printf("       |      \n");
				printf("       v      \n");
				printf("       2      \n\n");
				printf("0 zero for exit\n");
				printf("Introduce X and Y position next to the size and colour separated by spaces\n(e.g. 40 50 10 2): \n");
				scanf("%d %d %d %u", &pos_x, &pos_y, &size, &colour);
				if(ret == ERR){
					printf("Pixel position outside of the range 640x480\n");
					break;
				}else{
					// DO-WHILE Loop to move the square throught the screen
					do{
						ret = drawSquare(colour,size, pos_x, pos_y);  //CALLS the assembler function
						//printf("%u: %u,%u\n",ret, pos_x,pos_y);
						
						printf("Make your move (zero for exit)\n               ");
						scanf("%c", &op_mov);
						//printf("\n");
						switch(op_mov){
							//left
							case '4': 
									if(pos_x > (0+size))
										pos_x = pos_x - size;
									else pos_x = MAXCOL-1-size;
									printf("Case 4 - %c\n",op_mov);
									break;
							
							//up
							case '8': 
									if(pos_y>(0+size))
										pos_y = pos_y - size;
									else pos_y = MAXROW-1-size;
									printf("Case 8 - %c\n",op_mov);
									break;
							
							//right
							case '6': 
									if(pos_x<(MAXCOL-1-size))
										pos_x += size;
									else pos_x = 0+size;
									printf("Case 6 - %c\n",op_mov);
									break;
							
							//down						
							case '2': 
									if(pos_y<(MAXROW-1-size))
										pos_y += size;
									else pos_y = 0+size;
									printf("Case 2 - %c\n",op_mov);
							
							default: break;
											
						}// ends of switch(op_mov)
						
					}while(op_mov != '0'); //ends of do-while loop for movement
					
				} // ends of switch (
								
		default: break;
							
	} // ends of switch(option)
	
	return OK;
}