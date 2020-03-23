/*
Ahmad Hawamdah
ahawamda
pa5

Graph ADT implementation
*/


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2


typedef struct GraphObj {
    List *adjL;
    int *p; // parent
    int *fin; // finish
    int *col; // color
    int *disc; // discover
    int size;
    int order;
    
    
} GraphObj;


// return a reference to a new graph object containing n vertices and no edges
Graph newGraph (int n) {
    
      
    Graph G = malloc(sizeof(GraphObj));
    G->adjL = malloc((n+1) * sizeof(List));
    G->p = malloc((n+1) * sizeof(int));
    G->col = malloc((n+1) * sizeof(int));
    G->disc = malloc((n+1) * sizeof(int));
    G->fin = malloc((n+1) * sizeof(int));
    G->order = n;
    G->size = 0;

    
    for (int ind = 0; ind <= getOrder(G); ind++) {
           G->adjL[ind] = newList();
           G->col[ind] = WHITE;
           G->p[ind] = NIL;
           G->disc[ind] = UNDEF;
           G->fin[ind] = UNDEF;
       }
    
    return(G);
}


// frees all dynamic memory associated with the Graph *pG
// sets the handle *pG to NULL
void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
    for (int ind = 0; ind <= getOrder(*pG); ind++) {
        freeList(&((*pG))->adjL[ind]); // free List
    }
        free((*pG)->adjL);
        free((*pG)->col);
        free((*pG)->disc);
        free((*pG)->fin);
        free((*pG)->p);
        free(*pG); // free graph
        *pG = NULL;
    }
}


// returns the number of vertices in G
int getOrder(Graph G) {
    return (G->order);
}


int getSize(Graph G) {
    return (G->size);
}


int getFinish(Graph G, int u) {
    return (G->fin[u]);
}


int getParent(Graph G, int u) {
    if (G==NULL) {
        printf("Graph Error: calling getParent() on a NULL graph\n");
            exit(1);
        exit(1);
    }
    
    if (u < 1 || u > G->order) {
      printf("Graph Error: calling getParent() on vertices u exceeded boundris\n");
      exit(1);
      }
    
    return (G->p[u]);
}


int getDiscover(Graph G, int u) {
    return (G->disc[u]);
}



void addEdge(Graph G, int u, int v) {

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
      
}
        

void addArc(Graph G, int u, int v) {

    if (u < 1 || u > G->order) {
    printf("Graph Error: calling addArc() on vertices u exceeded boundris\n");
    exit(1);
    }

     List adjL1 = G->adjL[u];
    
    
    if(length(adjL1) == 0){
        append(adjL1, v);
        G->size++;
    } else {
        moveFront(adjL1);
        while(get(adjL1) < v) {
             moveNext(adjL1);
             if(getIndex(adjL1) == -1)
                 break;
         }

         if (getIndex(adjL1) == -1) { // check NULL status
             append(adjL1, v);
             G->size++;
         } else {
             insertBefore(adjL1, v);
             G->size++;
        }
    }
}





void visit(Graph G, int x, int *t, List S) {
     
    List L2 = G->adjL[x];
    
    G->disc[x] = ++(*t);
    G->col[x] = GRAY;
    
    moveFront(L2);
    while (getIndex(L2) > -1) {
        int y = get(L2);
        
        if (G->col[y] == WHITE) {
            G->p[y] = x;
            visit(G, y, t, S);
        }
        moveNext(L2);
    }
    G->col[x] = BLACK;
    G->fin[x] = ++(*t);
    prepend(S,x);
    
}


void DFS(Graph G, List S) {
    
    int time = 0;
    List C = copyList(S);
    clear(S);
    
    for (int ind = 1; ind <= getOrder(G); ind++) {
        G->col[ind] = WHITE;
        G->p[ind] = NIL;
        G->disc[ind] = UNDEF;
        G->fin[ind] = UNDEF;
    }
    
    moveFront(C);
    while (getIndex(C) > -1) {
        int x = get(C);
        if (G->col[x] == WHITE) {
            visit(G, x, &time, S);
        }
        moveNext(C);
    }
    freeList(&C);
}


void printGraph(FILE* out, Graph G) {
    if( G==NULL ) {
       printf("Graph Error: calling printGraph() on NULL Graph reference\n");
       exit(1);
    }
    
     for (int ind = 1; ind <= getOrder(G); ind++) {
         List L = G->adjL[ind];
         if (length(L) != 0) {
             moveFront(L);
             int v = get(L);
             fprintf(out, "\n%d: ", ind);
             while (getIndex(L) > -1){
                 v = get(L);
                 fprintf(out, "%d ", v);
                 moveNext(L);
             }
         } else {
              fprintf(out, "\n%d: ", ind);
         }
    }
    fprintf(out, "\n");
}



Graph copyGraph(Graph G) {
    
    if( G==NULL ) {
       printf("Graph Error: calling printGraph() on NULL Graph reference\n");
       exit(1);
    }
    
    
    int n = getOrder(G);
    Graph A = newGraph(n);
   
     for (int ind = 1; ind <= getOrder(G); ind++) {
         List L = G->adjL[ind];
         if (length(L) != 0) {
                A->adjL[ind] = copyList(L);
             }
         }
    return(A);
}


Graph transpose(Graph G) {
    
    if( G==NULL ) {
       printf("Graph Error: calling printGraph() on NULL Graph reference\n");
       exit(1);
    }
    
    int n = getOrder(G);
    Graph A = newGraph(n);

     for (int ind = 1; ind <= getOrder(G); ind++) {
         List L = G->adjL[ind];
         if (length(L) != 0) {
             moveFront(L);
             while (getIndex(L) > -1){
                 int u = get(L);
                 addArc(A, u, ind);
                 moveNext(L);
             }
         }
    }
    return(A);
}

