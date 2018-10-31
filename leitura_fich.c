/******************************************************************************
 *
 * File Name: leitura_fich.c
 
 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  27 Oct 2018
 *
 * NAME
 *     util.c - Implementation of reading file functions
 *
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "util.h"
#include "defs.h"
#include "leitura_fich.h"

#define MAX_SIZE 2048

UNICODE * Read_File(char * name_file)
{
    FILE * fp = Open_File(name_file, "r");
    UNICODE * new = (UNICODE *) Checked_Malloc(sizeof(UNICODE));
    /*
    int check=0,i=0,j=0;
    char buffer[MAX_SIZE]={'\0'};
    char delim[4]=" ";
    char *tok=NULL;
    fgets(buffer,MAX_SIZE,fp);
    sscanf(buffer,"%d %d %c %d",&new->tabu.size_x,&new->tabu.size_y,&new->modo_jogo,&new->passadeira_vermelha.num_pontos);//será que é boa ideia meter o numero de pontos turisticos na mesma estrutura que o roteiro?

    while(i<new->passadeira_vermelha.num_pontos){
        fgets(buffer,MAX_SIZE,fp);  
        sscanf(buffer,"%d %d",&new->passadeira_vermelha.points->x,&new->passadeira_vermelha.points->y);//custo e isso metemos a NULL?
        i++;
    }
    i=0;
    while(i<new->tabu.size_x){
        fgets(buffer,MAX_SIZE,fp);
        tok = strtok(buffer,delim); 
        while (tok != NULL) { 
            printf("%s, ", tok);
            new->tabu.tab[i][j]=atoi(tok); 
            tok = strtok(NULL, delim); 
            j++;
        }
        j=0;
        i++;
    }
    if(fgets(buffer,MAX_SIZE,fp)!=EOF){
        //frees e recursiva??
        //para passar as lnhas entre matrizes vou colocando fgets até ser !=NULL?

    }

    */






    // TODO: LEITURA DO FICHEIRO



    fclose(fp);

    return new;
}