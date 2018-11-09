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



// função para ler o ficheiro e colocar a informação na estrutura WAY
UNICODE * Read_File(FILE * fp);
char * OutPutFileName(char * nome_inicial);
int analisa_ficheiro(FILE *file);


#endif