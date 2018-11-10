

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>



int get_X_From_Point(point ponto);

int get_Y_From_Point(point ponto);
int MovesLowRight( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido );
int MovesLowLeft( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido );
int MovesHigh( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido );
int MovesLow( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido  );

