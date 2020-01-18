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
    //for(i = 0;i < 10;i++){
        int x, y, z, w;
        x = rand() % 1000;
        y = rand() % 1000;
        z = rand() % 3 *(rand() % 2 ? 1 : -1);
        w = rand() % 3 *(rand() % 2 ? 1 : -1);
        setFloat(&a, -9993, 2);
        setFloat(&b, -9934, 2);
        printf("%d,%d\n", x, z);
        printf("%d,%d\n", y, w);
        dispNumberFloat(&a);puts("");
        dispNumberFloat(&b);puts("");
        subFloat(&a, &b, &c);
        dispNumberFloat(&c);puts("");
    //}
}