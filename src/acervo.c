



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
    if(new->free == num_elementos - 1)
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
