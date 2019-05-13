#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void explode(const int code){
    printf("If this had been a real bomb, it would have exploded.\n");
    exit(code);
}

void readInput(char buffer[], const int bufferSize){
    int i;
    int c;
    for(i=0; i<=bufferSize; ++i){
        c = getchar();

        /* this checks that you are at the end of the line */
        /* Windows encodes an end-of-line as two characters: \r\n */
        /* Linux just uses \n */
        /* This will accept either version */
        if(c == '\r'){
            c = getchar();
        }
        
        if(c == '\n'){
            break;
        }
        else if(i<bufferSize){
            buffer[i] = (char)c;
        }
    }
}

void part1(){
    const int bufferSize = 12;
    char buffer[bufferSize];
    
    readInput(buffer, bufferSize);
    
    if(buffer[2] != 'Z' || buffer[5] != '5'){
        explode(10);
    }
}

void part2(){
    const int bufferSize = 10;
    char buffer[bufferSize];
    int z;
  
    readInput(buffer, bufferSize);
  
    /* atoi takes a string representation of a number (e.g. "1234") */
    /* and converts it to an int representation of the numbers (e.g. 1234) */
    z = atoi(buffer);
    if(z % 7 != 4 || z < 15)
        explode(20);
}

void part3(char buffer[], const int bufferSize){
    int j;
  
    readInput(buffer, bufferSize);
  
    j=0;
    while(j<bufferSize){
        if(buffer[j] == '7')
            break;
    
        j++;
    }
  
    if(j > 4)
        explode(30);
}
 
void part4(char buffer[], const int bufferSize){
    char buf2[bufferSize];
    int i;
  
    readInput(buf2, bufferSize);
  
    for(i=0; i<bufferSize && i<8; i++){
        if(buffer[i] == '7') {
            if(buf2[i] != 'w')
  	            explode(40);
        }
        else {
            if(buf2[i] != buffer[i])
    	          explode(42);
        }
    }
}

int main(){
    const int bufSize = 10;
    char buffer[bufSize];
  
    printf("Enter the stage 1 password: ");
    part1();
    printf("Stage 1 defused.\n");
  
    printf("Enter the stage 2 password: ");
    part2();
    printf("Stage 2 defused.\n");
  
    printf("Enter the stage 3 password: ");
    part3(buffer, bufSize);
    printf("Stage 3 defused.\n");
  
    printf("Enter the stage 4 password: ");
    part4(buffer, bufSize);
    printf("Stage 4 defused.\n");
  
    printf("The entire bomb has been defused.\n");
  
    return 0;
}
