#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define DIGIT 3000000000

int main(void){
   srand(time(NULL));
   long int a = rand() ;
   printf("%lld\n", LLONG_MAX);
   printf("%d\n", INT_MAX);
   return 0;
}
