/******************************************************************************
 *
 * File Name: util.h

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  27 Oct 2018
 *
 * NAME
 *     util.h - Implementation of utilitary functions to alloc memory, open files, etc
 *
*/

#ifndef _UTIL_H
#define _UTIL_H


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


void * Checked_Malloc(size_t size);

FILE * Open_File(char * file_name, char * mode);

FILE * checkArguments(int _argc, char ** _argv);

void FreeAll(UNICODE * turista);

void PrintMainStruct(UNICODE * turista);

FILE * OutPutFileName(char * nome_inicial);




#endif
