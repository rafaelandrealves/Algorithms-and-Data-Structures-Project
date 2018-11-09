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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void * Checked_Malloc(size_t size);

FILE * Open_File(char * file_name, char * mode);

FILE * checkArguments(int _argc, char ** _argv);

void FreeAll(UNICODE * turista);

int check_EOF( FILE * file );



#endif