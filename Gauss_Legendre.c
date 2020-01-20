#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "number.h"

#define CNT 9
int main(void){
    time_t t1 = time(NULL);
    struct FLOAT a, b, t, p, aAfter, bAfter, tAfter, pAfter, half, two, four, PI, temp1, temp2, temp3;
    int cnt = 0;
    //初期値の設定
    setFloat(&half, 5, -1);
    setFloat(&two, 2, 0);
    setFloat(&four, 4, 0);
    //a
    setFloat(&a, 1, 0);

    //b
    setFloat(&temp1, 2, 0);
    numSqrt(&temp1,&temp2);
    reciprocal(&temp2, &b);

    //t
    setFloat(&t, 25, -1);

    //p
    setFloat(&p, 1, 0);

    while(1){
        
        //a
        if(!addFloat(&a, &b, &temp1))
            return -1;
        if(!multipleFloat(&temp1, &half, &aAfter))
            return -1;
        
        //b
        if(!multipleFloat(&a, &b, &temp1))
            return -1;
        if(!numSqrt(&temp1, &bAfter))
            return -1;
        
        //t
        if(!subFloat(&a, &aAfter, &temp1))
            return -1;
        if(!power(&temp1, 2, &temp2))
            return -1;
        if(!multipleFloat(&temp2, &p, &temp3))
            return -1;
        if(!subFloat(&t, &temp3, &tAfter))
            return -1;
        
        //p
        if(!multipleFloat(&p, &two, &pAfter))
            return -1;
        
        cnt++;
        if(cnt >= CNT)
            break;
        //更新
        copyNumberFloat(&aAfter, &a);
        copyNumberFloat(&bAfter, &b);
        copyNumberFloat(&tAfter, &t);
        copyNumberFloat(&pAfter, &p);
    }

    //pi
    if(!addFloat(&aAfter, &bAfter, &temp1))
        return -1;
    if(!power(&temp1, 2, &temp2))
        return -1;
    if(!multipleFloat(&tAfter, &four, &temp3))
        return -1;
    if(!divideFloat(&temp2, &temp3, &PI))
        return -1;
    dispNumberFloatforCopy(&PI);
    puts("");
    time_t t2 = time(NULL);
    printf("%ld秒",t2-t1);
    return 0;
}