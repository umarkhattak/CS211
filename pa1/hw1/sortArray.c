#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

   FILE* pointerFile=fopen(argv[1],"r");

   if(pointerFile == NULL){
      return 1;
   }

   int numberforSize;
   fscanf(pointerFile,"%d",&numberforSize);
   int array[numberforSize];
   int x;
   int even;
   int odd;
   int k;

   if(numberforSize == 0){
      return 1;
   }

   for(x = 0; x < numberforSize; x++){
      fscanf(pointerFile,"%d", &array[x]);
   }

   for(even = 1; even < numberforSize; even++){
      for (odd = even - 1; odd >= 0; odd--){
         if(abs(array[even] % 2) == 0 && abs(array[odd] % 2) == 1){ 
            k = array[even];
            array[even] = array[odd];
            array[odd ] = k;
            even--;
         }
         else if(abs(array[even] % 2) == 1 && abs(array[odd] % 2) == 1){
            if(array[even] > array[odd]){
               k = array[even];
               array[even] = array[odd];
               array[odd] = k;
               even--;
            }
            else continue;
         }
         else if(abs(array[even] % 2) == 0 && abs(array[odd] % 2) == 0){ 
            if(array[even] < array[odd]){
               k = array[even];
               array[even] = array[odd];
               array[odd] = k;
               even--;
            }
            else continue;
         }
         else if(abs(array[even] % 2) == 1 && abs(array[odd] % 2) == 0){ 
            continue;
         }
      }
   }

   for(x = 0; x < numberforSize; x++){
      printf("%d\t",array[x]);
   }

   fclose(pointerFile);
   return 0;
}