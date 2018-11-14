

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "moves.h"

#ifndef POINTS_H
#define POINTS_H

typedef struct point_t point;


int get_X_From_Point(point ponto);

int get_Y_From_Point(point ponto);

void movimentos_num_ponto(Problema * new, int xmax, int ymax, int x , int y , char condicao, int *soma_min);

bool CheckHorseJump(point ponto1, point ponto2);



#endif
