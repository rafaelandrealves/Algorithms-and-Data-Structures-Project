

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "defs.h"
#include "moves.h"

typedef struct Dijk_struct Dijk;

typedef Dijk ** DijkMatrix;

int get_Acum_Cost(DijkMatrix aux, point * point);

Dijk ** AllocDijk(int ysize, int xsize);

DijkMatrix Problema2Dijk(Problema * turist);

point ** Possible_Jump_Points(tabuleiro * tab, point * ponto, DijkMatrix aux);

void Free_Possible_Jump_Points(point ** vect);

void DijkstraAlgoritm(Problema * turist,char * argv,FILE * fp_out);

void get_Move_Vector(DijkMatrix matrix, point * end, point * ORIGIN, Problema * turist, FILE * fp_out);


#endif
