



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

point * getIpoint(Problema * turist, int i);

point * getIpointFromCaminho(caminho * way, int i);

point ** get_point_vector(caminho * move);

caminho * Set_Custo_Total(caminho *move, int value);

bool CheckAllPoints(Problema * turist);

void Execute_B_Variant(Problema * turist, FILE * fp_out);

void Execute_A_Variant(Problema * turist, FILE * fp_out);

void Execute_C_Variant(Problema * turist, FILE * fp_out);

Problema * Alloc_Problema(int sizey, int sizex, char game_mode, int points_num);

void Aux_Set_Point(Problema * turist, int x, int y, int i);

void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx);

char GetModoJogo(Problema * turist);

void FreeAll(Problema * turista);

void PrintMainStruct(Problema * turista);

void movimentos(Problema *new);

void WriteFileWithFailure(Problema * turist, FILE * fp_out);

void WriteFileWithSuccess(Problema * turist, FILE * fp_out);

void movimentos_num_ponto(Problema * new, int xmax, int ymax, int x , int y , char condicao);


#endif
