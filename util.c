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
#include "leitura_fich.h"

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

