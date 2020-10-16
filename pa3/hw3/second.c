#include <stdio.h>

int main(int argc, char* argv[]){

    long int givenArgument = atoi(argv[1]); //reads the number given
    long int bitCurr = 0;
    long int bitPrev = 0;      
    long int parityPairs = 0;
    long int counterOnes = 0;

    while(givenArgument){
        bitCurr = givenArgument & 01;
        
        if( bitPrev && bitCurr ){  
            parityPairs = parityPairs + 1;
            bitPrev = 0;
        }else
            bitPrev = bitCurr;
        
        if(bitCurr)                     
            counterOnes = counterOnes + 1;
        givenArgument >>= 1;
    }

    if( counterOnes % 2 != 0){      
        printf("Odd-Parity\t%d\n", parityPairs);
    }else{
        printf("Even-Parity\t%d\n", parityPairs);
    }

    return 0;
}