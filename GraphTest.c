// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA2 
// *  GraphTest.c
// *  Test Client for Graph ADT
// *****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

void TestFunctions(){
   //Test getOrder()
   Graph G = newGraph(20);
   assert(getOrder(G) == 20);
   freeGraph(&G);
   printf("getOrder() works!\n");
   //Test getSize()
   G = newGraph(20);
   assert(G->size == 0);
   addEdge(G,1,2);
   addEdge(G,1,3);
   assert(G->size == 2);
   makeNull(G);
   assert(G->size == 0);
   freeGraph(&G);
   printf("getSize() works!\n");
   //Test addEdge()
   G = newGraph(20);
   assert(G->size == 0);
   assert(length(G->neighbors[1]) == 0);
   addEdge(G,1,2);
   addEdge(G,1,3);
   assert(G->size == 2);
   addEdge(G,1,4);
   addEdge(G,1,5);
   assert(G->size == 4);
   assert(length(G->neighbors[1]) != 0);
   assert(length(G->neighbors[2]) != 0);
   freeGraph(&G);
   printf("addEdge() works!\n");
   //Test addArc
   G = newGraph(20);
   assert(G->size == 0);
   assert(length(G->neighbors[1]) == 0);
   addArc(G,1,2);
   addArc(G,1,3);
   assert(G->size == 2);
   addArc(G,1,4);
   addArc(G,1,5);
   assert(G->size == 4);
   assert(length(G->neighbors[1]) != 0);
   assert(length(G->neighbors[2]) == 0);
   freeGraph(&G);
   printf("addArc() works!\n");
   //Test BFS()
   G = newGraph(20);
   assert(G->source == NIL);
   assert(G->dist[1] == INF);
   assert(G->parent[1] == NIL);
   assert(G->color[1] == white);
   addEdge(G,1,2);
   addEdge(G,1,3);
   BFS(G,1);
   assert(G->source != NIL);
   assert(G->dist[1] != INF);
   assert(G->parent[1] == NIL);
   assert(G->color[1] != white);
   freeGraph(&G);
   printf("BFS() works!\n");
   //Test getSource()
   G = newGraph(20);
   assert(G->source == NIL);
   addEdge(G,1,2);
   addEdge(G,1,3);
   BFS(G,1);
   assert(G->source != NIL);
   freeGraph(&G);
   printf("getSource() works!\n");
   //Test getParent() 
   G = newGraph(20);
   assert(G->parent[1] == NIL);
   addEdge(G,1,2);
   addEdge(G,1,3);
   BFS(G,1);
   assert(G->parent[1] == NIL);
   BFS(G,2);
   assert(G->parent[2 != NIL]);
   freeGraph(&G);
   printf("getParent() works!\n");
   //Test getDist() 
   G = newGraph(20);
   assert(G->dist[1] == INF);
   addEdge(G,1,2);
   addEdge(G,1,3);
   BFS(G,1);
   assert(G->dist[1] != INF);
   freeGraph(&G);
   printf("getDist() works!\n");
   //Test getPath() 
   G = newGraph(20);
   List Path = newList();
   List ExpectedPath = newList();
   addEdge(G,1,2);
   addEdge(G,1,3);
   BFS(G,3);
   append(ExpectedPath,3);
   append(ExpectedPath,1);
   append(ExpectedPath,2);
   getPath(Path,G,2);
   assert(equals(Path, ExpectedPath));
   freeGraph(&G);
   freeList(&Path);
   freeList(&ExpectedPath);
   printf("getPath() works!\n");
   //Test makeNull()
   G = newGraph(20);
   assert(G->size == 0);
   addEdge(G,1,2);
   addEdge(G,1,3);
   assert(G->size == 2);
   makeNull(G);
   assert(G->size == 0);
   freeGraph(&G);
   printf("makeNull() works!\n");

   //All Functions work
   printf("All Functions are working!\n");


}


int main(int argc, char* argv[]){

   TestFunctions();

}