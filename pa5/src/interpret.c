#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){
    if(argc != 2) {
      printf("Eror.\n");
      return 0;
    }

    char input[100][100];
    int registers[4];
    int x = 0;
    FILE *file = fopen(argv[1], "r");

    if(file == NULL){
      printf("Error\n");
      return 1;
    }

    while(fgets(input[x], 100, file)){
        input[x][strlen(input[x]) - 1] = '\0';
        x = x + 1;
    }
    fclose(file);

    for(int i = 0; i < x; ++i){
      char strings[20];
      strcpy(strings, input[i]);
      char *ptr1 = strtok(strings, " ");

      while(ptr1 != NULL){
            printf("%s\n", ptr1);
            ptr1 = strtok(NULL, " ");
        }
    }
    int ptr2 = 0;

    while(ptr2 < x){

        int a;
        int b;
        int currLine;

        if(!(strncmp((input[ptr2]), "add", 3))){
            int x = 2;
            int currNum = 0;

            if((input[ptr2][4] == 'a'))
                currNum = registers[0]; 
            else if((input[ptr2][4] == 'b'))
                currNum = registers[1];
            else if((input[ptr2][4] == 'c'))
                currNum = registers[2];
            else if((input[ptr2][4] == 'd'))
                currNum = registers[3];
            else{
                x = 0;
                char arr[16];

                for(int i = 0; i < strlen(input[ptr2]) - 7; i++){
                    arr[i] = input[ptr2][i + 4];
                    x = x + 1;
                }
                currNum = atoi(arr);                    
            }
            if((input[ptr2][x + 5] == 'a'))
                registers[0] += currNum;
            else if((input[ptr2][x + 5] == 'b'))
                registers[1] += currNum;
            else if((input[ptr2][x + 5] == 'c'))
                registers[2] += currNum;
            else if((input[ptr2][x + 5] == 'd'))
                registers[3] += currNum;
        }

        if(!(strncmp((input[ptr2]), "sub", 3))){
            int x = 2;
            int currNum = 0;

            if((input[ptr2][4] == 'a'))
                currNum = registers[0]; 
            else if((input[ptr2][4] == 'b'))
                currNum = registers[1];
            else if((input[ptr2][4] == 'c'))
                currNum = registers[2];
            else if((input[ptr2][4] == 'd'))
                currNum = registers[3];
            else{
                x = 0;
                char arr[16];

                for(int i = 0; i < strlen(input[ptr2]) - 7; i++){
                    arr[i] = input[ptr2][i + 4];
                    x = x + 1;
                }
                currNum = atoi(arr);                    
            }

            if((input[ptr2][x + 5] == 'a'))
                registers[0] = registers[0] - currNum;
            else if((input[ptr2][x + 5] == 'b'))
                registers[1] = registers[1] - currNum;
            else if((input[ptr2][x + 5] == 'c'))
                registers[2] = registers[2] - currNum;
            else if((input[ptr2][x + 5] == 'd'))
                registers[3] = registers[3] - currNum;
        }

        if(!(strncmp((input[ptr2]), "div", 3))){
            int x = 2;
            int currNum = 0;

            if((input[ptr2][4] == 'a'))
                currNum = registers[0]; 
            else if((input[ptr2][4] == 'b'))
                currNum = registers[1];
            else if((input[ptr2][4] == 'c'))
                currNum = registers[2];
            else if((input[ptr2][4] == 'd'))
                currNum = registers[3];
            else{
                x = 0;
                char arr[16];

                for(int i = 0; i < strlen(input[ptr2]) - 7; i++){
                    arr[i] = input[ptr2][i + 4];
                    x = x + 1;
                }
                currNum = atoi(arr);                    
            }

            if((input[ptr2][x + 5] == 'a'))
                registers[0] = registers[0] / currNum;
            else if((input[ptr2][x + 5] == 'b'))
                registers[1] = registers[1] / currNum;
            else if((input[ptr2][x + 5] == 'c'))
                registers[2] = registers[2] / currNum;
            else if((input[ptr2][x + 5] == 'd'))
                registers[3] = registers[3] / currNum;
        }

        if(!(strncmp((input[ptr2]), "mul", 3))){
            int currNum = 0;
            int x = 2;
            
            if((input[ptr2][4] == 'a'))
                currNum = registers[0]; 
            else if((input[ptr2][4] == 'b'))
                currNum = registers[1];
            else if((input[ptr2][4] == 'c'))
                currNum = registers[2];
            else if((input[ptr2][4] == 'd'))
                currNum = registers[3];
            else{
                char arr[16];
                x = 0;
                for(int i = 0; i < strlen(input[ptr2]) - 7; i++){
                    arr[i] = input[ptr2][i + 4];
                    x = x + 1;
                }
                currNum = atoi(arr);                    
            }

            if((input[ptr2][x + 5] == 'a'))
                registers[0] *= currNum;
            else if((input[ptr2][x + 5] == 'b'))
                registers[1] *= currNum;
            else if((input[ptr2][5+x] == 'c'))
                registers[2] *= currNum;
            else if((input[ptr2][x + 5] == 'd')){
                registers[3] *= currNum;
            }
        }

        if(!(strncmp((input[ptr2]), "read", 4))){
            int curr;
            scanf("%i", &curr);

            if((input[ptr2][5] == 'a'))
                registers[0] = curr;
            else if((input[ptr2][5] == 'b'))
                registers[1] = curr;
            else if((input[ptr2][5] == 'c'))
                registers[2] = curr;
            else if((input[ptr2][5] == 'd'))
                registers[3] = curr;
        }

        if(!(strncmp((input[ptr2]), "mov", 3))){
            int x = 2;
            int currNum = 0;

            if((input[ptr2][4] == 'a'))
                currNum = registers[0]; 
            else if((input[ptr2][4] == 'b'))
                currNum = registers[1];
            else if((input[ptr2][4] == 'c'))
                currNum = registers[2];
            else if((input[ptr2][4] == 'd'))
                currNum = registers[3];
            else{
                x = 0;
                char arr[16];

                for(int i = 0; i < strlen(input[ptr2]) - 7; i++){
                    arr[i] = input[ptr2][i + 4];
                    x = x + 1;
                }
                currNum = atoi(arr);                    
            }

            if((input[ptr2][x + 5] == 'a'))
                registers[0] = currNum;
            else if((input[ptr2][x + 5] == 'b'))
                registers[1] = currNum;
            else if((input[ptr2][x + 5] == 'c'))
                registers[2] = currNum;
            else if((input[ptr2][x + 5] == 'd'))
                registers[3] = currNum;
        }

        if(!(strncmp((input[ptr2]), "print", 5))){
            if((input[ptr2][6] == 'a'))
                printf("%i", registers[0]);
            else if((input[ptr2][6] == 'b'))
                printf("%i", registers[1]);
            else if((input[ptr2][6] == 'c'))
                printf("%i", registers[2]);
            else if((input[ptr2][6] == 'd'))
                printf("%i", registers[3]);
            else
                for(int i = 6; i < strlen(input[ptr2]) + 1; i++)
                    printf("%c", input[ptr2][i]);
        }
        
        if(!(strncmp((input[ptr2]), "j", 1))){
            char chars[20];
            strcpy(chars, input[ptr2]);
            char input[3];
            char x[16];
            char y[16];
            char* charTk = strtok(chars, " ");
            int ctr = 0;

            while (charTk){
                if(ctr == 1){
                    for(int i = 0; i < strlen(charTk); i++)
                        input[i] = charTk[i];
                    currLine = atoi(input);
                }

                if(ctr == 2){
                    if((charTk[0] == 'a') )
                        a = registers[0];
                    else if((charTk[0] == 'b') )
                        a = registers[1]; 
                    else if((charTk[0] == 'c') )
                        a = registers[2];
                    else if((charTk[0] == 'd') )
                        a = registers[3];
                    else{
                        for(int i = 0; i < strlen(charTk); i++)
                            x[i] = charTk[i];
                        a = atoi(x);
                    }
                }

                if(ctr == 3){
                    if((charTk[0] == 'a'))
                        b = registers[0];
                    else if((charTk[0] == 'b'))
                        b = registers[1]; 
                    else if((charTk[0] == 'c'))
                        b = registers[2];
                    else if((charTk[0] == 'd') )
                        b = registers[3];
                    else{
                        for(int i = 0; i < strlen(charTk); i++)
                            y[i] = charTk[i];
                        b = atoi(y);
                    }
                }
                ctr = ctr + 1;
                charTk = strtok(NULL, " ");
            }
        
        }

        if(!(strncmp((input[ptr2]), "je", 2))){ 
            if(a == b)
                ptr2 = currLine - 1;
        }

        if(!(strncmp((input[ptr2]), "jle", 3))){
            if(a <= b)
                ptr2 = currLine - 1;
        }
        else if(!(strncmp((input[ptr2]), "jl", 2))){
            if(a < b)
                ptr2 = currLine - 1;
        }

        if(!(strncmp((input[ptr2]), "jne", 3))){
            if(a != b)
                ptr2 = currLine - 1;
        }
        
        if(!(strncmp((input[ptr2]), "jmp", 3))){
            ptr2 = currLine - 1;
        }
                
        if(!(strncmp((input[ptr2]), "jge", 3))){
            if(a >= b)
                ptr2 = currLine - 1;
        }
        else if(!(strncmp((input[ptr2]), "jg", 2))){
            if(a > b)
                ptr2 = currLine - 1;
        }
        ptr2 = ptr2 + 1;
    }

    printf("\n");
}
