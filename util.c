/******************************************************************************
 *
 * File Name: util.c
 
 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  27 Oct 2018
 *
 * NAME
 *     util.c - Implementation of utilitary functions to alloc memory, open files, etc
 *
*/




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "util.h"
#include "defs.h"
#include "tabuleiros.h"


void * Checked_Malloc(size_t size)
{
    void * mem = malloc(size);
    if(mem == NULL)
    {
        printf("Error alocating memory. Exiting\n");
        exit(2);
    }
    return mem;
}


FILE * Open_File(char * file_name, char * mode)
{
    FILE * fp = NULL;

    fp = fopen(file_name, mode);
    if(fp == NULL)
    {
        printf("Error opening file %s. Exiting.\n", file_name);
        exit(2);
    }
    return fp;
}


FILE * checkArguments(int _argc, char ** _argv)
{
    char * tok=NULL;
    if(_argc>2){
        printf("ERRO NUMERO ELEVADO DE ELEMENTOS");
        exit(1);
    }    

    if(strstr(_argv[1],".cities")==NULL)
    {
        printf("ERROR-HAS TO BE A .cities file");
        exit (1);
    }
    tok = strtok(_argv[1],".");
    tok = strtok(NULL, "\0");
    if( strcmp(tok,"cities") != 0 ){
        printf("ERROR, TRYING THAT DOESNT WORK");
        exit(1);
    }

    return Open_File(_argv[1], "r");
}

void FreeAll(UNICODE * turista)
{
    free(turista->passadeira_vermelha.points);

    for(int i = 0; i < turista->tabu.size_x)
        free(turista->tabu.tab[i]);

    free(turista->tabu.tab);
}

