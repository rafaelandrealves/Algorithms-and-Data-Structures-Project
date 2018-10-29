


#ifndef _DEFS_H
#define _DEFS_H


typedef struct point
{
    int x;
    int y;
    int custo;
} point;

typedef struct tabuleiro
{
    int size_x; // dimensões do tabuleiro
    int size_y;
    int ** tab; // matriz do tabuleiro
} tabuleiro;

typedef struct caminho
{
    int num_pontos;
    point * points; // ou por uma lista
    int custo_total;
}caminho;

typedef struct elastico_demux // estrutura principal do programa
{
    int modo_jogo; // ou char
    tabuleiro tabu; // tabuleiro
    caminho passadeira_vermelha; // conjunto de pontos que o utilizador coloca
    caminho * para_preguicosos;  // caminhos que podem ser a solução ótima
} elastico_demux;


#endif
