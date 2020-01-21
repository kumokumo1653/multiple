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
        setInt(&e , -rand() % 100 );
        setInt(&d, rand() % 100);
        //setFloat(&a, 3, -1);
        //setFloat(&b, -2, 0);
        dispNumberInt(&e);puts("");
        dispNumberInt(&d);puts("");
        printf("%d\n", multipleInt(&e, &d, &f,&g));
        dispNumberInt(&f);puts("");
        dispNumberInt(&g);puts("");
        puts("");

    //}
}