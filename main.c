#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"





int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    UNICODE * cavaleiro;
    int num = 0;

    // aqui vamos ter o while principal do programa

    while( check_EOF(fp_in) )
    {
        /*
            LEITURA DO FICHEIRO
        */
        cavaleiro = Read_File(fp_in);

        /*
            PROCESSA INFORMAÇÃO E TALVEZ ESCREVA FICHEIRO
        */
        num++;

        /*
            LIBERTA A MEMÓRIA DESTA ITERAÇÃO
        */

        FreeAll(cavaleiro);
        
    }

    printf("Fiz %d vezes\n", num);


    fclose(fp_in);
    return (0);
}