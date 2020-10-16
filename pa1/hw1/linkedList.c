#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int nodeValue;
  struct node *nodeNext;
}
Node;

void helper1(Node* nodeFront){
  Node* pointer;
  if(nodeFront == NULL){
    free(nodeFront);
  }

  while(nodeFront != NULL){
    pointer = nodeFront;
    nodeFront = nodeFront -> nodeNext;
    free(pointer);
  }

}

int main(int argc, char* argv[]){

  FILE* file;

  if((file = fopen(argv[1],"r")) == NULL){
    printf("error");
    exit(0);
  }

  Node* nodeFront = NULL; 
  nodeFront = (Node*)malloc(sizeof(struct node));

  if (nodeFront == NULL){ 
    return 1;
  }

  char x;
  int val;
  int ctr = 0;
  nodeFront -> nodeValue = -1;
  nodeFront -> nodeNext = NULL;
  Node* newFrontNode;


  while(!feof(file)){
    fscanf(file,"%c\t%d\n", &x, &val);

    if(x =='i'){
      Node* newNode = NULL; 
      newNode = malloc(sizeof( struct node));
      newNode -> nodeValue = val;
      newNode -> nodeNext = NULL;

      if(nodeFront -> nodeNext == NULL){ 
          nodeFront -> nodeNext = newNode;
      }
      else{
        Node* previousNode;
        Node* pointer;
        previousNode = nodeFront;
        pointer = nodeFront -> nodeNext;
        while(pointer != NULL){
          if(pointer -> nodeValue >= newNode -> nodeValue){
            previousNode -> nodeNext = newNode;
            newNode -> nodeNext = pointer;
            break;
          }
          previousNode = pointer;
          pointer = pointer -> nodeNext;
        }
        previousNode -> nodeNext = newNode;
      }
    }


    if(x == 'd'){

      Node* pointer;
      Node* previousNode;

      previousNode = nodeFront;
      pointer = nodeFront -> nodeNext;

      while(pointer != NULL){
        if(pointer -> nodeValue == val){
          previousNode -> nodeNext = pointer->nodeNext;
          pointer -> nodeNext = NULL;
          free(pointer);
          break;
        }
        previousNode = pointer;
        pointer = pointer -> nodeNext;
      }
    }
  }

  if(nodeFront -> nodeNext == NULL){
    free(nodeFront);
    fclose(file);
    printf("%d", 0);
    return 0;
  }

  newFrontNode = nodeFront -> nodeNext;
  free(nodeFront);
  Node* current = newFrontNode;

  while (current != NULL) {
    current = current -> nodeNext;
    ctr++;
  }

  current = newFrontNode;
  printf("%d\n", ctr);

  if(ctr == 0){
    return 0;
  }

  int repeat;
  printf("%d\t", current -> nodeValue);
  repeat = current -> nodeValue;
  current = current -> nodeNext;
  
  while (current != NULL) {
    if(repeat != current -> nodeValue){
      printf("%d\t", current -> nodeValue);
    }
    repeat= current -> nodeValue;
    current = current -> nodeNext;
  }

  helper1(newFrontNode);
  fclose(file);
  return 0;
}