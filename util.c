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

#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"


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
        printf("rfrError opening file %s. Exiting.\n", file_name);
        exit(2);
    }
    return fp;
}


FILE * checkArguments(int _argc, char ** _argv)
{
    char * tok = NULL;
    char backup[40] ={'\0'};
    strcpy(backup,_argv[1]);
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

    return Open_File(backup, "r");
}

void FreeAll(UNICODE * turista)
{
    free(turista->passadeira_vermelha.points);

    for(int i = 0; i < turista->tabu.size_x; i++)
        free(turista->tabu.tab[i]);

    free(turista->tabu.tab);
}


int check_EOF( FILE * file )
{ 
    int fim = 1;
    char buffer[MAX_SIZE] = {'\0'};
    char *aux=NULL;
    fgets(buffer,MAX_SIZE,file);
    printf("ola\n");
    while(aux != NULL && strcmp(buffer,"\n") == 0){
       aux = fgets(buffer,MAX_SIZE,file);
       puts(buffer);
           printf("ola1\n");
    }

        printf("ola2\n");
    if( aux == NULL)
        fim = 0;

    return fim;
}