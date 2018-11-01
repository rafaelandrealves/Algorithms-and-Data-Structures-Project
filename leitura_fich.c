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


#include "util.h"
#include "defs.h"
#include "leitura_fich.h"

UNICODE * Read_File(char * name_file)
{
    FILE * fp = Open_File(name_file, "r");
    UNICODE * new = (UNICODE *) Checked_Malloc(sizeof(UNICODE));

    // TODO: LEITURA DO FICHEIRO



    fclose(fp);

    return new;
}

char * OutPutFileName(char * nome_inicial)
{
    int i = 0;
    //descobrir qual é a posição do '.' no ficheiro original
    for( i = 0; i < strlen(nome_inicial[1]); i++)
    {
        if(nome_inicial[1][i] ==  '.')
        break;
    }

    char * novo = (char *) malloc((strlen(".walks") + i)*sizeof(char));

    // copiar todos os caracteres até ao '.'
    for (int j = 0; j < i; j++)
        novo[j] = nome_inicial[1][j];

    strcat(novo, ".walks"); // juntar as duas strings

    return novo;
}