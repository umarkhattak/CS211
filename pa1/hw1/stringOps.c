#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    char* input;
    int i;
    for(i =1 ; i < argc; i++){
        
        int j;
        input = argv[i];
        int strLength;
        strLength=strlen(input);

        for(j = 0; j < strLength; j++){
            if(input[j]=='A'||input[j]=='a'||
                input[j]=='E'||input[j]=='e'||
                input[j]=='I'||input[j]=='i'||
                input[j]=='O'||input[j]=='o'||
                input[j]=='U'||input[j]=='u'){
                printf("%c",input[j]);
            }
        }
    }
    return 0;
}