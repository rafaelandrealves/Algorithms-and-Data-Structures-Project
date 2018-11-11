


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"

//se for para baixo é movimento -1 , para cima é 1

void MovesLowRight( UNICODE *new , int xmax , int ymax , int x, int y, int jog[8] ){
    int soma=0;

        soma+=new->tabu.tab[x][y];
        for(int j=0;j<3;j++)
        {
            if( (x - 1) >= 0 && (y+j) < ymax){
                soma+=new->tabu.tab[x-1][y+j];
            }
            else
            {
                soma=0;
                break;
            }
        }
        jog[6]=soma;   
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
                break;
            }
        }
        jog[7]=soma;    

    
}

void MovesLowLeft( UNICODE *new , int xmax , int ymax , int x, int y , int jog[8] ){
    int soma=0;
    soma+=new->tabu.tab[x][y];
    for(int j=0;j<3;j++)
    {
        if((x - 1) >= 0 && (y-j) >= 0){
            soma+=new->tabu.tab[x-1][y-j];
        }
        else
        {
            soma=0;
            break;
        }    
    }
    jog[4]=soma;    
    soma=0;
    soma+=new->tabu.tab[x][y];
    for(int j=0;j<3;j++)
    {
        if((x + 1) < xmax && (y-j) >= 0)
        {
            soma+=new->tabu.tab[x+1][y-j];
        }
        else
        {
            soma=0;
            break;
        }
    }
    jog[5]=soma;    
}



//menos -1 esquerda e 1 direita
void MovesHigh( UNICODE *new , int xmax , int ymax , int x, int y, int jog[8] ){
    int j=0,soma=0,sinal=1;

    for(j=0;j<3;j++)
    {
        if((x-j) >= 0){
            soma+=new->tabu.tab[x-j][y];
        }
        else
        {
            soma=0;
            sinal=0;
            break;
        }
    }
    if(sinal==1 && y+1 < ymax)
    {
        soma+=new->tabu.tab[x-j+1][y+1];
    }
    else
    {
        soma=0;
    }  
    jog[2]=soma;  
    printf("= 1 valor é %d \n",jog[2]);  
    soma=0;
    sinal=1;
    for(j=0;j<3;j++){
        if( (x-j) >= 0)
        {
            soma+=new->tabu.tab[x-j][y];
  
        }
        else
        {
            soma=0;
            sinal=0;
            break;
        }
    } 
    if( sinal==1 && y-1 >= 0)
    {
        soma+=new->tabu.tab[x-j+1][y-1];
    }
    else
    {
        soma=0;
    }
    jog[3]=soma;    
}

//menos -1 esquerda e 1 direita
void MovesLow( UNICODE *new , int xmax , int ymax , int x, int y, int jog[8] ){
    int j=0,soma=0,sinal=1;
    for(j=0;j<3;j++)
    {
        if((x+j) < xmax)
        {
            soma+=new->tabu.tab[x+j][y];
        }

        else
        {
            soma=0;
            sinal=0;
            break;
        }
    }

    if(sinal==1 && y+1 < ymax)
    {
        soma+=new->tabu.tab[x+j-1][y+1];
    }
    else
    {
        soma=0;
    }
    jog[0]=soma;  
    soma=0;
    sinal=1;
    for(j=0;j<3;j++){
        if((x+j) < xmax)
        {
            soma+=new->tabu.tab[x+j][y];
        }
        else
        {
            soma=0;
            sinal=0;
            break;
        }
    }
    if(sinal==1 && y-1 > 0){
        soma+=new->tabu.tab[x+j-1][y-1];
    }
    else
    {
        soma=0; 
    }    
    jog[1]=soma;
    printf("O valor é %d \n",jog[0]);  

}



int  analisa_jogadas(UNICODE *new, int jog[8]){
    int soma_min=1000;
    for(int i=0 ; i < 8 ; i++)
    {   printf("%d\n",jog[i]);
        if(soma_min > jog[i] && jog[i] != 0)
        {
            soma_min = jog[i];
        }

    }
    return soma_min;
}

void movimentos(UNICODE *new, int jog[8]){
    MovesLow(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y,jog);
    MovesLowLeft(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y,jog);
    MovesLowRight(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y,jog);
    MovesHigh(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x,new->passadeira_vermelha.points[0].y,jog);
}














int get_X_From_Point(point ponto)
{
    return ponto.x;
}


int get_Y_From_Point(point ponto)
{
    return ponto.y;
}

