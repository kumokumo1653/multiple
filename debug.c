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
<<<<<<< HEAD
        //setFloat(&a , rand() % 100000 * (rand() % 2 ? -1 : 1), rand() % 3 * (rand() % 2 ? 1 : -1) );
        //setFloat(&b, -rand() % 100000, rand() % 3 * (rand() % 2 ? 1 : -1));
        setFloat(&a, 3, 0);
        //setFloat(&b, -2, 0);
        dispNumberFloat(&a);puts("");
        //dispNumberFloat(&b);puts("");
        printf("%d\n", numSqrt2(&a, &c));
        dispNumberFloat(&c);puts("");
=======
        setInt(&e , -rand() % 100 );
        setInt(&d, rand() % 100);
        //setFloat(&a, 3, -1);
        //setFloat(&b, -2, 0);
        dispNumberInt(&e);puts("");
        dispNumberInt(&d);puts("");
        printf("%d\n", multipleInt(&e, &d, &f,&g));
        dispNumberInt(&f);puts("");
        dispNumberInt(&g);puts("");
>>>>>>> 1dab98f6fa29caeaca6be35dd45d934575d27b91
        puts("");

    //}
}