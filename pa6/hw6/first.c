#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct sturct** givenCache;
typedef struct sturct{

    unsigned long int label;
    int yep;
    unsigned long int duration;
}sturct;

sturct** structCreate(int num, int idx){

    givenCache = (sturct**)malloc(num*sizeof(sturct*));
    int i, j;
    for(i = 0; i < num; i++){
        givenCache[i] = (sturct*)malloc((idx)*sizeof(sturct));
    }
    for(i = 0; i < num; i++){
        for(j = 0; j < idx; j++){
            givenCache[i][j].yep = 0;
        }
    }
    return givenCache;
}

unsigned long int count;
int memoryReads;
int memoryWrites;
int cacheHits;
int cacheMisses;

void helperPreRead(unsigned long int labelIdx, unsigned long int partIdx, int idx){

    int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;

            memoryReads++;
            cacheMisses++;

            givenCache[partIdx][i].label = labelIdx;
            givenCache[partIdx][i].yep = 1;

            return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){
                cacheHits++;

                return;
            }  
            if(i == (idx - 1)){
                memoryReads++;
                cacheMisses++;

                minimum = 0;
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }                
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;

                return;
            }           
        }       
    }
    return;
}

void helperPreWrite(unsigned long int labelIdx, unsigned long int partIdx, int idx){
    
    int i, j, minimum;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;

            memoryReads++;
            memoryWrites++;
            cacheMisses++;

            givenCache[partIdx][i].yep = 1;
            givenCache[partIdx][i].label = labelIdx;

            return;
        }else{ 
            if(givenCache[partIdx][i].label == labelIdx){
                memoryWrites++;
                cacheHits++;

                return;
            }      
            if(i == (idx - 1)){
                memoryReads++;
                memoryWrites++;
                cacheMisses++;

                minimum = 0;
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;

                return;
            }   
        }     
    }
    return;
}

void helperRead(unsigned long int labelIdx,unsigned long int partIdx,int idx){
   
    int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;

            memoryReads++;
            cacheMisses++;
            
            givenCache[partIdx][i].yep = 1;
            givenCache[partIdx][i].label = labelIdx;
            
            return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){
                count++;
                givenCache[partIdx][i].duration = count;

                cacheHits++;
                
                return;
            }	
            if(i == (idx - 1)){
                minimum = 0;

                memoryReads++;
                cacheMisses++;
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;
                
                return;
            }
        }
	}
    return;
}

void helperWrite(unsigned long int labelIdx, unsigned long int partIdx, int idx){
    
    int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
        count++;
        givenCache[partIdx][i].duration = count;
        
        memoryReads++;
        memoryWrites++;
        cacheMisses++;
        
        givenCache[partIdx][i].yep = 1;
        givenCache[partIdx][i].label = labelIdx;
        
        return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){
                count++;
                givenCache[partIdx][i].duration = count;
                
                memoryWrites++;
                cacheHits++;
                
                return;
            }    
            if(i == (idx - 1)){
                minimum = 0;
                
                memoryReads++;
                memoryWrites++;
                cacheMisses++;
                
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;
                
                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;
                
                return;
            }  
        }       
    }
    return;
}

void helperEmpty(int num, int idx){
	
    int i, j;
	for(i = 0; i < num; i++){
		for(j = 0; j < idx; j++){
            givenCache[i][j].duration = 0;
			givenCache[i][j].label = 0;
			givenCache[i][j].yep = 0;
	    }
	}
    count = 0;
    memoryReads = 0;
	memoryWrites = 0;
    cacheHits = 0;
	cacheMisses = 0;
}

void helper1(unsigned long int labelIdx, unsigned long int partIdx, int idx){
	
	int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;

            memoryReads++;

            givenCache[partIdx][i].yep = 1;
            givenCache[partIdx][i].label = labelIdx;

            return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){	
                return;
            }
            if(i == (idx-  1)){	
                minimum = 0;

                memoryReads++;	
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;

                return;
            }
        }
	}
}

void helper2(unsigned long int labelIdx, unsigned long int partIdx, int idx, unsigned long int labelIdxx, unsigned long int partIdxx){
    
    int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;
            
            memoryReads++;
            cacheMisses++;
            
            givenCache[partIdx][i].yep = 1;
            givenCache[partIdx][i].label = labelIdx;
        
            helper1(labelIdxx, partIdxx, idx);

            return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){
                cacheHits++;

                return;
            }	
            if(i == (idx - 1)){
                minimum = 0;
                
                memoryReads++;
                cacheMisses++;
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;
                
                helper1(labelIdxx, partIdxx, idx);

                return;
            }
        }
	}
    return;
}

void helper3(unsigned long int labelIdx, unsigned long int partIdx, int idx){
	
	int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;

            memoryReads++;

            givenCache[partIdx][i].yep = 1;
            givenCache[partIdx][i].label = labelIdx;

            return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){
                return;
            }
            if(i == (idx - 1)){
                minimum = 0;

                memoryReads++;
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;

                return;
            }  
        }       
    }
    return;	
}

