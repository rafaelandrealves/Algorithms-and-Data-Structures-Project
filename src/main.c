


#include "defs.h"
#include "util.h"
#include "moves.h"

#define PrintStructs 0




/**
 * Reads and saves the information of one problem in the input file
 * @param  fp          [file pointer to the reading file]
 * @param  end_of_file [variable that checks if reached the end of file]
 * @return             [returns the main struct of the program with the new data (or empty in case of EOF)]
 */
Problema * Read_File(FILE * fp, int *sinal)
{
    int sizey, sizex, points_num;
    char game_mode;
    int pontox, pontoy;
    int cost;

    if(fscanf(fp, "%d %d %c %d", &sizey, &sizex, &game_mode, &points_num) != 4)
    {
        *sinal = 1;
        return NULL;
    }
    Problema * new ;
    if(*sinal == 0 )
        new = Alloc_Problema(sizey, sizex, game_mode, points_num);


    for(int i = 0; i < points_num ; i = i + 1)
        if(fscanf(fp, "%d %d", &pontoy, &pontox) == 2 && *sinal == 0)
            Aux_Set_Point(new, pontox, pontoy, i);


    for(int yy = 0; yy < sizey; yy = yy + 1)
    {
        for(int xx = 0; xx < getXSize(getTabuleiro(new)); xx = xx + 1)
            if(fscanf(fp, "%d ", &cost) == 1)
                Aux_Set_Matrix_Element(new, cost, yy, xx);
    }

    #if PrintStructs == 1
        PrintMainStruct(new);
    #endif

    return new;
}



int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    // FILE * fp_in = fopen("narrow_city01.cities", "r");
    FILE * fp_output = OutPutFileName(argv[1]);
    // FILE * fp_out = fopen("t1011.valid", "w");
    int sinal = 0;
    Problema * cavaleiro = Read_File(fp_in, &sinal);


    while(cavaleiro != NULL)
    {

        if(GetModoJogo(cavaleiro) == 'A')
            Execute_A_Variant(cavaleiro, fp_output,argv[1]);
        else if(GetModoJogo(cavaleiro) == 'B')
            Execute_B_Variant(cavaleiro, fp_output);
        else if(GetModoJogo(cavaleiro) == 'C')
            printf("Not done yet\n");
        else
            WriteFileWithFailure(cavaleiro, fp_output);
        FreeAll(cavaleiro);

        cavaleiro = Read_File(fp_in, &sinal);
    }

    fclose(fp_in);
    fclose(fp_output);
    return (0);
}