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




// função para ler o ficheiro e colocar a informação na estrutura WAY
UNICODE * Read_File(FILE * fp, bool *end_of_file);

int analisa_ficheiro(FILE *file);

bool check_Point_Inside_Table(tabuleiro table, point ponto);

int GetPointCost(tabuleiro table, point ponto);

void WriteFileWithFailure(UNICODE * turist, FILE * fp_out);

void WriteFileWithSuccess(UNICODE * turist, FILE * fp_out);


#endif