void helper4(unsigned long int labelIdx, unsigned long int partIdx, int idx, unsigned long int labelIdxx, unsigned long int partIdxx){
    
    int minimum, i, j;
    for(i = 0; i < idx; i++){
        if(givenCache[partIdx][i].yep == 0){
            count++;
            givenCache[partIdx][i].duration = count;

            memoryReads++;
            memoryWrites++;
            cacheMisses++;

            givenCache[partIdx][i].yep = 1;
            givenCache[partIdx][i].label = labelIdx;

            helper3(labelIdxx, partIdxx, idx);

            return;
        }else{
            if(givenCache[partIdx][i].label == labelIdx){
                memoryWrites++;
                cacheHits++;

                return;
            }	
            if(i == (idx - 1)){
                memoryReads++;
                memoryWrites++;
                cacheMisses++;
                
                minimum = 0;
                for(j = 0; j < idx; j++){
                    if(givenCache[partIdx][j].duration <= givenCache[partIdx][minimum].duration){
                        minimum = j;
                    }	
                }
                count++;
                givenCache[partIdx][minimum].duration = count;

                givenCache[partIdx][minimum].yep = 1;
                givenCache[partIdx][minimum].label = labelIdx;
                
                helper3(labelIdxx, partIdxx, idx);

                return;
            }
        }      
	}
    return;	
} 

int main(int argc, char** argv){
    int x;
    int y;
    int z;
    int idx;
    int num;

    int dimensions = atoi(argv[1]);
    int sizeBlocks = atoi(argv[4]);
    
    unsigned long int currAdr;
    unsigned long int adr;
    unsigned long int idx1;
    unsigned long int labelIdx;
    unsigned long int partIdx;
    unsigned long int labelIdxx;
    unsigned long int partIdxx;

    char c;

    if(argv[3][0] == 'f'){
        FILE* file;
        file = fopen(argv[5], "r");

        if(file == NULL){
            printf("Error\n");
            return 0;
        }
        if(argv[2][0] == 'd'){
            num = dimensions / sizeBlocks;
            idx = 1;
        }else if(argv[2][5]!= ':'){
            idx = dimensions / sizeBlocks;
            num = 1;
        }else{
            sscanf(argv[2], "assoc:%d", &x);
            num = dimensions / sizeBlocks / x;
            idx = x;
        }

        z = log(num) / log(2);
        idx1 = ((1 << z) - 1);
        y = log(sizeBlocks) / log(2);
        givenCache = structCreate(num, idx);

        while(fscanf(file, "%*x: %c %lx", &c, &currAdr) == 2){
            partIdx = (currAdr >> y) &idx1;
            labelIdx = currAdr >> (y + z);
            if(c == 'R'){
                helperPreRead(labelIdx, partIdx, idx);
            }else if(c == 'W'){
                helperPreWrite(labelIdx, partIdx, idx);
            }
        }
        fclose(file);

        file = fopen(argv[5], "r");
        if(file == NULL){
            printf("Error\n");
            return 0;
        }
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memoryReads, memoryWrites, cacheHits, cacheMisses);
        helperEmpty(num, idx);

        while(fscanf(file, "%*x: %c %lx", &c, &currAdr) == 2){
            partIdx = (currAdr >> y) &idx1;
            labelIdx = currAdr >> (y + z);
            adr = currAdr + sizeBlocks;
            partIdxx = (adr >> y) &idx1;
            labelIdxx = adr >> (y + z);

            if(c == 'R'){
                helper2(labelIdx,partIdx,idx,labelIdxx,partIdxx);
            }else if(c=='W'){
                helper4(labelIdx,partIdx,idx,labelIdxx,partIdxx);
            }
        }
    }else if(argv[3][0] == 'l'){
        FILE* file;
        file = fopen(argv[5], "r");

        if(file == NULL){
            printf("Error\n");
            return 0;
        }
        if(argv[2][0] == 'd'){
            num = dimensions / sizeBlocks;
            idx = 1;
        }else if(argv[2][5] != ':'){
            idx = dimensions / sizeBlocks;
            num = 1;
        }else{
            sscanf(argv[2],"assoc:%d",&x);
            num = dimensions / sizeBlocks / x;
            idx = x;
        }
        z = log(num) / log(2);
        idx1 = ((1 << z) - 1);
        y = log(sizeBlocks) / log(2);
        givenCache = structCreate(num, idx);

        while(fscanf(file, "%*x: %c %lx", &c, &currAdr) == 2){
            partIdx = (currAdr >> y) &idx1;
            labelIdx = currAdr >> (y + z);
            if(c == 'R'){ 
                helperRead(labelIdx, partIdx, idx);
            }else if(c == 'W'){
                helperWrite(labelIdx, partIdx, idx);
            }
        }
        fclose(file);

        file = fopen(argv[5], "r");
        if(file == NULL){
            printf("Error\n");
            return 0;
        }
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memoryReads, memoryWrites, cacheHits, cacheMisses);
	}else{
		printf("Error");
	}
    return 0;
}