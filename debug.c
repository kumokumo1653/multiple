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
    //for(i = 0; i < 10; i++){
        //setFloat(&a , rand() % 100000 * (rand() % 2 ? -1 : 1), rand() % 3 * (rand() % 2 ? 1 : -1) );
        //setFloat(&b, rand() % 100000, rand() % 3 * (rand() % 2 ? 1 : -1));
        setInt(&e, 25065);
        //setInt(&d, 23405);
        //dispNumberFloat(&a);puts("");
        //dispNumberFloat(&b);puts("");
        printf("%d\n", divByNInt(&e, &d, 3, &f));
        dispNumberInt(&d);puts("");
        dispNumberInt(&f);puts("");
        puts("");

    //}
}