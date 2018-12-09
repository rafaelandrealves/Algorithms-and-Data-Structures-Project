



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

void caminhos_recursiva(int * vetor, Problema * turist, int k, caminho ** Path_Matrix, caminho * best, bool * first_time, caminho * atual, caminho * move_to_save);

void troca_int(int * str, int p1, int p2);

void SetMatrix_Variant_C(char ** matriz, int * vetor, int num_ele, int num_linha);

void Free_Matrix_Variant_C(char ** matrix, int num_pontos);

bool CheckAllPoints(Problema * turist);

void Execute_B_Variant(Problema * turist, FILE * fp_out);

void Execute_A_Variant(Problema * turist, FILE * fp_out);

void C_for_one_path(Problema * turist, int * comb_vector, caminho ** Path_matrix, bool * first_time, caminho * best, caminho * atual, caminho * move_to_save);

caminho ** INIT_Path_Matrix(int number_of_points);

void Use_Caminho_PreCalculated(caminho insert, caminho *old, int points_to_insert);

void Insert_Reverse_Move(caminho * to_go, caminho ** caminho_path_matrix, int cost_final_to_go, int cost_inicial_to_go, point inicial_point_to_go, int init_pos, int dest_pos);

void Insert_CaminhoInMatrix(caminho ** move_matrix, caminho * to_insert, int origin, int destiny);

void Clean_caminho(caminho * move);

void Execute_C_Variant(Problema * turist, FILE * fp_out);

void Copy_Caminho(point * path, caminho * best);

void Aux_Set_Point(Problema * turist, int i, int x, int y);

Problema * Alloc_Problema(int sizey, int sizex, char game_mode, int points_num);

void Aux_Set_Matrix_Element(Problema * turist, short cost, int yy, int xx);

char GetModoJogo(Problema * turist);

void FreeAll(Problema * turista);

void PrintMainStruct(Problema * turista);

void WriteFileWithFailure(Problema * turist, FILE * fp_out);

void WriteFileWithSuccess(Problema * turist, FILE * fp_out);

void Free_Point_Vec(int num, caminho * move_struct);

void Free_INIT_Path_Matrix(caminho ** Path_Matrix, int num_points);

#endif
