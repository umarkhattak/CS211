#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *nextNode;
}
Node;

int helper1(Node* hst[], Node* node){
    int idx = node -> value % 10000; 
    int ctr = 0;

    if(idx < 0){
        idx = idx + 10000;
    }
    if(hst[idx] == NULL){
        hst[idx] = node;
    } 
    else{
        Node* ptr;
        int y = 0;
        ptr = hst[idx];
        Node* nodePrev = NULL;
        while(ptr != NULL){

            if(ptr -> value != node -> value){
                nodePrev = ptr;
                ptr = ptr -> nextNode;

            }
            else{
                y = 1;
                free(node);
                break;
            }

        }

        if(y == 0){
            nodePrev -> nextNode = node;
        }
        ctr++;
    }
    return ctr;
}

int helper2(Node* hst[], int x){
    int idx = x % 10000;
    int ctr = 0;    
    Node* ptr;

    if(idx < 0){
        idx = idx + 10000;
    }

    ptr = hst[idx];

    while(ptr != NULL){
        if(ptr == NULL){
            return 0;
        }
        if(ptr -> value == x){
            ctr++;
            break;
        }
        else{
            ptr = ptr -> nextNode;
        }
    }
    return ctr;
}

void helper3(Node* pointerIdx){
    Node* pointer;

    while(pointerIdx != NULL){
        pointer = pointerIdx;
        pointerIdx = pointerIdx -> nextNode;
        free(pointer);
    }
}

Node* helper4(int x){
    Node* node = NULL; 
    node = (struct node*)malloc(sizeof(struct node));
    node -> value = x;
    node -> nextNode = NULL;
    return node;
}

Node* hst[10000];

int main(int argc, char* argv[]){ 

    FILE* input;

    if((input = fopen(argv[1], "r")) == NULL){
      printf("error");
      exit(0);
    }

    Node* pointerIdx;
    int idx;
    int x;
    int ctr1=0;
    int ctr2=0;
    char a;

    while(!feof(input)){
      fscanf(input, "%c\t%d\n", &a, &x);
      if(a == 'i'){
        Node* node = helper4(x);
        ctr1 += helper1(hst, node);
      }
      if(a == 's'){
        ctr2 += helper2(hst, x);
      }
    }

    printf("%d\n",ctr1);
    printf("%d",ctr2);

    for(idx = 0; idx < 10000; idx++){
        pointerIdx = hst[idx];
        helper3(pointerIdx);
    }
    fclose(input);
    return 0;
}