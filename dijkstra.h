

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

void DijkstraAlgoritm(Problema * turist);



#endif
