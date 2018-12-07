



#include "defs.h"
#include "util.h"
#include "dijkstra.h"


struct acervoStruct
{
    point ** heap;
    int free;
};


#include "acervo.h"

#define lessPri(A, B) (A > B)
#define exch(A, B) {Item t = A; A = B; B = t; }

int num_elementos = 200;


/**
 * [getFree description]
 * @param  new [description]
 * @return     [description]
 */
int getFree(Acervo * new)
{
    return new->free;
}

/**
 * [getIPointFromHeap description]
 * @param  new [description]
 * @param  i   [description]
 * @return     [description]
 */
point * getIPointFromHeap(Acervo * new, int i)
{
    return new->heap[i];
}

/**
 * [FreeAcervo description]
 * @param old [description]
 */
void FreeAcervo(Acervo * old)
{
    for(int i = 0; i < old->free; i++)
        if(old->heap[i] != NULL)
            free(old->heap[i]);

    free(old->heap);
    free(old);
}

/**
 * [InitAcervo description]
 * @return [description]
 */
Acervo * InitAcervo()
{
    Acervo * new = (Acervo *) Checked_Malloc(sizeof(Acervo));
    new->heap = (point **) Checked_Malloc(num_elementos * sizeof(point *));
    new->free = 0;
    return new;
}

/**
 * [HeapInsertPoint description]
 * @param matrix [description]
 * @param new    [description]
 * @param I      [description]
 */
void HeapInsertPoint(DijkMatrix matrix, Acervo * new, point * I)
{
    // Insere novo elemento no fim e restabelece ordenação com FixUp
    new->heap[new->free] = I;
    (new->free)++;
    if(new->free == num_elementos - 1 )//condição!! Se for -1 é só inserir normalmente,caso contrário quer dizer que já está no acervo
    {
        num_elementos *= 2;
        new->heap = (point **) realloc(new->heap, sizeof(point *) * num_elementos);
    }

    new->heap[new->free] = NULL;

    FixUp(matrix, new, new->free - 1);
}

/**
 * [FixUp description]
 * @param matrix [description]
 * @param aux    [description]
 * @param Idx    [description]
 */
void FixUp(DijkMatrix matrix, Acervo * aux, int Idx)
{
    if(Idx == 0) return; // in this case the heap only have one point

    while (Idx > 0 && lessPri(get_Acum_Cost(matrix, aux->heap[(Idx - 1)/2]), get_Acum_Cost(matrix, aux->heap[Idx])))
    {
    
        exch(aux->heap[Idx], aux->heap[(Idx - 1)/2]);
        //Trocar na matriz a ordem
        Idx = (Idx - 1)/2;
    }
}

/**
 * [FixDown description]
 * @param matrix [description]
 * @param aux    [description]
 * @param Idx    [description]
 * @param N      [description]
 */
void FixDown(DijkMatrix matrix, Acervo * aux, int Idx, int N)
{
    int Child; /* índice de um nó descendente */
    while(2 * Idx < N - 1)  /* enquanto não chegar às folhas */
    {
        Child = 2 * Idx + 1;
        /* Selecciona o maior descendente. */
        /* Nota: se índice Child é N-1, então só há um descendente */
        if (Child < (N - 1) && lessPri(get_Acum_Cost(matrix, aux->heap[Child]), get_Acum_Cost(matrix, aux->heap[Child + 1]))) Child++;
        if (!lessPri(get_Acum_Cost(matrix, aux->heap[Idx]), get_Acum_Cost(matrix, aux->heap[Child]))) break; /* condição acervo */
        //trocar na matriz a ordem
        /* satisfeita */
        exch(aux->heap[Idx], aux->heap[Child]);
        /* continua a descer a árvore */
        Idx = Child;
    }
}

/**
 * [HeapDeleteMaxPoint description]
 * @param  matrix [description]
 * @param  aux    [description]
 * @return        [description]
 */
point * HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * aux)
{
    exch(aux->heap[0], aux->heap[aux->free - 1]);

    FixDown(matrix, aux, 0, aux->free - 1);
   //Passar na matriz para -2
    return aux->heap[--(aux->free)];
}

/**
 * [EmptyHeap description]
 * @param  aux [description]
 * @return     [description]
 */
int  EmptyHeap(Acervo * aux)
{
    return aux->free;
}
/*
point ** insert_Index_PQ( point ** aux, int tamanho_acervo, int pos_of_struct)
{
    point ** new = (point **)realloc(aux, sizeof(point *) * (tamanho_acervo + 1);

    new[pos_of_struct] = tamanho_acervo; 
    return new;
}
int ** INIT_Index_Matrix(int sizex, int sizey)
{
    int ** new = (int **)malloc(sizeof(point*) * sizey);

    for(int i = 0; i < sizey; i++)
    {
        int new[i] = (int *)malloc(sizeof(point*) * sizex);
        new[i] = -1;
    }

    new[0] = 0;
    return new;
}

int Search_position (point **aux,int pos_of_struct)
{
    int value = 0;

    

}

*/












