#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"number.h"

int main(void){
    struct FLOAT a, b;
    setFloat(&a, 1679000,1);
    setFloat(&b, 15000000,1);
    printf("%d\n", numCompFfloat(&a, &b));
    dispNumberFloat(&a);puts("");
    dispNumberFloat(&b);puts("");
}