
/******************************************************************************
 *
 * File Name: dijkstra.h

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  11 Dez 2018
 *
 * NAME
 *     dijkstra.h - Headers of Dijkstra.c
 *
*/

#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "defs.h"
#include "moves.h"

typedef struct Dijk_struct Dijk;

typedef Dijk ** DijkMatrix;

int get_Acum_Cost(DijkMatrix matrix, point ponto);

point get_Father(DijkMatrix matrix, point ponto);

DijkMatrix AllocDijk(int ysize, int xsize);

void FreeDijk(DijkMatrix matrix, int ysize, int xsize);

DijkMatrix Problema2Dijk(Problema * turist);

point * Possible_Jump_Points(tabuleiro * tab, point ponto, DijkMatrix aux);

void get_Move_Vector_A(DijkMatrix matrix, point end, point ORIGIN, Problema * turist, FILE * fp_out);

void get_Move_Vector_B(DijkMatrix matrix, point end, point ORIGIN, int *num_pontos, point * vect);

void OutPUT_B(Problema * turist, FILE * fp_out, int num_pontos, caminho * atual);

void DijkstraAlgoritm_A(Problema * turist,FILE * fp_out, point begin, point end);

void DijkstraAlgoritm_B(Problema * turist, FILE * fp_out, point begin, point end, int *num_pontos, int *ponto_atual, caminho * atual);

int get_Move_Vector_C(DijkMatrix matrix, point end, point ORIGIN, point * for_one_step);

void DijkstraAlgoritm_C(Problema * turist, point begin, point end, caminho *momentum, int *number_points, bool * No_Path);

void OutPUT_C(Problema * turist, FILE * fp_out, caminho ** best);

// int get_Acum_Cost(DijkMatrix aux, point point);
//
// point get_Father(DijkMatrix aux, point ponto);
//
// Dijk ** AllocDijk(int ysize, int xsize);
//
// point * GetDupPoint(point *ponto);
//
// DijkMatrix Problema2Dijk(Problema * turist);
//
// point * Possible_Jump_Points(tabuleiro * tab, point ponto, DijkMatrix aux);
//
// void DijkstraAlgoritm_A(Problema * turist,FILE * fp_out, point begin, point end);
//
// void DijkstraAlgoritm_B(Problema * turist,FILE * fp_out, point begin, point end, int *index, int *ponto_atual, caminho * move_vect);
//
// void DijkstraAlgoritm_C(Problema * turist, point begin, point end,caminho *momentum,int *cost_from_point, bool * No_Path);
//
// void get_Move_Vector_A(DijkMatrix matrix, point end, point ORIGIN, Problema * turist, FILE * fp_out);
//
// void OutPUT_B(Problema * turist, FILE * fp_out, int num_pontos, caminho * atual);
//
// void get_Move_Vector_B(DijkMatrix matrix, point end, point ORIGIN, int *index, point * vect);
//
// void OutPUT_C(Problema * turist, FILE * fp_out, caminho ** move_struct);
//
// int get_Move_Vector_C(DijkMatrix matrix, point end, point ORIGIN, point * vect);


#endif
