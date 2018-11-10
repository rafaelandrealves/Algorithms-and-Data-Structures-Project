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




#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"


void * Checked_Malloc(size_t size)
{
    void * mem = calloc(1, size);
    if(mem == NULL)
    {
        printf("Error alocating memory. Exiting\n");
        exit(0);
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
        exit(0);
    }
    return fp;
}


FILE * checkArguments(int _argc, char ** _argv)
{
    char * tok = NULL;
    char backup[40] = {'\0'};


    strcpy(backup, _argv[1]);

    if(_argc > 2){
        printf("ERRO! NUMERO ELEVADO DE ELEMENTOS");
        exit(0);
    }    

    if(strstr(_argv[1],".cities") == NULL)
    {
        printf("ERROR-HAS TO BE A .cities file");
        exit (0);
    }
    tok = strtok(_argv[1], ".");
    tok = strtok(NULL, "\0");
    if( strcmp(tok,"cities") != 0 ){
        printf("ERROR, TRYING THAT DOESNT WORK");
        exit(0);
    }

    return Open_File(backup, "r");
}


void FreeAll(UNICODE * turista)
{
    // fazer free do caminho lido do ficheiro
    free(turista->passadeira_vermelha.points);

    for(int i = 0; i < turista->tabu.size_y; i++)
        free(turista->tabu.tab[i]);

    free(turista->tabu.tab);

    free(turista);
}


void PrintMainStruct(UNICODE * turista)
{
    printf("%d %d %c %d\n", turista->tabu.size_y, turista->tabu.size_x, turista->modo_jogo, turista->passadeira_vermelha.num_pontos);

    for(int i = 0; i < turista->passadeira_vermelha.num_pontos; i++)
        printf("%d %d\n", get_X_From_Point(turista->passadeira_vermelha.points[i]), get_Y_From_Point(turista->passadeira_vermelha.points[i]));

    for(int yy = 0; yy < turista->tabu.size_y; yy++)
    {
        printf("\t");
        for(int xx = 0; xx < turista->tabu.size_x; xx++)
            printf("%d ", turista->tabu.tab[yy][xx]);

        printf("\n");
    }

}

char * OutPutFileName(char * nome_inicial)
{
    int i = 0;
    //descobrir qual é a posição do '.' no ficheiro original
    for( i = 0; i < strlen(nome_inicial) && nome_inicial[i] != '.'; i++);

    char * novo = (char *) Checked_Malloc((strlen(".walks") + i)*sizeof(char));

    // copiar todos os caracteres até ao '.'
    for (int j = 0; j < i; j++)
        novo[j] = nome_inicial[j];

    strcat(novo, ".walks"); // juntar as duas strings

    return novo;
}
