



#include "defs.h"
#include "util.h"
#include "dijkstra.h"


struct acervoStruct
{
    point ** heap;
    int free;
    int ** idx_matrix;
};


#include "acervo.h"

#define lessPri(A, B) (A > B)
#define exch(A, B) {Item t = A; A = B; B = t; }
#define swap_int(A, B){int t = A; A = B; B = t; }

int num_elementos = 200;

/**
 * [get_Idx_matrix description]
 * @param  heap    [description]
 * @param  virgula [description]
 * @return         [description]
 */
int get_Idx_matrix(Acervo * heap, point * virgula)
{
    return heap->idx_matrix[get_Y_From_Point(virgula)][get_X_From_Point(virgula)];
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
point * getIPointFromHeap(Acervo * new, int i)
{
    return new->heap[i];
}

/**
 * [FreeAcervo description]
 * @param old [description]
 */
void FreeAcervo(Acervo * old, int ysize)
{
    for(int i = 0; i < old->free; i++)
        if(old->heap[i] != NULL)
            free(old->heap[i]);

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
    new->heap = (point **) Checked_Malloc(num_elementos * sizeof(point *));
    new->free = 0;

    new->idx_matrix = (int **) Checked_Malloc(sizey * sizeof(int*));
    for(int i = 0; i < sizey; i++)
    {
        new->idx_matrix[i] = (int *) Checked_Malloc(sizex * sizeof(int));
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

    int xcoor = get_X_From_Point(I);
    int ycoord = get_Y_From_Point(I);
    new->idx_matrix[ycoord][xcoor] = new->free - 1;

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
        point * child_point = getIPointFromHeap(aux, Idx);
        point * dad_point = getIPointFromHeap(aux, (Idx - 1)/2);

        int xdad = get_X_From_Point(dad_point);
        int ydad = get_Y_From_Point(dad_point);
        int xchild = get_X_From_Point(child_point);
        int ychild = get_Y_From_Point(child_point);

        swap_int(aux->idx_matrix[ydad][xdad], aux->idx_matrix[ychild][xchild]);
        
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

        point * dad_point = getIPointFromHeap(aux, Idx);
        point * child_point = getIPointFromHeap(aux, Child);
        exch(aux->heap[Idx], aux->heap[Child]);

        int xdad = get_X_From_Point(dad_point);
        int ydad = get_Y_From_Point(dad_point);
        int xchild = get_X_From_Point(child_point);
        int ychild = get_Y_From_Point(child_point);

        swap_int(aux->idx_matrix[ydad][xdad], aux->idx_matrix[ychild][xchild]);

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
    point * to_remove = getIPointFromHeap(aux, 0);
    point * to_exch = getIPointFromHeap(aux, aux->free - 1);

    // int x_remove = get_X_From_Point(to_remove);
    // int y_remove = get_Y_From_Point(to_remove);
    // int x_exch = get_X_From_Point(to_exch);
    // int y_exch = get_Y_From_Point(to_exch);


    // swap_int(aux->idx_matrix[y_exch][x_exch], aux->idx_matrix[y_remove][x_remove]);
    //
    // aux->idx_matrix[y_remove][x_remove] = -2;

    // aux->idx_matrix[get_Y_From_Point(to_exch)][get_X_From_Point(to_exch)] = aux->idx_matrix[get_Y_From_Point(to_remove)][get_X_From_Point(to_remove)]

    aux->idx_matrix[get_Y_From_Point(to_exch)][get_X_From_Point(to_exch)] = 0;
    aux->idx_matrix[get_Y_From_Point(to_remove)][get_X_From_Point(to_remove)] = -2;

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
