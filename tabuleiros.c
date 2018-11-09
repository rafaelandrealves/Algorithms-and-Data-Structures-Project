/******************************************************************************
 *
 * File Name: leitura_fich.c
 
 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  27 Oct 2018
 *
 * NAME
 *     util.c - Implementation of reading file functions
 *
*/


// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <string.h>


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"





UNICODE * Read_File(FILE * fp, bool *end_of_file)
{
    UNICODE * new = (UNICODE *) Checked_Malloc(sizeof(UNICODE));



    if(fscanf(fp, "%d %d %c %d", &new->tabu.size_y, &new->tabu.size_x, &new->modo_jogo, &new->passadeira_vermelha.num_pontos) < 4)
    {
        *end_of_file = true;
        return NULL;
    }
    printf("%d %d %c %d\n", new->tabu.size_y, new->tabu.size_x, new->modo_jogo, new->passadeira_vermelha.num_pontos);

    new->tabu.tab = (int **) Checked_Malloc(new->tabu.size_y * sizeof(int*));
    for(int i = 0; i < new->tabu.size_y; i++)
        new->tabu.tab[i] = (int *) Checked_Malloc(new->tabu.size_x * sizeof(int));

    new->passadeira_vermelha.points = (point *) Checked_Malloc( new->passadeira_vermelha.num_pontos * sizeof(point));


    for(int i = 0; i < new->passadeira_vermelha.num_pontos; i++)
    {
        fscanf(fp, "%d %d", &new->passadeira_vermelha.points[i].x, &new->passadeira_vermelha.points[i].y);
        printf("%d %d \n \a", new->passadeira_vermelha.points[i].x, new->passadeira_vermelha.points[i].y);
    }

    
    for(int yy = 0; yy < new->tabu.size_y; yy++)
    {
       for(int xx = 0; xx < new->tabu.size_x; xx++)
           fscanf(fp, "%d ", &new->tabu.tab[yy][xx]);
    }


    return new;
}



char * OutPutFileName(char * nome_inicial)
{
    int i = 0;
    //descobrir qual é a posição do '.' no ficheiro original
    for( i = 0; i < strlen(nome_inicial); i++)
    {
        if(nome_inicial[i] ==  '.')
        break;
    }

    char * novo = (char *) malloc((strlen(".walks") + i)*sizeof(char));

    // copiar todos os caracteres até ao '.'
    for (int j = 0; j < i; j++)
        novo[j] = nome_inicial[j];

    strcat(novo, ".walks"); // juntar as duas strings

    return novo;
}














