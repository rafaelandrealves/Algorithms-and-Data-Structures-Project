


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
Problema * Read_File(FILE * fp, bool * validity)
{
    int sizey, sizex, points_num, pontox, pontoy, cost, lixo;
    char game_mode;
    bool will_save = true;

    if(fscanf(fp, "%d %d %c %d", &sizey, &sizex, &game_mode, &points_num) != 4)
    {
        * validity = false;
        return NULL;
    }

    if( (game_mode == 'A' && points_num != 2) || (game_mode == 'B' && points_num < 2) || (game_mode == 'C' && points_num < 2) )
        will_save = false;

    if(game_mode != 'A' && game_mode != 'B' && game_mode != 'C')
        will_save = false;

    Problema * new = Alloc_Problema(sizey, sizex, game_mode, points_num);

    if(will_save == true)
    {
        for(int i = 0; i < points_num ; i = i + 1)
        {
            if(fscanf(fp, "%d %d", &pontoy, &pontox) == 2)
                Aux_Set_Point(new, pontox, pontoy, i);
        }
    }
    else
    {
        for(int i = 0; i < points_num ; i = i + 1)
        {
            if(fscanf(fp, "%d %d", &lixo, &lixo) == 2);
        }
    }

    if(will_save == true)
    {
        for(int yy = 0; yy < sizey; yy = yy + 1)
        {
            for(int xx = 0; xx < sizex; xx = xx + 1)
                if(fscanf(fp, "%d ", &cost) == 1)
                    Aux_Set_Matrix_Element(new, cost, yy, xx);
        }
    }
    else
    {
        for(int yy = 0; yy < sizey; yy = yy + 1)
        {
            for(int xx = 0; xx < sizex; xx = xx + 1)
                if(fscanf(fp, "%d ", &lixo) == 1);
        }
    }


    #if PrintStructs == 1
        PrintMainStruct(new);
    #endif

    * validity = will_save;

    return new;
}



int main (int argc, char ** argv)
{
    FILE * fp_in = checkArguments(argc, argv);
    FILE * fp_output = OutPutFileName(argv[1]);
    bool validity = false;

    Problema * cavaleiro = Read_File(fp_in, &validity);


    while(cavaleiro != NULL)
    {

        if(validity == true && GetModoJogo(cavaleiro) == 'A')
            Execute_A_Variant(cavaleiro, fp_output);
        else if(validity == true && GetModoJogo(cavaleiro) == 'B')
            Execute_B_Variant(cavaleiro, fp_output);
        else if(validity == true && GetModoJogo(cavaleiro) == 'C')
            Execute_C_Variant(cavaleiro, fp_output);
        else
            WriteFileWithFailure(cavaleiro, fp_output);

        FreeAll(cavaleiro);

        validity = false;
        cavaleiro = Read_File(fp_in, &validity);
    }

    fclose(fp_in);
    fclose(fp_output);
    return 0;
}
