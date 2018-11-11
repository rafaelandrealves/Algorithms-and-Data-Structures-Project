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
#include "moves.h"

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
        printf("rfrError opening file %s. Exiting.\n", file_name);
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
    char * tok = NULL;
    char backup[40] = {'\0'};


    strcpy(backup, _argv[1]);

    if(_argc > 2){
        exit(0);
    }

    if(strstr(_argv[1],".cities") == NULL)
    {
        exit (0);
    }
    tok = strtok(_argv[1], ".");
    tok = strtok(NULL, "\0");
    if( strcmp(tok,"cities") != 0 ){
        exit(0);
    }

    return Open_File(backup, "r");
}

/**
 * Free all memory from one struct
 * @param turista [struct to be freed]
 */
void FreeAll(UNICODE * turista)
{
    // fazer free do caminho lido do ficheiro
    free(turista->passadeira_vermelha.points);

    for(int i = 0; i < turista->tabu.size_y; i++)
        free(turista->tabu.tab[i]);

    free(turista->tabu.tab);

    free(turista);
}

/**
 * Prints all the info of one struct the way it was read
 * @param turista [struct to be printed]
 */
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


/**
 * Generates the output file name based on the imput file name
 * @param  nome_inicial [name of the imput file]
 * @return              [returns a char * to the output file name]
 */
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
