/******************************************************************************
 *
 * File Name: leitura_fich.h

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  27 Oct 2018
 *
 * NAME
 *     leitura_fich.h - Implementation of reading file functions
 *
*/

#ifndef TABULEIROS_H
#define TABULEIROS_H


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "points.h"


typedef struct tabuleiro_t tabuleiro;


// função para ler o ficheiro e colocar a informação na estrutura WAY

int getXSize(tabuleiro table);

int getYSize(tabuleiro table);

bool check_Point_Inside_Table(tabuleiro table, point ponto);

int GetPointCost(tabuleiro table, point ponto);

int GetPointCostFromCoord(tabuleiro table, int yy, int xx);

void WriteFileWithFailure(Problema * turist, FILE * fp_out);

void WriteFileWithSuccess(Problema * turist, FILE * fp_out);

tabuleiro * Set_Lenght_Width(tabuleiro * table, int sizey, int sizex);

void SetMatrixElement(tabuleiro * table, short cost, int yy, int xx);


#endif
