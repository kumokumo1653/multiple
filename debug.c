#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"number.h"

int main(void){
    struct FLOAT a, b, c;
    struct NUMBER e, d, f, g;
    srand(time(NULL));
    int i;
    //for(i = 0; i < 10; i++){
        setFloat(&a , rand() % 10000, rand() % 3 *(rand() % 2 ? -1 : 1));
        setFloat(&b, -rand() % 10000, rand() % 3 * (rand() % 2 ? -1 : 1));
        //setFloat(&a, 7537, 2);
        //setFloat(&b, 6091, -1);
        dispNumberFloat(&a);puts("");
        dispNumberFloat(&b);puts("");
        printf("%d\n", multipleFloat(&a, &b, &c));
        dispNumberFloat(&c);puts("");
        puts("");

    //}
}