


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
    point * points; // ou por uma lista
    int custo_total;
}caminho;

typedef struct tabuleiro
{
    int size_x; // dimensões do tabuleiro
    int size_y;
    int ** tab; // matriz do tabuleiro
} tabuleiro;

typedef struct UNICODE // estrutura principal do programa
{
    char modo_jogo; // ou char
    tabuleiro tabu; // tabuleiro
    caminho passadeira_vermelha; // conjunto de pontos que o utilizador coloca
    caminho * para_preguicosos;  // caminhos que podem ser a solução ótima
} UNICODE;




#endif
