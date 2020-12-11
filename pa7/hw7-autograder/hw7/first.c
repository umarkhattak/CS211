#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//last assignment boyyy here we go

int main(int argc, char* argv[]){

    FILE* file = fopen (argv[1], "r");
    int input = 0;
    char inputSize[60];

	while(fgets(inputSize, sizeof(inputSize), file)){
	    input++;
    }
    fclose(file);
    file = fopen (argv[1], "r");

    char* *variablesI;
    char* *variablesO;
    char* *variablesT = malloc(sizeof(char*)*input); 

    int idxI = 0;
    int inputLength = 0;
    int idxO = 0;
    int outputLength = 0;
    int length = 0;
    int count = 1;

    
    for(int i = 0; i < input; i++){
        variablesT[i] = malloc((10) * sizeof(char));
    }
    
    while(count <= 2 && fgets(inputSize, sizeof(inputSize), file)){
        size_t stringLength = strlen(inputSize);
        int ctr = 1;
        char chars[60];

        if(stringLength > 0 && inputSize[stringLength-1] == '\n'){
            inputSize[--stringLength] = '\0';
        } 

        strcpy(chars, inputSize);
        char* stringTk = strtok(chars, " ");

        while(stringTk){
            if(ctr == 2){
                if(count == 1){
                    inputLength = atoi(stringTk);
                    variablesI  = malloc(sizeof(char*)*inputLength); 

                    for(int i = 0; i <= inputLength - 1; i++){
                        variablesI[i] = malloc((10) * sizeof(char));
                    }
                }
                else if(count == 2){
                    outputLength = atoi(stringTk);
                    variablesO  = malloc(sizeof(char*)*outputLength);

                    for(int i = 0; i < outputLength; i++){
                        variablesO[i] = malloc((10) * sizeof(char));
                    }
                }
            }
            else if(ctr >= 3){
                if(count == 1){
                    strcpy(variablesI[idxI], stringTk);
                    idxI = idxI + 1;;
                }
                else if(count == 2){
                    strcpy(variablesO[idxO], stringTk);
                    idxO = idxO + 1;
                }
            }
            ctr += 1;
            stringTk = strtok(NULL, " ");
        }
        count += 1;
    }
 
    int** x = malloc((int)pow(2, idxI) * sizeof(int*));
    
    for(int i = 0; i < (int)pow(2, idxI); i++){ 
        x[i] = malloc((idxI+idxO) * sizeof(int));
    }

    int** var = malloc((int)pow(2, idxI) * sizeof(int*));
    int i;
    int j;
    int y;
    int bin[32]; 

    for(i = 0; i < (int)pow(2, idxI); i++){
        var[i] = malloc((input) * sizeof(int));
    }

    for(j = 0; j < (int)pow(2, idxI); j++){
        y = j;

        int k = 0;

        for(k = 0; k <= 31; k++){
            bin[k] = 0;
        }

        int i = 0; 

        for(i = 0; y > 0; i++){    
            bin[31 - i] = y % 2;
            y = y / 2;    
        } 
        for(int i = idxI - 1; i >= 0; i--){
            x[j][i] = bin[32 - idxI + i];
        }
    }

    while(fgets(inputSize, sizeof(inputSize), file)) {
        size_t stringLength = strlen(inputSize);

        if(stringLength > 0 && inputSize[stringLength-1] == '\n'){
            inputSize[--stringLength] = '\0';
        }

        int ctr = 1;
        int c1 = -1;
        int c2 = -1;
        int c1temp = -1;
        int c2temp = -1;

        char chars[60];
        strcpy(chars, inputSize);
        char* stringTk = strtok(chars, " ");

        char char1[10];
        char char2[10];
        char charOutput[10]; 
        char function[5];

        while(stringTk){
            if(ctr == 1){
                strcpy(function, stringTk);
            }
            else if(ctr == 2){
                strcpy(char1, stringTk);
            }
            else if(ctr == 3){
                strcpy(char2, stringTk);
            }
            else if(ctr == 4){
                strcpy(charOutput, stringTk);
            }
            ctr += 1;
            stringTk = strtok(NULL, " ");
        }

        for (int i = 0; i < idxI; i++){
            if((strcmp(char1, variablesI[i]) == 0)){
                c1 = i;
            }
            if((strcmp(char2, variablesI[i]) == 0)){
                c2 = i;
            }
        }
        
        for (int i = 0; i < length; i++){
            if((strcmp(char1, variablesT[i]) == 0)){
                c1temp = i;
            }
            if((strcmp(char2, variablesT[i]) == 0)){
                c2temp = i;
            }
        }

        // int i;
        // int j;

        for (int i = 0; i < (int)pow(2, idxI); i++){
            int rev = 1;
            int placer = 1;
            int indexVal = -1;
            int a = -1;
            int b = -1;

            if (c1 == -1){
                a = var[i][c1temp];
            }
            else{
                a = x[i][c1];
            }

            if (c2 == -1 && (strcmp(function, "NOT") != 0)){
                b = var[i][c2temp];
            }
            else if (strcmp(function, "NOT") != 0){
                b = x[i][c2];
            }

            if (strcmp(function, "NOT") == 0){
                indexVal = !(a);
                strcpy(charOutput, char2);
            }
            else if (strcmp(function, "AND") == 0){
                indexVal = (a)&(b);
            }
            else if (strcmp(function, "NAND") == 0){
                indexVal = !((a)&(b));
            }
            else if (strcmp(function, "OR") == 0){
                indexVal = (a)|(b);
            }
            else if (strcmp(function, "NOR") == 0){
                indexVal = !((a)|(b));
            }
            else if (strcmp(function, "XOR") == 0){
                indexVal = (a) ^ (b);
            }

            for (int j = 0; j < idxO; j++){
                if( (strcmp(charOutput, variablesO[j]) == 0) ){
                    x[i][idxI + j] = indexVal;
                    rev = 0;
                }
            }

            if (rev){ 
                for (int j = 0; j < length; j++){
                    if( (strcmp(charOutput, variablesT[j]) == 0) ){
                        var[i][j] = indexVal;
                        placer = 0;
                    }
                }
            }

            if (placer && rev){
                strcpy(variablesT[length], charOutput);
                var[i][length] = indexVal;
                length += 1;
            }
        }    
    }

    for (int i = 0; i < (int)pow(2, idxI); i++){
        for (int j = 0; j < idxI + idxO; j++){
            printf("%d ", x[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < pow(2, idxI); i++){
        free(var[i]);
    }

    for (int i = 0; i < pow(2, idxI); i++){
        free(x[i]);
    }

    for (int i = 0; i < idxI; i++){
        free(variablesI[i]);
    }

    for (int i = 0; i < idxO; i++){
        free(variablesO[i]);
    }

    for (int i = 0; i < input; i++){
        free(variablesT[i]);
    }

    free(var);
    free(x);
    free(variablesI);
    free(variablesO);
    free(variablesT);
}