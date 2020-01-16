#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<malloc.h>
#include"number.h"
void clearByZero(struct NUMBER *num){
    int i;
    for(i = 0; i < DIGIT; i++)
        num->n[i] = 0;

    setSign(num,1);
}
void dispNumber(struct NUMBER *num){
    int i;
    if(getSign(num) > 0)
        printf("+");
    else
        printf("-");
    for(i = DIGIT - 1;i >= 0;i--)
        printf("%2d",num->n[i]);
}
void dispNumberZeroSuppress(struct NUMBER *num){
    int i;
    if(getSign(num) > 0)
        printf("+");
    else
        printf("-");
    for(i = DIGIT - 1; i >= 0;i--){
        if(num->n[i] != 0)
            break;
    }
    if(i == 0){
        printf(" 0");
        return;
    }
    for(; i >= 0;i--){
        printf("%2d",num->n[i]);
    }
}
void setRandom(struct NUMBER *num,int digit){
    int i;
    clearByZero(num);
    if(digit > DIGIT){
        printf("Argument is abnormal");
        return;
    }
    for(i = 0;i < digit;i++){
        num->n[i] = rand() % 10;
    }
    int Sign = rand() % 2;
    switch (Sign)
    {
    case 1:
        setSign(num,1);
        break;
    case 0:
        setSign(num,-1);
        break;

    }
}
void copyNumber(struct NUMBER *source, struct NUMBER *to){
    int i;
    clearByZero(to);
    for (i = 0; i < DIGIT;i++){
        to->n[i] = source->n[i];
    }
    setSign(to,getSign(source));
}
void getAbs(struct NUMBER *source,struct NUMBER *to){
    copyNumber(source,to);
    setSign(to,1);
}
//返り値
//1... num == 0
//0... num != 0
//各桁が0であるのに符号変数が負のとき0ではないと返す
int isZero(struct NUMBER *num){
    int i;
    int flag = 1;
    if(getSign(num) == 1){
        for(i = 0;i < DIGIT;i++){
            if(num->n[i] != 0){
                flag = 0;
                break;
            }
        }
        if(flag)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
//返り値
//1...正常終了
//0...オーバーフロー
int mulBy10(struct NUMBER *source,struct NUMBER *to){
    int i;
    clearByZero(to);
    if(source->n[DIGIT - 1] != 0){
        clearByZero(to);
        return 0;
    }
    for(i = 0;i < DIGIT - 1;i++){
        to->n[i + 1] = source->n[i];
    }
    to->n[0] = 0;
    setSign(to,getSign(source));
    return 1;
}
//返り値
//割り算の剰余
int divBy10(struct NUMBER *source,struct NUMBER *to){
    int i,temp;
    clearByZero(to);
    temp = source->n[0];
    for(i = 0;i < DIGIT - 1; i++){
        to->n[i] = source->n[i + 1];
    }
    to->n[DIGIT - 1] = 0;
    setSign(to,getSign(source));
    return getSign(source) * temp;
}
//返り値
//1...正常終了
//0...設定できなかった
int setInt(struct NUMBER *num,int set){
    clearByZero(num);
    int digit = 0;
    if(set == 0)
        return 1;
    //符号をセット
    if(set > 0)
        setSign(num,1);
    else
        setSign(num,-1);
    
    while(set != 0){
        if(digit > DIGIT){
            printf("error:Few digits\n");
            clearByZero(num);
            return 0;
        }
        int surplus = abs(set % 10);
        num->n[digit] = surplus;
        digit++;
        set /= 10;
    }
    return 1;
}
//1...正常終了
//0...エラー
int getInt(struct NUMBER *num,int *set){
    int i;
    *set = 0;
    int digit = getDigit(num);
    if(digit > 32){
        printf("error:big digit\n");
        return 0;
    }
    else if (digit == 0)
        return 1;
    for(i = digit - 1; i >= 0;i--){
        *set += num->n[i];
        *set *= 10;
    }
    *set /= 10;
    //符号
    *set *= getSign(num);
    return 1;
}

void swap(struct NUMBER *a,struct NUMBER *b){
    struct NUMBER temp;
    copyNumber(a,&temp);
    copyNumber(b,a);
    copyNumber(&temp,b);
}
//返り値 桁数
int getDigit(struct NUMBER *num){
    int i;
    for(i = DIGIT - 1; i >= 0;i--){
        if(num->n[i] != 0)
            return i + 1;
    }
    return 0;
}

//1...正常終了0...エラー
int getIntToString(struct NUMBER *num,char *set){
    int i;
    int digit = getDigit(num);
    set = (char *)malloc(sizeof(char) * (digit + 1));
    for(i = 0; i < digit; i++){
        set[digit - 1 - i] = num->n[i] + '0';
        
    }
    set[digit] = '\0';
    printf("%s\n",set);
    return 1;
}

//1...正に-1...負に
int setSign(struct NUMBER *num,int s){
    if(s == 1)
        num->sign = 1;
    else if(s == -1)
        num->sign = -1;
}
//正なら1負なら-1を返す。
int getSign(struct NUMBER *num){
    if(num->sign == 1)
        return 1;
    else if(num->sign == -1)
        return -1;
}
//1...a>b
//0...a=b
//-1...a<b
int numComp(struct NUMBER *a,struct NUMBER *b){
    int aSign = getSign(a);
    int bSign = getSign(b);
    int i;
    //aとbの符号が違うとき
    if((aSign == -1) && (bSign == 1))
        return -1;
    if((aSign == 1) && (bSign == -1))
        return 1;
    //ともに正のとき
    if((aSign == 1) && (bSign == 1)){
        for(i = DIGIT - 1;i >= 0; i--){
            if(a->n[i] > b->n[i])
                return 1;
            else if(a->n[i] < b->n[i])
                return -1;
        }
        return 0;
    }
    //ともに負のとき
    if((aSign == -1) && (bSign == -1)){
        for(i = DIGIT -1; i >= 0; i--){
            if(a->n[i] > b->n[i])
                return -1;
            else if(a->n[i] < b->n[i])
                return 1;
        }
        return 0;
    }
    return 1;
}
int add(struct  NUMBER *augend, struct NUMBER *addend, struct NUMBER *ans){
    int carry = 0;
    int i;
    int augendSign = getSign(augend);
    int addendSign = getSign(addend);
    //ともに正
    if((augendSign == 1) && (addendSign == 1)){
        clearByZero(ans);
        for(i = 0; i < DIGIT;i++){
            int sum = augend->n[i] + addend->n[i] + carry;
            ans->n[i] = sum % 10;
            carry = sum / 10;
        }
        if(carry > 0){
            printf("overflow\n");
            clearByZero(ans);
            return 0;
        }
        return 1;
    }
    //augendが負addendが正
    else if((augendSign == -1) && (addendSign == 1)){
        struct NUMBER temp;
        getAbs(augend,&temp);
        if(!sub(addend,&temp,ans)){
            clearByZero(ans);
            return 0;
        }
    }
    //augendが正addendが負
    else if((augendSign == 1) && (addendSign == -1)){
        struct NUMBER temp;
        getAbs(addend,&temp);
        if(!sub(augend, &temp, ans)){
            clearByZero(ans);
            return 0;
        }
    }
    //ともに負
    else {
        struct NUMBER augendTemp,addendTemp;
        getAbs(augend,&augendTemp);
        getAbs(addend,&addendTemp);
        if(!add(&augendTemp, &addendTemp,ans)){
            clearByZero(ans);
            return 0;
        }
        setSign(ans, -1);
    }
    return 0;
}

//ans = minuend - subtrahend
//0...エラー
//1...正常終了
int sub(struct NUMBER *minuend,struct NUMBER *subtrahend, struct NUMBER *ans){
    int i;
    int borrrow = 0;
    int minuendSign = getSign(minuend);
    int subtrahendSign = getSign(subtrahend);
    //ともに正のとき
    if((minuendSign == 1) && (subtrahendSign == 1)){
        //a<bのとき入れ替える
        if(numComp(minuend,subtrahend) == -1){
            swap(minuend,subtrahend);
            if(!sub(minuend,subtrahend,ans)){
                clearByZero(ans);
                return 0;
            }
            swap(minuend,subtrahend);
            setSign(ans,-1);
        }else{
            clearByZero(ans);
            for(i = 0;i < DIGIT; i++){
                //繰り下がり考慮
                int minuendDigit = minuend->n[i] - borrrow;
                int subtrahendDigit = subtrahend->n[i];
                if(minuendDigit >= subtrahendDigit){
                    ans->n[i] = minuendDigit - subtrahendDigit;
                    borrrow = 0;
                }else{
                    ans->n[i] = 10 + minuendDigit - subtrahendDigit;
                    borrrow = 1;
                }
            }
            if(borrrow != 0){
                printf("over flow\n");
                return 0;
            }
            return 1;
        }
    }
    //minuendが正でsubtrahedが負のとき
    else if((minuendSign == 1) && (subtrahendSign == -1)){
        struct NUMBER temp;
        getAbs(subtrahend,&temp);
        if(!add(minuend,&temp,ans)){
            clearByZero(ans);
            return 0;
        }
    }
    //minuendが負でsubtrahendが正のとき
    else if((minuendSign == -1) && (subtrahendSign == 1)){
        struct NUMBER temp;
        getAbs(minuend,&temp);
        if(!add(&temp,subtrahend,ans)){
            clearByZero(ans);
            return 0;
        }
        setSign(ans,-1);
    }
    //ともに負
    else{
        struct NUMBER minuendTemp,subtrahendTemp;
        getAbs(minuend,&minuendTemp);
        getAbs(subtrahend,&subtrahendTemp);
        if(!sub(&subtrahendTemp, &minuendTemp, ans)){
            clearByZero(ans);
            return 0;
        }
    }
}
//1足す
//返り値
//0…オーバーフロー
//1…正常終了
int increment(struct NUMBER *source, struct NUMBER *to){
    struct NUMBER one;
    setInt(&one,1);
    return add(source,&one,to);
}
//返り値
//1...正常終了
//0...オーバーフロー
int multiple(struct NUMBER *multiplicand, struct NUMBER *multiplier, struct NUMBER *ans){
    struct NUMBER temp, productTemp;
    int carry = 0;//繰り上がり
    clearByZero(ans);
    int i, j;
    int multiplicandDigit = getSign(multiplicand);
    int multiplierDigit = getSign(multiplier);
    //ともに正
    if(multiplicandDigit == 1 && multiplierDigit == 1){
        for (i = 0; i < DIGIT; i++){
            clearByZero(&temp);
            for (j = 0; j < DIGIT; j++){
                int product = multiplicand->n[j] * multiplier->n[i] + carry;
                if ((j + i) < DIGIT){
                    temp.n[j + i] = product % 10;
                }else if((product % 10) != 0){ 
                    clearByZero(ans);
                    return 0;
                }
                carry = product / 10;
            }
            if(carry != 0){
                clearByZero(ans);
                return 0;
            }
            //ansにtempを加える
            if(!add(ans, &temp, &productTemp)){
                clearByZero(ans);
                return 0;
            }
            copyNumber(&productTemp, ans);
        }
        return 1;
    }//負×正
    else if(multiplicandDigit == -1 && multiplierDigit == 1){
        struct NUMBER temp;
        getAbs(multiplicand,&temp);
        if(!multiple(&temp,multiplier,ans)){
            clearByZero(ans);
            return 0;
        }
        setSign(ans,-1);
        return 1;
    }else if(multiplicandDigit == 1 && multiplierDigit == -1){
        struct NUMBER temp;
        getAbs(multiplier,&temp);
        if(!multiple(multiplicand,&temp,ans)){
            clearByZero(ans);
            return 0;
        }
        setSign(ans,-1);
        return 1;
    }else if(multiplicandDigit == -1 && multiplierDigit == -1){
        struct NUMBER temp1,temp2;
        getAbs(multiplicand,&temp1);
        getAbs(multiplier,&temp2);
        if(!multiple(&temp1,&temp2,ans)){
            clearByZero(ans);
            return 0;
        }
        return 1;
    }
    return 0;
}

//返り値
//0 エラー 0除算
//1 正常終了

int divide(struct NUMBER *dividend, struct NUMBER *divisor,struct NUMBER *quotient, struct NUMBER *remainder){
    clearByZero(quotient);
    clearByZero(remainder);
    //ゼロ除算検知
    if(isZero(divisor))
        return 0;
    int dividendSign = getSign(dividend);
    int divisorSign = getSign(divisor);
    if(dividendSign == 1 && divisorSign == 1){
        struct NUMBER tempDividend,temp;
        copyNumber(dividend, &tempDividend);
        while(1){
            if(numComp(&tempDividend, divisor) >=0){
                copyNumber(divisor,remainder);
                setInt(&temp,1);
                struct NUMBER tempRemainder,tempTemp;
                while(1){
                    if(numComp(&tempDividend,remainder) >= 0){
                        //remainderを10倍
                        mulBy10(remainder,&tempRemainder);
                        copyNumber(&tempRemainder,remainder);
                        //tempも10倍
                        mulBy10(&temp,&tempTemp);
                        copyNumber(&tempTemp,&temp);
                    }else{
                        divBy10(remainder,&tempRemainder);
                        copyNumber(&tempRemainder,remainder);
                        divBy10(&temp,&tempTemp);
                        copyNumber(&tempTemp,&temp);
                        break;
                    }
                }
                
                struct NUMBER ansTemp;
                sub(&tempDividend,remainder,&ansTemp);
                copyNumber(&ansTemp,&tempDividend);
                add(quotient,&temp,&ansTemp);
                copyNumber(&ansTemp,quotient);
            }else if (numComp(&tempDividend,divisor) < 0){
                copyNumber(&tempDividend,remainder);
                break;
            }
        }
        return 1;
    }else if (dividendSign == 1 && divisorSign == -1){
        struct NUMBER temp;
        getAbs(divisor,&temp);
        divide(dividend,&temp,quotient,remainder);
        setSign(quotient,-1);
        return 1;
    }else if (dividendSign == -1 && divisorSign == 1){
        struct NUMBER temp;
        getAbs(dividend,&temp);
        divide(&temp,divisor,quotient,remainder);
        setSign(quotient, -1);
        setSign(remainder, -1);
        return 1;
    }else if (dividendSign == -1 && divisorSign == -1){
        struct NUMBER  temp1, temp2;
        getAbs(dividend, &temp1);
        getAbs(divisor, &temp2);
        divide(&temp1, &temp2 , quotient, remainder);
        setSign(remainder, -1);
        return 1;
    }
    return 0;
}
//除数1桁のときの高速化
//0 エラーゼロ除算
//1 正常終了
int divInt(struct NUMBER *dividend, int divisor,struct NUMBER *quotient, int *remainder){
    int remain = 0;
    int i;
    clearByZero(quotient);
    *remainder = 0;
    //ゼロ除算検知
    if(divisor == 0)
        return 0;
    int dividendSign = getSign(dividend);
    //ともに正
    if(dividendSign == 1 && divisor >= 0){
        for(i = DIGIT - 1;i >= 0; i--){
            int digittemp = dividend->n[i];
            int temp = digittemp + 10 * remain;
            remain = temp % divisor;
            quotient->n[i] = (temp - remain) / divisor;
        }
        *remainder = remain;
        return 1;
    }else if(dividendSign == 1 && divisor < 0){
        divInt(dividend,divisor * -1,quotient,remainder);
        setSign(quotient,-1);
        return 1;
    }else if(dividendSign == -1 && divisor >= 0){
        struct NUMBER temp;
        getAbs(dividend,&temp);
        divInt(&temp,divisor,quotient,remainder);
        setSign(quotient, -1);
        *remainder *= -1;
        return 1;
    }else if(dividendSign == -1 && divisor < 0){
        struct NUMBER temp;
        getAbs(dividend,&temp);
        divInt(&temp,divisor * -1, quotient,remainder);
        *remainder *= -1;
        return 1;
    }
}
//正の平方根を求める。
//戻り値
//0...エラー
//1...正常終了
int numSqrt(struct NUMBER *source,struct NUMBER *sqroot){
    clearByZero(sqroot);
    //初期値をとりあえずソースに
    struct NUMBER x, xOneBefore, xTwoBefore;
    copyNumber(source,&x);
    copyNumber(source,&xOneBefore);
    copyNumber(source,&xTwoBefore);
    if(getSign(source) == -1)
        return 0;
    if(getDigit(source) <= 1 && (source->n[0] <= 1)){
        copyNumber(source, sqroot);
        return 1;
    }
    //振動,収束するまで繰り返す
    while(1){
        //前のxを更新
        copyNumber(&xOneBefore,&xTwoBefore);
        copyNumber(&x, &xOneBefore);

        //xを更新
        struct NUMBER divTemp,temp,addtemp;
        int remain;
        if(!(divide(source, &xOneBefore, &divTemp, &temp)))
            return 0;
        if(!(add(&divTemp, &xOneBefore,&addtemp)))
            return 0;
        if(!(divInt(&addtemp, 2,&x,&remain)))
            return 0;
        //収束
        if(numComp(&x, &xOneBefore) == 0)
            break;
        //振動
        if(numComp(&x, &xTwoBefore) == 0){
            //小さい方を採用
            if(numComp(&x, &xTwoBefore) == 1)
                copyNumber(&xOneBefore, &x);
            break;
        }
    }
    copyNumber(&x, sqroot);
    return 1;

}
//baseのexponent乗を返す。(exponent>=0)ゼロのゼロ乗は1とする
//オーバーフローしたら0を入れる。
//0…エラー、オーバーフロー
//1…正常終了
int power(struct NUMBER *base, int exponent,struct NUMBER *ans){
    if(exponent < 0)
        return 0;
    else if(exponent == 0){
        setInt(ans,1);
        return 1;
    }else if(exponent == 1){
        copyNumber(base,ans);
        return 1;
    }else if(exponent % 2 == 0){
        struct NUMBER square;
        if(!(multiple(base, base, &square))){
            clearByZero(ans);
            return 0;
        }
        if(!(power(&square, exponent / 2,ans))){
            clearByZero(ans);
            return 0;
        }
    }else{
        struct NUMBER powerTemp;
        if(!(power(base, exponent - 1, &powerTemp))){
            clearByZero(ans);
            return 0;
        }
        if(!(multiple(base, &powerTemp, ans))){
            clearByZero(ans);
            return 0;
        }
    }
    return 1;
}
