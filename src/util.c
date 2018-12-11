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
        printf("Error alocating memory. Exiting...\n");
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
    if(_argc > 2 || _argc < 2)
        exit(0);

    int size = strlen(_argv[1]);
    if(size <= 7 || !(_argv[1][size - 1] == 's' && _argv[1][size - 2] == 'e' && _argv[1][size - 3] == 'i' && _argv[1][size - 4] == 't' &&
        _argv[1][size - 5] == 'i' && _argv[1][size - 6] == 'c' && _argv[1][size - 7] == '.'))
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

    // i gets the position of '.'
    for( i = strlen(nome_inicial); i >= 0 && nome_inicial[i] != '.'; i--);

    char * novo = (char *) Checked_Malloc((strlen(".walks") + i + 1) * sizeof(char));

    // copy all chars until the '.'
    for (int j = 0; j < i; j++)
        novo[j] = nome_inicial[j];

    strcat(novo, ".walks"); // juntar as duas strings

    FILE * fp = Open_File(novo, "w");
    free(novo);

    return fp;
}

/**
 * Factorial of integer n
 * @param  n [number]
 * @return   [n!]
 */
unsigned long int fact(int n)
{
    if(n == 1 || n == 0)
        return 1;

    return n * fact(n - 1);
}

/**
 * Auxiliary function to print one matrix to help in the debug
 * @param matrix [matrix]
 * @param sizey  [size y of the matrix]
 * @param sizex  [size x of the matrix]
 */
void printMatrix(Item * matrix, int sizey, int sizex)
{
    for(int i = 0; i < sizey; i ++)
    {
        for(int j = 0; j < sizex; j++)
        {
            printf("%d ", ((char *)matrix[i])[j]);
        }
        printf("\n");
    }
}
