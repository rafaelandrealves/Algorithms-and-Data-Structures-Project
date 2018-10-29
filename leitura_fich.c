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