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


/**
 * Allocs memory (with calloc) and checks if the memory was correctly allocated
 * @param  size [size of memory to be allocated]
 * @return      [returns void * to the memory allocation]
 */
Item Checked_Malloc(size_t size)
{
    Item mem = calloc(1, size);
    if(mem == NULL)
    {
        printf("Error alocating memory. Exiting\n");
        exit(0);
    }
    return mem;
}

/**
 * Opens a file and checks if was correctly opened
 * @param  file_name [name of the file to be opened]
 * @param  mode      [mode to open the file]
 * @return           [file pointer]
 */
FILE * Open_File(char * file_name, char * mode)
{
    FILE * fp = NULL;

    fp = fopen(file_name, mode);
    if(fp == NULL)
    {
        printf("Error opening file %s. Exiting.\n", file_name);
        exit(0);
    }
    return fp;
}


/**
 * Checks the argv arguments to the main program run
 * @param  _argc [number of argv arguments]
 * @param  _argv [char ** vector with the imput arguments]
 * @return       [returns the file pointer if all arguments are valids]
 */
FILE * checkArguments(int _argc, char ** _argv)
{
    char * aux = NULL;

    if((aux = strstr(_argv[1], ".cities")) == NULL)
        exit(0);
    if(*(aux + 7) != '\0')
        exit(0);

    return Open_File(_argv[1], "r");
}




/**
 * Generates the output file name based on the imput file name
 * @param  nome_inicial [name of the imput file]
 * @return              [returns the file pointer to the output file]
 */
FILE * OutPutFileName(char * nome_inicial)
{
    int i = 0; // o i tem que ser inicializado fora do for para que a variável seja conservada fora do for

    //descobrir qual é a posição do '.' no ficheiro original
    for( i = 0; i < strlen(nome_inicial) && nome_inicial[i] != '.'; i++);

    char * novo = (char *) Checked_Malloc((strlen(".valid") + i + 1) * sizeof(char));

    // copiar todos os caracteres até ao '.'
    for (int j = 0; j < i; j++)
        novo[j] = nome_inicial[j];

    strcat(novo, ".walks"); // juntar as duas strings

    FILE * fp = Open_File(novo, "w");
    free(novo);

    return fp;
}

int fact(int n)
{
    if(n == 1 || n == 0)
        return 1;

    return n * fact(n - 1);
}

void printMatrix(Item * matrix, int sizey, int sizex)
{
    for(int i = 0; i < sizey; i ++)
    {
        for(int j = 0; j < sizex; j++)
        {
            printf("%d ", ((int *)matrix[i])[j]);
        }
        printf("\n");
    }
}
