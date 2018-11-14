

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


#ifndef POINTS_H
#define POINTS_H

int get_X_From_Point(point ponto);

int get_Y_From_Point(point ponto);
int analisa_pontos(UNICODE *new);
void movimentos(UNICODE *new, int *soma_min);
//int  analisa_jogadas(UNICODE *new, int jog[8]);
void movimentos_num_ponto(UNICODE *new,int xmax, int ymax, int x , int y , char condicao, int *soma_min);


#endif
