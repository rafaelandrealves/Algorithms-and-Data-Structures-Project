



#ifndef _MOVES_H
#define _MOVES_H

#include "tabuleiros.h"

typedef struct caminho_t caminho;
typedef struct Problema_t Problema;

tabuleiro getTabuleiro(Problema * turist);

caminho getCaminho(Problema * turist);

int getCustoTotal(Problema * turist);

int getNumPontos(Problema * turist);

bool CheckAllPoints(Problema * turist);

void Execute_B_Variant(Problema * turist, FILE * fp_out);

void Execute_A_Variant(Problema * turist, FILE * fp_out);

Problema * Alloc_Problema(int sizey, int sizex, char game_mode, int points_num);

void Aux_Set_Point(Problema * turist, int x, int y, int i);

void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx);

char GetModoJogo(Problema * turist);

void FreeAll(Problema * turista);

void PrintMainStruct(Problema * turista);

void movimentos(Problema *new);


#endif
