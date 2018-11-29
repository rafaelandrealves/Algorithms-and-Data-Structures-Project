



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


int getFree(Acervo * new)
{
    return new->free;
}

point * getIPointFromHeap(Acervo * new, int i)
{
    return new->heap[i];
}

void FreeAcervo(Acervo * old)
{
    free(old->heap);
    free(old);
}

Acervo * InitAcervo()
{
    Acervo * new = (Acervo *) Checked_Malloc(sizeof(Acervo));
    new->heap = (point **) Checked_Malloc(sizeof(point *));
    new->free = 0;
    return new;
}



void HeapInsertPoint(DijkMatrix matrix, Acervo * new, point * I)
{
    // Insere novo elemento no fim e restabelece ordenação com FixUp
    new->heap[new->free] = I;
    (new->free)++;
    new->heap = (point **) realloc(new->heap, sizeof(point *) * (new->free + 1));
    new->heap[new->free] = NULL;

    FixUp(matrix, new, new->free - 1);
}


// Usando isto, adiciona-se o conceito de HEAPSORT para ser um acervo

void FixUp(DijkMatrix matrix, Acervo * aux, int Idx)
{
    if(Idx == 0) return; // in this case the heap only have one point

    while (Idx > 0 && lessPri(get_Acum_Cost(matrix, aux->heap[(Idx - 1)/2]), get_Acum_Cost(matrix, aux->heap[Idx])))
    {
        exch(aux->heap[Idx], aux->heap[(Idx - 1)/2]);
        Idx = (Idx - 1)/2;
    }
}


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
        /* satisfeita */
        exch(aux->heap[Idx], aux->heap[Child]);
        /* continua a descer a árvore */
        Idx = Child;
    }
}


point * HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * aux)
{
    exch(aux->heap[0], aux->heap[aux->free - 1]);

    FixDown(matrix, aux, 0, aux->free - 1);

    return aux->heap[--(aux->free)];
}

int  EmptyHeap(Acervo * aux)
{
    return aux->free;

}
