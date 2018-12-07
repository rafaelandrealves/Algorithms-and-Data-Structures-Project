



#include "defs.h"
#include "util.h"
#include "dijkstra.h"


struct acervoStruct
{
    point * heap;
    int free;
    short ** idx_matrix;
};


#include "acervo.h"

#define lessPri(A, B) (A > B)
#define exch(A, B) {point t = A; A = B; B = t; }
#define swap_int(A, B){int t = A; A = B; B = t; }

/**
 * [get_Idx_matrix description]
 * @param  heap    [description]
 * @param  virgula [description]
 * @return         [description]
 */
int get_Idx_matrix(Acervo * heap, point virgula)
{
    return heap->idx_matrix[virgula.y][virgula.x];
}
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
point getIPointFromHeap(Acervo * new, int i)
{
    return new->heap[i];
}

/**
 * [FreeAcervo description]
 * @param old [description]
 */
void FreeAcervo(Acervo * old, int ysize)
{
    for(int i = 0; i < ysize; i++)
        free(old->idx_matrix[i]);

    free(old->idx_matrix);
    free(old->heap);
    free(old);
}

/**
 * [InitAcervo description]
 * @return [description]
 */
Acervo * InitAcervo(int sizey, int sizex)
{
    Acervo * new = (Acervo *) Checked_Malloc(sizeof(Acervo));
    new->heap = (point *) Checked_Malloc(sizey*sizex * sizeof(point));
    new->free = 0;

    new->idx_matrix = (short **) Checked_Malloc(sizey * sizeof(short*));
    for(int i = 0; i < sizey; i++)
    {
        new->idx_matrix[i] = (short *) Checked_Malloc(sizex * sizeof(short));
        for(int j = 0; j < sizex; j++)
            new->idx_matrix[i][j] = -1; // never entered the heap_tree
    }
    return new;
}

/**
 * [HeapInsertPoint description]
 * @param matrix [description]
 * @param new    [description]
 * @param I      [description]
 */
void HeapInsertPoint(DijkMatrix matrix, Acervo * new, point I)
{
    // Insere novo elemento no fim e restabelece ordenação com FixUp
    new->heap[new->free] = I;
    (new->free)++;

    new->idx_matrix[I.y][I.x] = new->free - 1;

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
        point child_point = getIPointFromHeap(aux, Idx);
        point dad_point = getIPointFromHeap(aux, (Idx - 1)/2);

        swap_int(aux->idx_matrix[dad_point.y][dad_point.x], aux->idx_matrix[child_point.y][child_point.x]);

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

        point dad_point = getIPointFromHeap(aux, Idx);
        point child_point = getIPointFromHeap(aux, Child);
        exch(aux->heap[Idx], aux->heap[Child]);

        swap_int(aux->idx_matrix[dad_point.y][dad_point.x], aux->idx_matrix[child_point.y][child_point.x]);

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
point HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * aux)
{
    point to_remove = getIPointFromHeap(aux, 0);
    point to_exch = getIPointFromHeap(aux, aux->free - 1);

    aux->idx_matrix[to_exch.y][to_exch.x] = 0;
    aux->idx_matrix[to_remove.y][to_remove.x] = -2;

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
