

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

void DijkstraAlgoritm(Problema * turist,FILE * fp_out, point * begin, point *end, int *custo_total_acumulado,int *index,int *ponto_atual, point ** vect_out, int num_pontos);

void get_Move_Vector_A(DijkMatrix matrix, point * end, point * ORIGIN, Problema * turist, FILE * fp_out);

void OutPUT_B(DijkMatrix matrix, point * end, point * ORIGIN, Problema * turist, FILE * fp_out, int num, point ** vect, int custo_acumulado);

void get_Move_Vector_B(DijkMatrix matrix, point * end, point * ORIGIN, int *index, point ** vect);
#endif
