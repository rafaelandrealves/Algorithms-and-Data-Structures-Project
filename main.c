

#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"
#include "moves.h"





int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    FILE *fp_out = OutPutFileName(argv[1]);
    // FILE * fp_in = fopen(argv[1], "r");
    UNICODE * cavaleiro;
    bool end_of_file = false;
    int soma_min=10000;
    int sinal=0;
        /*
            LEITURA DO FICHEIRO
        */
    while(!end_of_file)
    {
        cavaleiro = Read_File(fp_in, &end_of_file);
        if( cavaleiro -> modo_jogo == 'A'){
            //movimentos(cavaleiro,jogadas);
            //soma=analisa_jogadas(cavaleiro,jogadas);
            sinal=analisa_pontos(cavaleiro);
            if(sinal==-1)
            {
                printf("O PONTO NÃO É VÁLIDO \n");
                soma_min = -1;
                 printf(" A SOMA é %d \n",soma_min);

            }
            else
            {
                movimentos(cavaleiro,&soma_min);
                if(soma_min==10000)
                {
                    printf("NÃO EXISTEM JOGADAS POSSIVEIS\n");
                    FreeAll(cavaleiro);
                    sinal=0;
                    continue;
                }

            fprintf(fp_out, " A SOMA é %d \n",soma_min);

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
                soma_min=10000;

            }
            sinal=0;
        }
        FreeAll(cavaleiro);
    }

    fclose(fp_in);
    fclose(fp_out);
    return (0);
}
