
/******************************************************************************
 *
 * File Name: acervo.c

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  11 Dez 2018
 *
 * NAME
 *     acervo.c - Implementation of functions realted to the heap like insert points in the heap, remove, fixup, fixdown, ...
 *
*/


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

/**
 * [Macro to compare 2 values]
 * @param  A [value A]
 * @param  B [value B]
 * @return   [if(A>B) returns 1; else returns 0]
 */
#define lessPri(A, B) (A > B)

/**
 * [exchange 2 points]
 * @param  A [point A]
 * @param  B [point B]
 */
#define exch_pts(A, B) {point t = A; A = B; B = t; }

/**
 * [swap two integers]
 * @param  A [integer A]
 * @param  B [integer B]
 */
#define swap_int(A, B){int t = A; A = B; B = t; }


/**
 * [gets the position of one given point in the heap]
 * @param  heap    [the heap struct]
 * @param  virgula [point to get the index]
 * @return         [heap position of one given point]
 */
int get_Idx_matrix(Acervo * heap, point virgula)
{
    return heap->idx_matrix[virgula.y][virgula.x];
}
/**
 * [get the free variable of the heap struct]
 * @param  heap [heap struct]
 * @return     [value of free]
 */
int getFree(Acervo * heap)
{
    return heap->free;
}

/**
 * [given one index of the heap returns the point in 'i' position of the heap]
 * @param  heap [heap struct]
 * @param  i   [position in the heap to get the point]
 * @return     [point in the 'i' position]
 */
point getIPointFromHeap(Acervo * heap, int i)
{
    return heap->heap[i];
}

/**
 * [Frees all the memory related to the heap]
 * @param heap   [heap struct to be freed]
 * @param ysize [size of the index matrix contained in the heap struct]
 */
void FreeAcervo(Acervo * heap, int ysize)
{
    for(int i = 0; i < ysize; i++)
        free(heap->idx_matrix[i]);

    free(heap->idx_matrix);
    free(heap->heap);
    free(heap);
}

/**
 * [Inicializes the heap struct allocating memory and inicializing some values]
 * @param  sizey [size_x of the board to alloc the heap vector]
 * @param  sizex [size-Y of the board to alloc the heap vector]
 * @return       [heap allocated and inicialized]
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
 * [Inserts one point in the heap vector, incrementing the free variable, reestablishes the order in the heap]
 * @param matrix [graph matrix]
 * @param heap    [heap]
 * @param I      [point to insert in the heap]
 */
void HeapInsertPoint(DijkMatrix matrix, Acervo * acervo, point I)
{
    acervo->heap[acervo->free] = I;
    (acervo->free)++;

    // saves the heap position in the matrix of index
    acervo->idx_matrix[I.y][I.x] = acervo->free - 1;

    FixUp(matrix, acervo, acervo->free - 1);
}


/**
 * [Given one point reestablishes the order by priority in the heap from that point to the top of the heap]
 * @param matrix [graph matrix]
 * @param acervo    [heap struct]
 * @param Idx    [index of the point to fix up]
 */
void FixUp(DijkMatrix matrix, Acervo * acervo, int Idx)
{
    if(Idx == 0) return; // in this case the heap only have one point

    while (Idx > 0 && lessPri(get_Acum_Cost(matrix, acervo->heap[(Idx - 1)/2]), get_Acum_Cost(matrix, acervo->heap[Idx])))
    {
        point child_point = getIPointFromHeap(acervo, Idx);
        point dad_point = getIPointFromHeap(acervo, (Idx - 1)/2);

        // exchange the position of the points in the heap
        swap_int(acervo->idx_matrix[dad_point.y][dad_point.x], acervo->idx_matrix[child_point.y][child_point.x]);

        // exchange the 2 points in the heap
        exch_pts(acervo->heap[Idx], acervo->heap[(Idx - 1)/2]);

        Idx = (Idx - 1)/2;
    }
}

/**
 * [Given one point reestablishes the order by priority in the heap from that point to the bottom of the heap]
 * @param matrix [graph matrix]
 * @param acervo    [heap struct]
 * @param Idx    [index of the point to order]
 * @param N      [index of the last element of the heap]
 */
void FixDown(DijkMatrix matrix, Acervo * acervo, int Idx, int N)
{
    int Child;
    while(2 * Idx < N - 1) // while doesn't reach the leafs
    {
        Child = 2 * Idx + 1;
        // selects the most priority descendent
        if (Child < (N - 1) && lessPri(get_Acum_Cost(matrix, acervo->heap[Child]), get_Acum_Cost(matrix, acervo->heap[Child + 1]))) Child++;

        // to verify the heap condition
        if (!lessPri(get_Acum_Cost(matrix, acervo->heap[Idx]), get_Acum_Cost(matrix, acervo->heap[Child]))) break;

        point dad_point = getIPointFromHeap(acervo, Idx);
        point child_point = getIPointFromHeap(acervo, Child);
        exch_pts(acervo->heap[Idx], acervo->heap[Child]);

        swap_int(acervo->idx_matrix[dad_point.y][dad_point.x], acervo->idx_matrix[child_point.y][child_point.x]);

        /* continua a descer a árvore */
        Idx = Child;
    }
}

/**
 * [Removes the most priority point in the heap]
 * @param  matrix [graph matrix]
 * @param  acervo    [heap struct]
 * @return        [returns the deleted point]
 */
point HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * acervo)
{
    point to_remove = getIPointFromHeap(acervo, 0);
    point to_exch = getIPointFromHeap(acervo, acervo->free - 1);

    // reset the positions on those points in the heap
    acervo->idx_matrix[to_exch.y][to_exch.x] = 0;
    acervo->idx_matrix[to_remove.y][to_remove.x] = -2;

    // exchange the 2 points
    exch_pts(acervo->heap[0], acervo->heap[acervo->free - 1]);

    FixDown(matrix, acervo, 0, acervo->free - 1);

    return acervo->heap[--(acervo->free)];
}

/**
 * [Verify if the heap is empty by returning the free value. If free == 0 means that heap is empty]
 * @param  acervo [heap struct]
 * @return     [free value]
 */
int EmptyHeap(Acervo * acervo)
{
    return acervo->free;
}
