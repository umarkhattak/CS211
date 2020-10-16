#include <stdio.h>

int main(int argc, char* argv[]){

    char given[30];
    char function[30];
    long int x;
    int y;
    int z;
    int command;

    FILE* file = fopen(argv[1], "r");

    fgets(given, 30, file);
    sscanf(given, "%d", &x); 

    while( fgets(given, 30, file) ){
        sscanf(given, "%s %d %d", function, &y, &z); 
    //    select multiple elements in array for set, comp, and get??
    //    char function2[4];
    //    int i;

    //    for(i = 0; i < strlen(function2); i++){
    //        function2[i] = function[i];
    //    }
            // if(function[0] == 'g'){ 
            // else{
            //     printf("error");
            // }
        switch(function[0]){ //gets first char of array of function
            case 's': //set
            command = 1;
            command = command << y; 

            if(!z){
                command = ~ command;
                x = x & command;
            }else{
                x = x | command;
            }

            printf("%d\n", x);
            break;

            case 'c': //comp
                command = 1;
                command = command << y;   
                x = x ^ command;   
                printf("%d\n", x);
                break;

            case 'g': //get 
                command = 1;
                command = command << y;  
                printf("%d\n",(x & command) && 1);
                break;
        
            default: //else which assuming will not happen
                printf("Error");
        }
    }
    return 0;
}