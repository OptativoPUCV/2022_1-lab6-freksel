#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i,j,p,k,m,l;
    int A[10];
  //Filas 
    for(i=0;i<9;i++){
      for(p=0;p<10;p++){
        A[p]=0;
      }
      for(j=0;j<9;j++){
        if(n->sudo[i][j]!=0){
          k=n->sudo[i][j];
          if(A[k]!=0){
            return 0;
          }
          else{
            A[k]=1;
          }
        }
      }
    }
  //Columnas
  for(i=0;i<9;i++){
    for(p=0;p<10;p++){
      A[p]=0;
    }
    for(j=0;j<9;j++){
      if(n->sudo[j][i]!=0){
        k=n->sudo[j][i];
        if(A[k]!=0){
          return 0;
        }
        else{
          A[k]=1;
        }
      }
    }
  }
  //Matrices
  for(l=0;l<9;l++){
    for(p=0;p<10;p++){
      A[p]=0;
    }
    for(m=0;m<9;m++){
      int i=3*(l/3) + (m/3) ;
      int j=3*(l%3) + (m%3) ;
      if(n->sudo[i][j]!=0){
        k=n->sudo[i][j];
        if(A[k]!=0){
          return 0;
        }
        else{
          A[k]=1;
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* lista=createList();
    int i,j,k;
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(n->sudo[i][j]==0){
          for(k=1;k<10;k++){
            n->sudo[i][j]=k;
            if(is_valid(n)){
              Node* adj=copy(n);
              pushBack(lista,adj);
            }
          }
          n->sudo[i][j]=0;
          return lista;
        }
      }
    }
    return lista;
}


int is_final(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if (n->sudo[i][j]==0){
        return 0;
      }
    }
  }  
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S=createStack();
  push(S,initial);
  while(get_size(S)!=0){
    Node* wa=top(S);
    pop(S);
    if(is_final(wa)){
      return wa;
    }
    List* Alist=get_adj_nodes(wa);
    Node* Laux= first(Alist);
    while(Laux){
      push(S,Laux);
      Laux=next(Alist);
    }
    free(wa);
    (*cont)++;
  }
  printf("%d\n",*cont);
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/