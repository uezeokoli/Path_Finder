// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA2 
// *  FindPath.c
// *  Outputs distance and path given # of vertices, edges, source, and destination
// *****************************************************************************************/

#include "Graph.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Invalid number of command line arguments\n");
        exit(EXIT_FAILURE);
    }
    FILE *output = fopen(argv[2],"w");
    FILE *input = fopen(argv[1], "r");
    if (input == NULL){
        // fclose(input);
        fclose(output);
        fprintf(stderr, "Invalid file\n");
        exit(EXIT_FAILURE);
    }

    char str_vertices[100];
    fgets(str_vertices,100,input);
    int vertices = atoi(str_vertices);

    Graph G = newGraph(vertices);
    
    char str_u[100];        //string of fist vertex
    char str_v[100];        //string of second vertex
    int u;          //fist vertex
    int v;          //second vertex
    while (1){
        fscanf(input, "%s", str_u);
        fscanf(input, "%s", str_v);
        u = atoi(str_u);
        v = atoi(str_v);
        if(u == 0){
            break;
        }
        addEdge(G,u,v);
    }

    printGraph(output,G);
    fprintf(output, "\n");

    List path = newList();      //initiating list for getPath()
    while (1){
        fscanf(input, "%s", str_u);
        fscanf(input, "%s", str_v);
        u = atoi(str_u);            //source vertex
        v = atoi(str_v);            //destination vertex
        if(u == 0){
            break;
        }
        BFS(G,u);
        getPath(path,G,v);
        fprintf(output,"The distance from %d to %d is ",u, v);

        if (getDist(G,v)==-1){
            fprintf(output,"infinity\n");
            fprintf(output,"No %d-%d path exists",u,v);
        }
        else{
            fprintf(output,"%d\n", getDist(G,v));
            fprintf(output,"A shortest %d-%d path is: ",u,v);
            printList(output,path);
        }

        fprintf(output,"\n\n");
        clear(path);
    }
}