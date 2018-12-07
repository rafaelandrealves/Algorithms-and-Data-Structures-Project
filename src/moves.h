



#ifndef _MOVES_H
#define _MOVES_H

#include "defs.h"
#include "tabuleiros.h"

typedef struct caminho_t caminho;
typedef struct Problema_t Problema;

tabuleiro * getTabuleiro(Problema * turist);

caminho * getCaminho(Problema * turist);

int getCustoTotalFromProb(Problema * turist);

int getCustoTotalFromCaminho(caminho * way);

int getNumPontos(Problema * turist);

point getIpoint(Problema * turist, int i);

point getIpointFromCaminho(caminho * way, int i);

point * get_point_vector(caminho * move);

caminho * Set_Custo_Total(caminho *move, int value);

void permutacao_recursiva(int * vetor, int ** matriz, int k, int num_ele, int *num_linha);

void troca_int(int * str, int p1, int p2);

void SetMatrix_Variant_C(int ** matriz, int * vetor, int num_ele, int num_linha);

void Free_Matrix_Variant_C(int ** matrix, int num_pontos);

bool CheckAllPoints(Problema * turist);

void Execute_B_Variant(Problema * turist, FILE * fp_out);

void Execute_A_Variant(Problema * turist, FILE * fp_out);

void Execute_C_Variant(Problema * turist, FILE * fp_out);

void Aux_Set_Point(Problema * turist, int i, int x, int y);

Problema * Alloc_Problema(int sizey, int sizex, char game_mode, int points_num);

void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx);

char GetModoJogo(Problema * turist);

void FreeAll(Problema * turista);

void PrintMainStruct(Problema * turista);

void WriteFileWithFailure(Problema * turist, FILE * fp_out);

void WriteFileWithSuccess(Problema * turist, FILE * fp_out);

void Free_Point_Vec(int num, caminho * move_struct);


#endif
