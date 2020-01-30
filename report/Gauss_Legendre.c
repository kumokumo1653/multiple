#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "number.h"

#define CNT 9

int main(void){
    struct timeval tv;
    double tstart, tend;
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    struct FLOAT a, b, t, p, aAfter, bAfter, tAfter, pAfter, half, two, four, PI, temp1, temp2, temp3;
    int cnt = 0;
    //初期値の設定
    clearByZeroFloat(&half);
    clearByZeroFloat(&two);
    clearByZeroFloat(&four);
    clearByZeroFloat(&a);
    clearByZeroFloat(&temp1);
    clearByZeroFloat(&t);
    clearByZeroFloat(&p);
    setInt(&half.n, 5 * (RADIX  / 10), 0);
    setExp(&half, -1);
    setInt(&two.n, 2,0);
    setInt(&four.n, 4, 0);
    //a
    setInt(&a.n, 1, 0);

    //b
    setInt(&temp1.n, 2, 0);
    numSqrt(&temp1,&temp2);
    reciprocal(&temp2, &b);

    //t
    setInt(&t.n, 250000000, 0);
    setExp(&t, -1);

    //p
    setInt(&p.n, 1, 0);

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
    dispNumberFloat(&PI);
    puts("");
    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("%f秒",tend - tstart);
    return 0;
}

