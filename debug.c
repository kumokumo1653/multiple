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
   setRandomInt(&e,2);
   setRandomInt(&d,2);
   e.sign = 1;
   d.sign = 1;
   dispNumberInt(&e);puts("");
   dispNumberInt(&d);puts("");
   printf("%d\n",multipleInt(&e, &d, &f, &g));
   dispNumberInt(&g);
   dispNumberInt(&f);puts("");
   //setRandomFloat(&a, 2, 2);
   //setRandomFloat(&b, 2, 2);
   //dispNumberFloat(&a);puts("");
   //dispNumberFloat(&b);puts("");
   //printf("%d\n",subFloat(&a, &b, &c));
   //dispNumberFloat(&c);puts("");

}