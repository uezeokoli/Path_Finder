// /****************************************************************************************
// *  Graph.c
// *  Defines functions for Graph ADT
// *****************************************************************************************/


#include "Graph.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



/*** Constructors-Destructors ***/
Graph newGraph(int n){
    if (0 > n){
        fprintf(stderr,"Graph Error: Vertices can not be negative\n");
        exit(EXIT_FAILURE);
    }

    Graph new_graph = malloc(sizeof(GraphObj));
    new_graph->neighbors = (List *) calloc(n+1, sizeof(List));
    new_graph->color = (int *) calloc(n+1, sizeof(int));
    new_graph->parent = (int *) calloc(n+1, sizeof(int));
    new_graph->dist = (int *) calloc(n+1, sizeof(int));
    new_graph->order = n;
    new_graph->size = 0;
    new_graph->source = NIL;

    for(int i = 1; i<=(n);i++){
        new_graph->neighbors[i] = newList();
        new_graph->dist[i] = INF ;
        new_graph->parent[i] = NIL ;
        new_graph->color[i] = white;
    }
    return new_graph;
}
void freeGraph(Graph* pG){
    if(pG!=NULL && *pG!=NULL) { 
        Graph G = *pG;
        for (int i = 1; i <= G->order; i++){
            freeList(&G->neighbors[i]);
        }
        free(G->neighbors);
        free(G->color);
        free(G->dist);
        free(G->parent);
        free(*pG);
        *pG = NULL;
    }

}
/*** Access functions ***/
int getOrder(Graph G){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}
int getSize(Graph G){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}
int getSource(Graph G){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺). 
int getParent(Graph G, int u){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > G->order){
        fprintf(stderr,"Graph Error: calling getParent() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺). 
int getDist(Graph G, int u){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (1 > u || u > G->order){
        fprintf(stderr,"Graph Error: calling getDist() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->dist[u];

}
//getPath() has the precondition getSource(G)!=NIL, so BFS() must be called before getPath() is called.
//precondition 1 ≤ 𝑢 ≤ getOrder(𝐺). 
void getPath(List L, Graph G, int u){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (1 > u || u > G->order){
        fprintf(stderr,"Graph Error: calling getPath() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }

    if(getSource(G)==NIL){
        fprintf(stderr,"Graph Error: calling getPath() when BFS() has not been called");
        exit(EXIT_FAILURE);
    }


    if (u == getSource(G)){
        append(L,getSource(G));
    }
    else if (G->parent[u] == NIL){
        //printf("%d is not reachable from %d\n", u, getSource(G));
        append(L,NIL);
    }
    else{
        getPath(L,G,G->parent[u]);
        append(L,u);
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    if (G != NULL){
        G->size = 0;
        G->source = NIL;
        for (int i = 1; i <= G->order; i++){
            freeList(&G->neighbors[i]);
        }
    }
}
void addEdge(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if ((1 > u || u > G->order) || (1 > v || v > G->order)){
        fprintf(stderr,"Graph Error: calling addEdge() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }

    if (u <= G->order && v <=G->order){
        G->size--;
        //adding v to adj[u] list
        addArc(G,u,v);
        //adding u to adj[v] list
        addArc(G,v,u);

    }
}
void addArc(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr,"Graph Error: Graph is NULL\n");
        exit(EXIT_FAILURE);
    }

    if ((1 > u || u > G->order) || (1 > v || v > G->order)){
        fprintf(stderr,"Graph Error: calling addArc() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }

    for (moveFront(G->neighbors[u]); index(G->neighbors[u]) >= 0; moveNext(G->neighbors[u])){
        if (get(G->neighbors[u]) == v){
            return;
        }
    }
    if (u <= G->order && v <=G->order){
        // adding v to adj[u] list
        G->size++;
        if (length(G->neighbors[u]) == 0){
            append(G->neighbors[u],v);
        }
        else{
            moveFront(G->neighbors[u]);
            for (int x = 0; x<length(G->neighbors[u]);x++){
                if(v < get(G->neighbors[u])){
                    insertBefore(G->neighbors[u],v);
                    break;
                }
                if(x == length(G->neighbors[u])-1){
                    insertAfter(G->neighbors[u], v);
                    break;
                }
                moveNext(G->neighbors[u]);
            }
        }
    }
}
//Predition s < G->order
void BFS(Graph G, int s){
    if((1 > s || s > G->order)){
        fprintf(stderr,"Graph Error: calling BFS() on out of bound vertex\n");
        exit(EXIT_FAILURE);
    }

    for (int x = 1; x <= G->order;x++){
        if (x == s){
            continue;
        }
        G->color[x] = white;
        G->dist[x] = INF;
        G->parent[x] = NIL;
    }
    int x;
    G->source = s;
    G->color[s] = gray;     //discover the source s
    G->dist[s] = 0;
    G->parent[s] = NIL;
    List Queue = newList();
    append(Queue,s);
    while(length(Queue) != 0){
        x = front(Queue);
        deleteFront(Queue);
        for (moveFront(G->neighbors[x]); index(G->neighbors[x])>=0; moveNext(G->neighbors[x])){
            if (G->color[get(G->neighbors[x])] == white){
                G->color[get(G->neighbors[x])] = gray;
                G->dist[get(G->neighbors[x])] = G->dist[x] + 1;
                G->parent[get(G->neighbors[x])] = x;
                append(Queue, get(G->neighbors[x]));
            }
        }
        G->color[x] = black;       
    }
    freeList(&Queue);

}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if (G != NULL){
        for (int i = 1; i <= G->order;i++){
            fprintf(out,"%d: ",i);
            printList(out, G->neighbors[i]);
            fprintf(out,"\n");
        }
    }
}

