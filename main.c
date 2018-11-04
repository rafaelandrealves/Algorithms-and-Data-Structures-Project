#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "util.h"
#include "defs.h"
#include "tabuleiros.h"





int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    UNICODE * cavaleiro;

    // aqui vamos ter o while principal do programa

    /*
        LEITURA DO FICHEIRO
    */
    cavaleiro = Read_File(fp_in);

    /*
        PROCESSA INFORMAÇÃO E TALVEZ ESCREVA FICHEIRO
    */



   /*
        LIBERTA A MEMÓRIA DESTA ITERAÇÃO
   */

    FreeAll(cavaleiro);


    fclose(fp_in);
    return (0);
}