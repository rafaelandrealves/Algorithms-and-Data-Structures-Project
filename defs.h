


#ifndef _DEFS_H
#define _DEFS_H


#define MAX_SIZE 2048


typedef void * Item;

typedef struct point
{
    int x;
    int y;
} point;


typedef struct caminho
{
    int num_pontos;
    point * points;
    int custo_total;
} caminho;

typedef struct tabuleiro
{
    int size_x; // sizes of the table
    int size_y;
    int ** tab; // table matrix
} tabuleiro;

typedef struct UNICODE // main struct of the program
{
    char modo_jogo; // problem mode
    tabuleiro tabu; // table
    caminho passadeira_vermelha; // move that ir read from the file
    caminho * para_preguicosos;  // possible ways to be the optimal soluction
} UNICODE;




#endif
