


#ifndef POINTS_H
#define POINTS_H


#include "defs.h"


typedef struct point_t point;


int get_X_From_Point(point * ponto);

int get_Y_From_Point(point * ponto);

size_t getSizeOfPoint(void);

size_t getSizeOfPointAst();

bool CheckHorseJump(point * ponto1, point * ponto2);

point * SetPoint(point * ponto, int x, int y);


#endif
