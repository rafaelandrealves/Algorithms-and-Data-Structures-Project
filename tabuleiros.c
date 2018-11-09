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


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"





UNICODE * Read_File(FILE * fp)
{
    UNICODE * new = (UNICODE *) Checked_Malloc(sizeof(UNICODE));

    int i = 0,j = 0;
    char buffer[MAX_SIZE] = {'\0'};
    char delim[4] = " ";
    char * tok = NULL;
    fgets(buffer,MAX_SIZE,fp);


    sscanf(buffer,"%d %d %c %d", &new->tabu.size_x, &new->tabu.size_y, &new->modo_jogo, &new->passadeira_vermelha.num_pontos);

    new->tabu.tab = (int **) Checked_Malloc(new->tabu.size_x * sizeof(int*));
    new->passadeira_vermelha.points = (point *) Checked_Malloc( new->passadeira_vermelha.num_pontos * sizeof(point));


    while(i < new->passadeira_vermelha.num_pontos)
    {
        fgets(buffer,MAX_SIZE,fp);  
        sscanf(buffer,"%d %d",&new->passadeira_vermelha.points[i].x,&new->passadeira_vermelha.points[i].y);
        // FIXME: tinhas aqui um erro porque estavas a ler tudo para a mesma posição
        i++;
    }
    i = 0;

    while(i < new->tabu.size_x)
    {
        fgets(buffer,MAX_SIZE,fp);
        new->tabu.tab[i] = (int *) Checked_Malloc(new->tabu.size_y*sizeof(int));
        tok = strtok(buffer,delim); 
        while (tok != NULL)
        { 
            new->tabu.tab[i][j] = atoi(tok); 
            tok = strtok(NULL, delim); 
            j++;
        }
        j=0;
        i++;
    }


    // printf("%d--%d---%c--%d--%d\n",new->tabu.size_x,new->passadeira_vermelha.num_pontos,new->modo_jogo,new->tabu.tab[0][0],new->tabu.tab[1][2]);

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














