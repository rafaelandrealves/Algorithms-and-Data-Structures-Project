#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"

//se for para baixo é movimento -1 , para cima é 1

int MovesLowRight( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido ){
    int soma=0;



    if(strcmp(sentido,"high")==0){
        for(int j=0;j<3;j++){
            if(( x - 1) < xmax && (x - 1) > 0 && (y+j) < ymax && (y+j) >0)
                soma+=new->tabu.tab[x-1][y+j];
        }
    }
    else
    {
        for(int j=0;j<3;j++){
            if((x+1) < xmax && (x + 1) > 0 && (y+j) < ymax && (y+j) >0)
                soma+=new->tabu.tab[x+1][y+j];
        }

    }
    return soma;
}

int MovesLowLeft( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido ){
    int soma=0;



     if(strcmp(sentido,"high")==0){
        for(int j=0;j<3;j++){
            if(( x - 1) < xmax && (x - 1) > 0 && (y-j) < ymax && (y-j) >0)
                soma+=new->tabu.tab[x-1][y-j];
        }
    }
    else
    {
        for(int j=0;j<3;j++){
            if((x + 1) < xmax && (x + 1) > 0 && (y-j) < ymax && (y-j) >0)
                soma+=new->tabu.tab[x+1][y-j];
        }

    }
    return soma;
}



//menos -1 esquerda e 1 direita
int MovesHigh( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido ){
    int j=0,soma=0;



     if(strcmp(sentido,"right")==0){
        for(j=0;j<2;j++){
            if((x-j) > 0)
                soma+=new->tabu.tab[x-j][y];
        }
        if(y+1 < ymax){
            soma+=new->tabu.tab[x-j][y+1];
        }
    }
    else
    {
        for(j=0;j<2;j++){
            if( (x-j) > 0)
                soma+=new->tabu.tab[x-j][y];
        }
        if(y-1 > 0){
            soma+=new->tabu.tab[x-j][y-1];
        }

    }
    return soma;
}

//menos -1 esquerda e 1 direita
int MovesLow( UNICODE *new , int xmax , int ymax , int x, int y , char * sentido  ){
    int j=0,soma=0;



     if(strcmp(sentido,"right")==0){
        for(j=0;j<2;j++){
            if((x+j) < xmax)
                soma+=new->tabu.tab[x+j][y];
        }
        if(y+1 < ymax){
            soma+=new->tabu.tab[x+j][y+1];
        }
    }
    else
    {
        for(j=0;j<2;j++){
            if((x+j) < xmax)
                soma+=new->tabu.tab[x+j][y];
        }
        if(y-1 > 0){
            soma+=new->tabu.tab[x+j][y-1];
        }

    }
    return soma;
}




















