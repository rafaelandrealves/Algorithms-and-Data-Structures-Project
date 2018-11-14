


#include "defs.h"
#include "util.h"
#include "tabuleiros.h"
#include "points.h"


//Função encarregue de fazer os movimentos para todos os lados possiveis e ver qual é que é mais barato
/*
 PARAM:
  -> NEW: Matriz com os dados da matriz
  -> soma_min : soma minima total
*/
void movimentos(UNICODE *new, int *soma_min){
    char variavelx = 'x';
    char variavely = 'y';
    printf("---->%d\n",new->tabu.tab[new->passadeira_vermelha.points[0].y][new->passadeira_vermelha.points[0].x]);
    movimentos_num_ponto(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x ,(new->passadeira_vermelha.points[0].y - 2),variavelx,soma_min);//move_HIGH
    movimentos_num_ponto(new,new->tabu.size_x,new->tabu.size_y,new->passadeira_vermelha.points[0].x ,(new->passadeira_vermelha.points[0].y + 2),variavelx,soma_min);//move_LOW
    movimentos_num_ponto(new,new->tabu.size_x,new->tabu.size_y,(new->passadeira_vermelha.points[0].x + 2) ,new->passadeira_vermelha.points[0].y,variavely,soma_min);//move_low_right
    movimentos_num_ponto(new,new->tabu.size_x,new->tabu.size_y,(new->passadeira_vermelha.points[0].x -2) ,new->passadeira_vermelha.points[0].y,variavely,soma_min);//move_low_left
}

//Função que tem como variáveis uma condição, que pode ser x ou y, por exemplo, se for x, quer dizer que é o x que varia entre 1 ou -1 enquanto a outro váriavel mantêm-se fixa, 
// esta função tem por base o facto de que em todos os movimentos existe sempre uma variavel que varia -2 ou +2, mas mantêm-se, enquanto a outro varia entre -1 e 1
// PARAM: 
/*
    new ->matriz com os dados do ficheiro
    xmax e ymax -> dimensões da matriz
    x e y-> ponto de partida
    condição -> Se a variável que oscila entre 1 e -1 é a x ou y 
    soma_min ->  soma mínima das operaçoes 


*/
void movimentos_num_ponto(UNICODE *new,int xmax, int ymax, int x , int y , char condicao, int *soma_min)
{   int soma2=0,soma1=0;
    
    
    
    if(condicao == 'y'){
        if(x < xmax && (y+1) < ymax && x >= 0)
        {
            soma1 = new->tabu.tab[y+1][x];
        }
        if(x < xmax && x >= 0 && (y-1) >= 0)
        {
            soma2 = new->tabu.tab[y-1][x]; 
        }        
        if( soma1 <= *soma_min && soma1 != 0){
            *soma_min=soma1;
        }
        if( soma2 <= *soma_min && soma2 != 0){
            *soma_min=soma2;
        }
    }
    if(condicao == 'x'){
        if((x+1) < xmax && y < ymax && y >= 0)
        {  
            soma1 = new->tabu.tab[y][x + 1];
 
        }
        if( y < ymax && (x-1) >= 0 && y >= 0)
        {  
            soma2 = new->tabu.tab[y][x - 1];

        }
        if( soma1 <= *soma_min && soma1 != 0){
            *soma_min=soma1;
        }
        if( soma2 <= *soma_min && soma2 != 0){
            *soma_min=soma2;
        }
    }
}
// analisa se o ponto dado está ou não dentro da matriz

int analisa_pontos(UNICODE *new)
{
    if(new->tabu.size_x > new->passadeira_vermelha.points[0].x && new->tabu.size_y > new->passadeira_vermelha.points[0].y && new->passadeira_vermelha.points[0].x >=0 && new-> passadeira_vermelha.points[0].y >= 0 )
    {
        return 1;

    }
    else
    {
        return -1;
    }
}



int get_X_From_Point(point ponto)
{
    return ponto.x;
}


int get_Y_From_Point(point ponto)
{
    return ponto.y;
}

