

#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"





int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    // FILE * fp_in = fopen(argv[1], "r");
    UNICODE * cavaleiro;
    bool end_of_file = false;


    while(!end_of_file)
    {
        /*
            LEITURA DO FICHEIRO
        */
        cavaleiro = Read_File(fp_in, &end_of_file);


        /*
            PROCESSA INFORMAÇÃO E TALVEZ ESCREVA FICHEIRO
        */


        /*
            LIBERTA A MEMÓRIA DESTA ITERAÇÃO
        */

        FreeAll(cavaleiro);
    }

    fclose(fp_in);
    return (0);
}
