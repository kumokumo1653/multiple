#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"number.h"

int main(void){
    srand(time(NULL));
    //struct NUMBER base,ans;
    //int baseInt,exponent;
    //baseInt = rand() % 50;
    //exponent = rand() % 50;
    //setInt(&base, baseInt);
    //int a = power(&base, exponent, &ans);
    //printf("%d,%d\n",baseInt, exponent);
    //dispNumber(&ans);puts("");
    //printf("\n%d\n",a);

    struct NUMBER a, b;
    int random = (rand() % 100) * 1000000;
    printf("%d\n", random);
    setInt(&a, random);
    numSqrt(&a, &b);
    dispNumber(&a);puts("");
    dispNumber(&b);puts("");
    printf("%f\n",sqrt(random));

}