
#ifndef _ACERVO_H
#define _ACERVO_H

#include "defs.h"

typedef struct acervoStruct Acervo;

#include "dijkstra.h"

int get_Idx_matrix(Acervo * heap, point * virgula);

int getFree(Acervo * new);

point * getIPointFromHeap(Acervo * new, int i);

void FreeAcervo(Acervo * old, int ysize);

Acervo * InitAcervo(int sizey, int sizex);

void FixDown(DijkMatrix matrix, Acervo * aux, int Idx, int N);

void HeapInsertPoint(DijkMatrix matrix, Acervo * new, point * I);

void FixUp(DijkMatrix matrix, Acervo * aux, int Idx);

point * HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * aux);

int  EmptyHeap(Acervo * aux);

#endif
