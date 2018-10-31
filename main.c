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
    char *tok=NULL;
    if(argc>2){
        printf("ERRO NUMERO ELEVADO DE ELEMENTOS");
        exit(1);
    }    

    if(strstr(argv[1],".cities")==NULL) //será que é preciso garantir que está na posição certa??
    {
        printf("ERROR-HAS TO BE A .cities file");
        exit (1);
    }
    tok=strtok(argv[1],".");
    tok=strtok(NULL,"\0");
    if(strcmp(tok,"cities")!=0){
        printf("ERROR, TRYING THAT DOESNT WORK");
        exit(1);
    }

    


    free(cavaleiro);
    return (0);
}