#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "number.h"

int main(void){
    struct FLOAT a, b, c;
    struct NUMBER e, d, f, g;
    srand(time(NULL));
    int i,j;
    for(i = 0; i < 10; i++){
        setFloat(&a , -rand() % 1000, rand() % 3 * (rand() % 2 ? 1 : -1) );
        setFloat(&b, -rand() % 1000, rand() % 3 * (rand() % 2 ? 1 : -1));
        //setFloat(&a, -1, 2);
        //setFloat(&b, -2, 0);
        dispNumberFloat(&a);puts("");
        dispNumberFloat(&b);puts("");
        printf("%d\n", divideFloat(&a, &b, &c));
        dispNumberFloat(&c);puts("");
        puts("");

    }
}