#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"number.h"

int main(void){
    struct FLOAT a, b, c;
    struct NUMBER e, d, f;
    srand(time(NULL));
    int i;
    setFloat(&a , 8311, 0);
    setFloat(&b, 23, 0);

    dispNumberFloat(&a);puts("");
    dispNumberFloat(&b);puts("");
    printf("%d\n", subFloat(&a, &b, &c));
    dispNumberFloat(&c);puts("");
}