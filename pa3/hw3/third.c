#include <stdio.h>

int main(int argc, char* argv[]){

    unsigned short int givenArgument = atoi(argv[1]); //reads the number given
    int unsignedShortBits[16]; //unsigned shorts are 2 types or 16 bits
    int x = 0;
    int y = 0;

    while(givenArgument){
        unsignedShortBits[x] = givenArgument % 2;
        givenArgument = givenArgument / 2;
        x = x + 1; 
    }

    while(x > y && unsignedShortBits[x] != unsignedShortBits[y]){
        y = y + 1;
        x = x - 1;
    }

    if(x > y){ //will be palindrome
        printf("Is-Palindrome\n");
    }else{
        printf("Not-Palindrome\n");
    }

    return 0;
}