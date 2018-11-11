

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>



int get_X_From_Point(point ponto);

int get_Y_From_Point(point ponto);
void MovesLowRight( UNICODE *new , int xmax , int ymax , int x, int y  );
void MovesLowLeft( UNICODE *new , int xmax , int ymax , int x, int y  );
void MovesHigh( UNICODE *new , int xmax , int ymax , int x, int y );
void MovesLow( UNICODE *new , int xmax , int ymax , int x, int y );
void movimentos(UNICODE *new);
int  analisa_jogadas(UNICODE *new);

