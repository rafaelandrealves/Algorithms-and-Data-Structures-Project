#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"





int main (int argc, char ** argv)
{
    // FILE * fp_in = checkArguments(argc, argv);
    FILE * fp_in = fopen(argv[1], "r");
    UNICODE * cavaleiro;
    int num = 0;
    bool end_of_file = false;


    do
    {
        /*
            LEITURA DO FICHEIRO
        */
        cavaleiro = Read_File(fp_in, &end_of_file);

        /*
            PROCESSA INFORMAÇÃO E TALVEZ ESCREVA FICHEIRO
        */
        num++;
        /*
            LIBERTA A MEMÓRIA DESTA ITERAÇÃO
        */

        // FreeAll(cavaleiro);
        
    //}while( num < 10 && !check_EOF(fp_in));
    }while(!end_of_file);

    printf("Fiz %d vezes\n", num);


    fclose(fp_in);
    return (0);
}