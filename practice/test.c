#include <stdio.h>

int f(int i){
    return i * i + 1;
}

int main(){

    int i;
    int res;

    for(i=0; i<10; i++){
        res = f(i);
        printf("%d, %d\n", i, res);
    }

    return 0;
}
