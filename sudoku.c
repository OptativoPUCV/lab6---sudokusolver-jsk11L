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
  int fila[10];
  int columna[10];
  int matriz[10];

  for(int i = 0; i < 9; i++){
    
    for(int ceros = 0; ceros < 10; ceros++){
      fila[ceros] = 0;
      columna[ceros] = 0;
      matriz[ceros] = 0;
    }
    
    for(int k = 0; k < 9; k++){
      
      if(n->sudo[i][k] != 0){
        if(fila[n->sudo[i][k]] == 1) return 0;
        else fila[n->sudo[i][k]] = 1;
      }

      if(n->sudo[k][i] != 0){
        if(columna[n->sudo[k][i]] == 1) return 0;
        else columna[n->sudo[k][i]] = 1;
      }
      
      int matrizI = 3*(i/3) + (k/3);
      int matrizJ = 3*(i%3) + (k%3);

      if(n->sudo[matrizI][matrizJ] != 0){
        if(matriz[n->sudo[matrizI][matrizJ]] == 1) return 0;
        else matriz[n->sudo[matrizI][matrizJ]] = 1;
      } 
      
    }
    
  }
  
  return 1;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0 ){
          for(int aux = 1; aux < 10; aux++){
            n->sudo[i][j] = aux;
            Node* nuevoNodo = copy(n);
            if(is_valid(nuevoNodo) == 1){
              pushBack(list,nuevoNodo);
            }
          }
        }
      }
    }
    return list;
}

int is_final(Node* n){
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila,initial);

  while(is_empty(pila) != 1){
    Node* primero = top(pila);
    pop(pila);
    
    if(is_final(primero) == 1) return primero;
    List* lista = get_adj_nodes(primero);

    Node* nodos = first(lista);
    while(nodos != NULL){
      push(pila,nodos);
      nodos = next(lista);
    }
  }
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