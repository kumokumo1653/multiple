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
   //setRandomInt(&e,2);
   //setRandomInt(&d,2);
   //e.sign = 1;
   //d.sign = 1;
   //dispNumberInt(&e);puts("");
   //dispNumberInt(&d);puts("");
   //printf("%d\n",multipleInt(&e, &d, &f, &g));
   //dispNumberInt(&g);
   //dispNumberInt(&f);puts("");
   clearByZeroFloat(&a);
   //clearByZeroFloat(&b);

   setInt(&a.n, 2, 0);
   //setInt(&a.n, 255098128, 1);
   //setInt(&a.n, 28554305, 2);
   //setInt(&a.n, 973245041, 3);
   //setInt(&a.n, 268008940, 4);
   //setInt(&a.n, 12, 5);
   //setInt(&b.n, 338521192, 0);
   //setInt(&b.n, 446242422, 1);
   //setInt(&b.n, 30200784, 2);
   //setInt(&b.n, 0, 3);
   //setInt(&b.n, 0, 4);
   //setInt(&b.n, 1, 5);
   //setRandomFloat(&a, 2, 2);
   //setRandomFloat(&b, 2, 1);
   //setExp(&a, 1);
   //setExp(&b, 0);
   dispNumberFloat(&a);puts("");
   //dispNumberFloat(&b);puts("");
   //setExp(&a, -1);
   //setExp(&b, 0);
   printf("%d\n",numSqrt(&a, &c));
   dispNumberFloat(&c);puts("");

}