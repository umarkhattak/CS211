#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *nodeLeft;
    struct node* nodeRight;
}
Node;

void helper1(Node* node){
  if(node != NULL){
        helper1(node -> nodeLeft);
        printf("%d\t", node -> value);
        helper1(node -> nodeRight);
    }
}

void helper2(Node* node){
  if(node == NULL){
      return;
    }
    helper2(node -> nodeLeft);
    helper2(node -> nodeRight);
    free(node);
    return;
}

Node* helper3(Node* node, Node* nodeNew){
    if(node == NULL){
        return nodeNew;
    }
    if(node -> value > nodeNew -> value){
        node -> nodeLeft = helper3(node -> nodeLeft, nodeNew);
    }
    else if(node -> value < nodeNew -> value){
        node -> nodeRight = helper3(node -> nodeRight, nodeNew);
    }
    else{
        free(nodeNew);
    }
    return node;
}

Node* helper4(int x){
    Node* nodeNew = NULL; 
    nodeNew = (struct node*)malloc(sizeof(struct node));
    nodeNew -> nodeRight = NULL;
    nodeNew -> nodeLeft = NULL;
    nodeNew -> value = x;
    return nodeNew;
}

int main(int argc, char* argv[]){

    FILE* input;

    if((input = fopen(argv[1], "r")) == NULL){
      printf("error");
      exit(0);
    }

    else{
        int x;
        char a;
        Node* node = NULL;
        while(!feof(input)){
            fscanf(input, "%c\t%d\n", &a, &x);
            if(a == 'i'){
                Node* nodeNew = helper4(x);
                node = helper3(node,nodeNew);
            }
        }
        helper1(node);
        helper2(node);
    }
    fclose(input);
    return 0;
}