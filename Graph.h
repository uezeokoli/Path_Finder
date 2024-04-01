// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA2 
// *  Graph.h
// *  declare functions and construct the Graph 
// *****************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "List.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INF -1
#define NIL  0
#define white 2
#define gray  1
#define black 0


typedef struct GraphObj* Graph;

typedef struct GraphObj {
    List *neighbors;
    int* color;
    int* parent;
    int* dist;
    int order;
    int size;
    int source;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif