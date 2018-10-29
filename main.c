#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "util.h"
#include "defs.h"
#include "leitura_fich.h"

int main (int argc, char ** argv)
{ 
    UNICODE * cavaleiro = Read_File(argv[1]);

    

    if(strstr(argv[1],".cities")==NULL) //será que é preciso garantir que está na posição certa??
    {
        printf("ERROR-HAS TO BE A .cities file");
        exit (1);
    }

    


    free(cavaleiro);
    return (0);
}