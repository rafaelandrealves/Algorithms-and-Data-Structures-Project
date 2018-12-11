
/******************************************************************************
 *
 * File Name: acervo.h

 * Author:    Rafael Cordeiro & Rodrigo Figueiredo
 * Revision:  11 Dez 2018
 *
 * NAME
 *     acervo.h - Headers of acervo.c
 *
*/


#ifndef _ACERVO_H
#define _ACERVO_H


#include "defs.h"

typedef struct acervoStruct Acervo;

#include "dijkstra.h"

int get_Idx_matrix(Acervo * heap, point virgula);

int getFree(Acervo * heap);

point getIPointFromHeap(Acervo * heap, int i);

void FreeAcervo(Acervo * heap, int ysize);

Acervo * InitAcervo(int sizey, int sizex);

void HeapInsertPoint(DijkMatrix matrix, Acervo * acervo, point I);

void FixUp(DijkMatrix matrix, Acervo * acervo, int Idx);

void FixDown(DijkMatrix matrix, Acervo * acervo, int Idx, int N);

point HeapDeleteMaxPoint(DijkMatrix matrix, Acervo * acervo);

int EmptyHeap(Acervo * acervo);

#endif
