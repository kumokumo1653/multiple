#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define DIGIT 3

int main(void){
   srand(time(NULL));
   long int a = rand() ;
   printf("%0DIGId\n", 45);
   //printf("%d\n", INT_MAX);
   return 0;
}
