

#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"





int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    // FILE * fp_in  = fopen("t7006.cities", "r");
    FILE * fp_out = OutPutFileName(argv[1]);
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
        if(cavaleiro->modo_jogo == 'B' && end_of_file == false)
            Execute_B_Variant(cavaleiro, fp_out);
        else if(end_of_file == true);
        else
            WriteFileWithFailure(cavaleiro, fp_out);

        /*
            LIBERTA A MEMÓRIA DESTA ITERAÇÃO
        */

        FreeAll(cavaleiro);
    }

    fclose(fp_in);
    fclose(fp_out);
    return (0);
}
