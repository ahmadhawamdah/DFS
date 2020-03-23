/*
Ahmad Hawamdah
ahawamda
pa5

Implementation file for FindComponent
*/


#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include"Graph.h"


int main(int argc, char* argv[]) {

    FILE *pIn, *pOut;
    int numStrgComp, size, i;
    numStrgComp = size = 0;
    int u, v;
    u = v = 1;
    
    
//   pIn = fopen(argv[1], "r");
//  pOut = fopen(argv[2], "w");

//    pIn = fopen("in.txt", "r");
//    pOut = fopen("out.txt", "w");
    
    if (pIn == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    if (pOut == NULL) {
        printf("FILE DOESN'T EXIST ... GET THE HELL OUT!");
        exit(1);
    }
    
    
    fscanf(pIn, "%d", &size);
    int n = size;
    Graph G = newGraph(n);
    
    List S = newList();
    List SG = newList();
    
    for (i=1; i<=n; i++) append(S, i);

    while(u != 0 || v != 0) {
        fscanf(pIn, "%d", &u);
        fscanf(pIn, "%d", &v);
    
        if(u == 0 && v == 0)
            break;
    
        addArc(G, u, v);
    }
    
    
    
    fprintf(pOut, "Adjacency list representation of G: ");
    printGraph(pOut, G);
    
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);
    
    for (i = 1; i <= getOrder(T); i++){
        if (getParent(T, i) == NIL) {
            numStrgComp++;
        }
    }
    
    fprintf(pOut, "\nG contains %d strongly connected components: \n", numStrgComp);

    moveBack(S);
    for (i = 1; i <= numStrgComp; i++) {
        fprintf(pOut, "Component %d: ", i);
        while (getParent(T, get(S)) != NIL) {   // parents
            prepend(SG, get(S));
            movePrev(S);
        }
        prepend(SG, get(S));    // children
        
        if(getIndex(S) != -1) {
            movePrev(S);
        }
        printList(pOut, SG);
        fprintf(pOut, "\n");
        clear(SG);
    }

    freeList(&S);
    freeList(&SG);
    freeGraph(&G);
    freeGraph(&T);
    fclose(pIn);
    fclose(pOut);
    
    return(0);
}

