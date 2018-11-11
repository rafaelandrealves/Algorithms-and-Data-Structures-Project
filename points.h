

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>



int get_X_From_Point(point ponto);

int get_Y_From_Point(point ponto);
void MovesLowRight( UNICODE *new , int xmax , int ymax , int x, int y , int jog[8]);
void MovesLowLeft( UNICODE *new , int xmax , int ymax , int x, int y, int jog[8]);
void MovesHigh( UNICODE *new , int xmax , int ymax , int x, int y , int jog[8]);
void MovesLow( UNICODE *new , int xmax , int ymax , int x, int y, int jog[8]);
void movimentos(UNICODE *new, int jog[8]);
int  analisa_jogadas(UNICODE *new, int jog[8]);

