#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "number.h"

int main(void){
    struct FLOAT a, b, c;
    struct NUMBER e, d, f, g;
    setInt(&e,499786);
    setInt(&d,98);
    divideInt(&e,&d,&f,&g);
    dispNumberZeroSuppressInt(&f);
    dispNumberZeroSuppressInt(&g);

}