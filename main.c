

#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"





int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    // FILE * fp_in = fopen(argv[1], "r");
    UNICODE * cavaleiro;
    int jogadas[8]={'0'};
    bool end_of_file = false;
    int soma=0;
        /*  
            LEITURA DO FICHEIRO
        */
        cavaleiro = Read_File(fp_in, &end_of_file);
        movimentos(cavaleiro,jogadas);
        soma=analisa_jogadas(cavaleiro,jogadas);
        printf("A melhor soma é %d\n",soma);
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