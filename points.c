


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"

//se for para baixo é movimento -1 , para cima é 1

void MovesLowRight( UNICODE *new , int xmax , int ymax , int x, int y ){
    int soma=0;

        soma+=new->tabu.tab[x][y];
        for(int j=0;j<3;j++)
        {
            if( (x - 1) > 0 && (y+j) < ymax){
                soma+=new->tabu.tab[x-1][y+j];
            }
            else
            {
                soma=0;
            }
        }
        new->para_preguicosos[6].custo_total=soma;   
        soma=0;
        soma+=new->tabu.tab[x][y]; 
        for(int j=0;j<3;j++)
        {
            if((x+1) < xmax && (y+j) < ymax){
                soma+=new->tabu.tab[x+1][y+j];
            }
            else
            {
                soma=0;
            }
        }
        new->para_preguicosos[7].custo_total=soma;    

    
}

void MovesLowLeft( UNICODE *new , int xmax , int ymax , int x, int y ){
    int soma=0;

    soma+=new->tabu.tab[x][y];
    for(int j=0;j<3;j++)
    {
        if((x - 1) > 0 && (y-j) > 0){
            soma+=new->tabu.tab[x-1][y-j];
        }
        else
        {
            soma=0;
        }    
    }
    new->para_preguicosos[4].custo_total=soma;    
    soma=0;
    soma+=new->tabu.tab[x][y];
    for(int j=0;j<3;j++)
    {
        if((x + 1) < xmax && (y-j) > 0)
        {
            soma+=new->tabu.tab[x+1][y-j];
        }
        else
        {
            soma=0;
        }
    }
    new->para_preguicosos[5].custo_total=soma;    
}



//menos -1 esquerda e 1 direita
void MovesHigh( UNICODE *new , int xmax , int ymax , int x, int y ){
    int j=0,soma=0;

    for(j=0;j<3;j++)
    {
        if((x-j) > 0){
            soma+=new->tabu.tab[x-j][y];
        }
        else
        {
            soma=0;
        }
    }
    if(y+1 < ymax)
    {
        soma+=new->tabu.tab[x-j][y+1];
    }
    else
    {
        soma=0;
    }  
    new->para_preguicosos[2].custo_total=soma;    
    soma=0;
    for(j=0;j<3;j++){
        if( (x-j) > 0)
        {
            soma+=new->tabu.tab[x-j][y];
        }
        else
        {
            soma=0;
        }
    } 
    if(y-1 > 0)
    {
        soma+=new->tabu.tab[x-j][y-1];
    }
    else
    {
        soma=0;
    }
    new->para_preguicosos[3].custo_total=soma;    
}

//menos -1 esquerda e 1 direita
void MovesLow( UNICODE *new , int xmax , int ymax , int x, int y ){
    int j=0,soma=0;
    for(j=0;j<3;j++)
    {
        if((x+j) < xmax)
        {
            soma+=new->tabu.tab[x+j][y];
        }
        else
        {
            soma=0;
        }
    }
    if(y+1 < ymax)
    {
        soma+=new->tabu.tab[x+j-1][y+1];
    }
    else
    {
        soma=0;
    }
    new->para_preguicosos[0].custo_total=soma;    
    soma=0;
    for(j=0;j<3;j++){
        if((x+j) < xmax)
        {
            soma+=new->tabu.tab[x+j][y];
        }
        else
        {
            soma=0;
        }
    }
    if(y-1 > 0){
        soma+=new->tabu.tab[x+j][y-1];
    }
    else
    {
        soma=0;
    } 
    new->para_preguicosos[1].custo_total=soma;
}



int  analisa_jogadas(UNICODE *new){
    int soma_min=1000;
    for(int i=0 ; i < 8 ; i++)
    {
        if(soma_min > new->para_preguicosos[i].custo_total)
        {
            soma_min = new->para_preguicosos[i].custo_total;
        }

    }
    return soma_min;
}

void movimentos(UNICODE *new){
    MovesLow(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y);
    MovesLowLeft(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y);
    MovesLowRight(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y);
    MovesHigh(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y);
}














int get_X_From_Point(point ponto)
{
    return ponto.x;
}


int get_Y_From_Point(point ponto)
{
    return ponto.y;
}

