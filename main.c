#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "util.h"

int main (int argc, char ** argv)
{ 
    FILE *fp=NULL;

    if(strcmp(argv[0],"./tuktuk")!=0 ){
        printf("ERROR-NAME OF THE EXEC. HAS TO BE tuktuk");
        exit (1);
    }
    if(strstr(argv[1],".cities")==NULL){//será que é preciso garantir que está na posição certa??
        printf("ERROR-HAS TO BE A .cities file");
        exit (1);
    }
    fp=fopen(argv[1],"r");
    if(fp==NULL){// validação,caso o ficheiro não abra, o prgrama vai fechar
        printf("Não foi possível abrir o ficheiro");
        exit(1);
    }





    fclose(fp);
    return (0);
}