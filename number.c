#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include "number.h"
void clearByZeroInt(struct NUMBER *num){
    int i;
    for(i = 0; i < DIGIT; i++)
        num->n[i] = 0;

    setSignInt(num,1);
}
void clearByZeroFloat(struct FLOAT *num){
    clearByZeroInt(&(num->n));
    num->exp = 0;
}

void dispNumberInt(struct NUMBER *num){
    int i;
    if(getSignInt(num) > 0)
        printf("+");
    else
        printf("-");
    for(i = DIGIT - 1;i >= 0;i--)
        printf("%2d",num->n[i]);
}
void dispNumberFloat(struct FLOAT *num){
    int i;
    int exp = num->exp;
    if(getSignInt(&(num->n)) > 0)
        printf("+");
    else
        printf("-");
    if(exp >= 0){

        for(i = getDigitInt(&(num->n)) - 1; i >= 0; i--){
            printf("%2d",num->n.n[i]);
            if(exp == 0)
                printf(" .");
            exp--;
        }
        if( exp > 0 ){
            printf(" 0");
            while(exp != 0){
                printf(" 0");
                exp--;
            }
            printf(" .");
        }
    }else{
        printf(" 0");
        exp++;
        printf(" ."); 
        while(exp != 0){
            printf(" 0");
            exp++;
        }
        for(i = getDigitInt(&(num->n))- 1; i >= 0; i--)
            printf("%2d",num->n.n[i]);

    }
    
    
}

void dispNumberZeroSuppressInt(struct NUMBER *num){
    int i;
    if(getSignInt(num) > 0)
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
void setRandomInt(struct NUMBER *num,int digit){
    int i;
    clearByZeroInt(num);
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
        setSignInt(num,1);
        break;
    case 0:
        setSignInt(num,-1);
        break;

    }
}
void copyNumberInt(struct NUMBER *source, struct NUMBER *to){
    int i;
    clearByZeroInt(to);
    for (i = 0; i < DIGIT;i++){
        to->n[i] = source->n[i];
    }
    setSignInt(to,getSignInt(source));
}
void copyNumberFloat(struct FLOAT *source, struct FLOAT *to){
    clearByZeroFloat(to);
    copyNumberInt(&source->n, &to->n);
    to->exp = source->exp;
}

void getAbsInt(struct NUMBER *source,struct NUMBER *to){
    copyNumberInt(source,to);
    setSignInt(to,1);
}

void getAbsFloat(struct FLOAT *source,struct FLOAT *to){
    clearByZeroFloat(to);
    getAbsInt(&source->n, &to->n);
    to->exp = source->exp;

}

//返り値
//1... num == 0
//0... num != 0
//各桁が0であるのに符号変数が負のとき0ではないと返す
int isZeroInt(struct NUMBER *num){
    int i;
    int flag = 1;
    if(getSignInt(num) == 1){
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
//1... num == 0
//0... num != 0
//各桁が0であるのに指数部が0でないのとき0ではないと返す
int isZeroFloat(struct FLOAT *num){
    if(isZeroInt(&num->n)){
        if(num->exp == 0)
            return 1;
        else
            return 0;
    }else
        return 0;
}

//返り値
//1...正常終了
//0...オーバーフロー
int mulBy10Int(struct NUMBER *source,struct NUMBER *to){
    int i;
    clearByZeroInt(to);
    if(source->n[DIGIT - 1] != 0){
        clearByZeroInt(to);
        return 0;
    }
    for(i = 0;i < DIGIT - 1;i++){
        to->n[i + 1] = source->n[i];
    }
    to->n[0] = 0;
    setSignInt(to,getSignInt(source));
    return 1;
}
//返り値
//割り算の剰余
int divBy10Int(struct NUMBER *source,struct NUMBER *to){
    int i,temp;
    clearByZeroInt(to);
    temp = source->n[0];
    for(i = 0;i < DIGIT - 1; i++){
        to->n[i] = source->n[i + 1];
    }
    to->n[DIGIT - 1] = 0;
    setSignInt(to,getSignInt(source));
    return getSignInt(source) * temp;
}
//返り値
//1...正常終了
//0...設定できなかった
int setInt(struct NUMBER *num,int set){
    clearByZeroInt(num);
    int digit = 0;
    if(set == 0)
        return 1;
    //符号をセット
    if(set > 0)
        setSignInt(num,1);
    else
        setSignInt(num,-1);
    
    while(set != 0){
        if(digit > DIGIT){
            printf("error:Few digits\n");
            clearByZeroInt(num);
            return 0;
        }
        int surplus = abs(set % 10);
        num->n[digit] = surplus;
        digit++;
        set /= 10;
    }
    return 1;
}
int setFloat(struct FLOAT *num, int n, int e){
    clearByZeroFloat(num);
    setInt(&(num->n), n);
    num->exp = e;
}


//1...正常終了
//0...エラー
int getInt(struct NUMBER *num,int *set){
    int i;
    *set = 0;
    int digit = getDigitInt(num);
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
    *set *= getSignInt(num);
    return 1;
}

void swapInt(struct NUMBER *a,struct NUMBER *b){
    struct NUMBER temp;
    copyNumberInt(a,&temp);
    copyNumberInt(b,a);
    copyNumberInt(&temp,b);
}
//返り値 桁数
int getDigitInt(struct NUMBER *num){
    int i;
    for(i = DIGIT - 1; i >= 0;i--){
        if(num->n[i] != 0)
            return i + 1;
    }
    if(isZeroInt(num))
        return 1;
    return 0;
}

//1...正常終了0...エラー
int getIntToString(struct NUMBER *num,char *set){
    int i;
    int digit = getDigitInt(num);
    set = (char *)malloc(sizeof(char) * (digit + 1));
    for(i = 0; i < digit; i++){
        set[digit - 1 - i] = num->n[i] + '0';
        
    }
    set[digit] = '\0';
    printf("%s\n",set);
    return 1;
}

//1...正に-1...負に
int setSignInt(struct NUMBER *num,int s){
    if(s == 1)
        num->sign = 1;
    else if(s == -1)
        num->sign = -1;
}
//正なら1負なら-1を返す。
int getSignInt(struct NUMBER *num){
    if(num->sign == 1)
        return 1;
    else if(num->sign == -1)
        return -1;
}
//1...a>b
//0...a=b
//-1...a<b
int numCompInt(struct NUMBER *a,struct NUMBER *b){
    int aSign = getSignInt(a);
    int bSign = getSignInt(b);
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
//1...a>b
//0...a=b
//-1...a<b

int numCompFfloat(struct FLOAT *a,struct FLOAT *b){
    int Aexp = a->exp;
    int Bexp = b->exp;
    int Adigit = getDigitInt(&a->n);
    int Bdigit = getDigitInt(&b->n);
    int i;
    struct NUMBER temp1,temp2;
    if(Aexp > Bexp)
        return 1;
    else if(Aexp < Bexp)
        return -1;
    else{
        if(Adigit > Bdigit){
            copyNumberInt(&b->n, &temp1);
            for(i = 0; i < (Adigit - Bdigit); i++){
                mulBy10Int(&temp1, &temp2);
                copyNumberInt(&temp2,&temp1);
            }
            return numCompInt(&a->n, &temp1);
        }else if(Adigit < Bdigit){
            copyNumberInt(&a->n, &temp1);
            for(i = 0; i < Bdigit - Adigit; i++){
                mulBy10Int(&temp1, &temp2);
                copyNumberInt(&temp2, &temp1);
            }
            return numCompInt(&temp1, &b->n);
        }else
            return numCompInt(&a->n, &b->n);
    }
    
}

int addInt(struct  NUMBER *augend, struct NUMBER *addend, struct NUMBER *ans){
    int carry = 0;
    int i;
    int augendSign = getSignInt(augend);
    int addendSign = getSignInt(addend);
    //ともに正
    if((augendSign == 1) && (addendSign == 1)){
        clearByZeroInt(ans);
        for(i = 0; i < DIGIT;i++){
            int sum = augend->n[i] + addend->n[i] + carry;
            ans->n[i] = sum % 10;
            carry = sum / 10;
        }
        if(carry > 0){
            printf("overflow\n");
            clearByZeroInt(ans);
            return 0;
        }
        return 1;
    }
    //augendが負addendが正
    else if((augendSign == -1) && (addendSign == 1)){
        struct NUMBER temp;
        getAbsInt(augend,&temp);
        if(!subInt(addend,&temp,ans)){
            clearByZeroInt(ans);
            return 0;
        }
    }
    //augendが正addendが負
    else if((augendSign == 1) && (addendSign == -1)){
        struct NUMBER temp;
        getAbsInt(addend,&temp);
        if(!subInt(augend, &temp, ans)){
            clearByZeroInt(ans);
            return 0;
        }
    }
    //ともに負
    else {
        struct NUMBER augendTemp,addendTemp;
        getAbsInt(augend,&augendTemp);
        getAbsInt(addend,&addendTemp);
        if(!addInt(&augendTemp, &addendTemp,ans)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans, -1);
    }
    return 0;
}

//ans = minuend - subtrahend
//0...エラー
//1...正常終了
int subInt(struct NUMBER *minuend,struct NUMBER *subtrahend, struct NUMBER *ans){
    int i;
    int borrrow = 0;
    int minuendSign = getSignInt(minuend);
    int subtrahendSign = getSignInt(subtrahend);
    //ともに正のとき
    if((minuendSign == 1) && (subtrahendSign == 1)){
        //a<bのとき入れ替える
        if(numCompInt(minuend,subtrahend) == -1){
            swapInt(minuend,subtrahend);
            if(!subInt(minuend,subtrahend,ans)){
                clearByZeroInt(ans);
                return 0;
            }
            swapInt(minuend,subtrahend);
            setSignInt(ans,-1);
        }else{
            clearByZeroInt(ans);
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
        getAbsInt(subtrahend,&temp);
        if(!addInt(minuend,&temp,ans)){
            clearByZeroInt(ans);
            return 0;
        }
    }
    //minuendが負でsubtrahendが正のとき
    else if((minuendSign == -1) && (subtrahendSign == 1)){
        struct NUMBER temp;
        getAbsInt(minuend,&temp);
        if(!addInt(&temp,subtrahend,ans)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans,-1);
    }
    //ともに負
    else{
        struct NUMBER minuendTemp,subtrahendTemp;
        getAbsInt(minuend,&minuendTemp);
        getAbsInt(subtrahend,&subtrahendTemp);
        if(!subInt(&subtrahendTemp, &minuendTemp, ans)){
            clearByZeroInt(ans);
            return 0;
        }
    }
}
//1足す
//返り値
//0…オーバーフロー
//1…正常終了
int incrementInt(struct NUMBER *source, struct NUMBER *to){
    struct NUMBER one;
    setInt(&one,1);
    return addInt(source,&one,to);
}

int decrementInt(struct NUMBER *source, struct NUMBER *to){
    struct NUMBER one;
    setInt(&one,-1);
    return addInt(source,&one,to);

}
//返り値
//1...正常終了
//0...オーバーフロー
int multipleInt(struct NUMBER *multiplicand, struct NUMBER *multiplier, struct NUMBER *ans){
    struct NUMBER temp, productTemp;
    int carry = 0;//繰り上がり
    clearByZeroInt(ans);
    int i, j;
    int multiplicandDigit = getSignInt(multiplicand);
    int multiplierDigit = getSignInt(multiplier);
    //ともに正
    if(multiplicandDigit == 1 && multiplierDigit == 1){
        for (i = 0; i < DIGIT; i++){
            clearByZeroInt(&temp);
            for (j = 0; j < DIGIT; j++){
                int product = multiplicand->n[j] * multiplier->n[i] + carry;
                if ((j + i) < DIGIT){
                    temp.n[j + i] = product % 10;
                }else if((product % 10) != 0){ 
                    clearByZeroInt(ans);
                    return 0;
                }
                carry = product / 10;
            }
            if(carry != 0){
                clearByZeroInt(ans);
                return 0;
            }
            //ansにtempを加える
            if(!addInt(ans, &temp, &productTemp)){
                clearByZeroInt(ans);
                return 0;
            }
            copyNumberInt(&productTemp, ans);
        }
        return 1;
    }//負×正
    else if(multiplicandDigit == -1 && multiplierDigit == 1){
        struct NUMBER temp;
        getAbsInt(multiplicand,&temp);
        if(!multipleInt(&temp,multiplier,ans)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans,-1);
        return 1;
    }else if(multiplicandDigit == 1 && multiplierDigit == -1){
        struct NUMBER temp;
        getAbsInt(multiplier,&temp);
        if(!multipleInt(multiplicand,&temp,ans)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans,-1);
        return 1;
    }else if(multiplicandDigit == -1 && multiplierDigit == -1){
        struct NUMBER temp1,temp2;
        getAbsInt(multiplicand,&temp1);
        getAbsInt(multiplier,&temp2);
        if(!multipleInt(&temp1,&temp2,ans)){
            clearByZeroInt(ans);
            return 0;
        }
        return 1;
    }
    return 0;
}

//返り値
//0 エラー 0除算
//1 正常終了

int divideInt(struct NUMBER *dividend, struct NUMBER *divisor,struct NUMBER *quotient, struct NUMBER *remainder){
    clearByZeroInt(quotient);
    clearByZeroInt(remainder);
    //ゼロ除算検知
    if(isZeroInt(divisor))
        return 0;
    int dividendSign = getSignInt(dividend);
    int divisorSign = getSignInt(divisor);
    if(dividendSign == 1 && divisorSign == 1){
        struct NUMBER tempDividend,temp;
        copyNumberInt(dividend, &tempDividend);
        while(1){
            if(numCompInt(&tempDividend, divisor) >=0){
                copyNumberInt(divisor,remainder);
                setInt(&temp,1);
                struct NUMBER tempRemainder,tempTemp;
                while(1){
                    if(numCompInt(&tempDividend,remainder) >= 0){
                        //remainderを10倍
                        mulBy10Int(remainder,&tempRemainder);
                        copyNumberInt(&tempRemainder,remainder);
                        //tempも10倍
                        mulBy10Int(&temp,&tempTemp);
                        copyNumberInt(&tempTemp,&temp);
                    }else{
                        divBy10Int(remainder,&tempRemainder);
                        copyNumberInt(&tempRemainder,remainder);
                        divBy10Int(&temp,&tempTemp);
                        copyNumberInt(&tempTemp,&temp);
                        break;
                    }
                }
                
                struct NUMBER ansTemp;
                subInt(&tempDividend,remainder,&ansTemp);
                copyNumberInt(&ansTemp,&tempDividend);
                addInt(quotient,&temp,&ansTemp);
                copyNumberInt(&ansTemp,quotient);
            }else if (numCompInt(&tempDividend,divisor) < 0){
                copyNumberInt(&tempDividend,remainder);
                break;
            }
        }
        return 1;
    }else if (dividendSign == 1 && divisorSign == -1){
        struct NUMBER temp;
        getAbsInt(divisor,&temp);
        divideInt(dividend,&temp,quotient,remainder);
        setSignInt(quotient,-1);
        return 1;
    }else if (dividendSign == -1 && divisorSign == 1){
        struct NUMBER temp;
        getAbsInt(dividend,&temp);
        divideInt(&temp,divisor,quotient,remainder);
        setSignInt(quotient, -1);
        setSignInt(remainder, -1);
        return 1;
    }else if (dividendSign == -1 && divisorSign == -1){
        struct NUMBER  temp1, temp2;
        getAbsInt(dividend, &temp1);
        getAbsInt(divisor, &temp2);
        divideInt(&temp1, &temp2 , quotient, remainder);
        setSignInt(remainder, -1);
        return 1;
    }
    return 0;
}
//除数1桁のときの高速化
//0 エラーゼロ除算
//1 正常終了
int divIntInt(struct NUMBER *dividend, int divisor,struct NUMBER *quotient, int *remainder){
    int remain = 0;
    int i;
    clearByZeroInt(quotient);
    *remainder = 0;
    //ゼロ除算検知
    if(divisor == 0)
        return 0;
    int dividendSign = getSignInt(dividend);
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
        divIntInt(dividend,divisor * -1,quotient,remainder);
        setSignInt(quotient,-1);
        return 1;
    }else if(dividendSign == -1 && divisor >= 0){
        struct NUMBER temp;
        getAbsInt(dividend,&temp);
        divIntInt(&temp,divisor,quotient,remainder);
        setSignInt(quotient, -1);
        *remainder *= -1;
        return 1;
    }else if(dividendSign == -1 && divisor < 0){
        struct NUMBER temp;
        getAbsInt(dividend,&temp);
        divIntInt(&temp,divisor * -1, quotient,remainder);
        *remainder *= -1;
        return 1;
    }
}
//正の平方根を求める。
//戻り値
//0...エラー
//1...正常終了
int numSqrt(struct NUMBER *source,struct NUMBER *sqroot){
    clearByZeroInt(sqroot);
    //初期値をとりあえずソースに
    struct NUMBER x, xOneBefore, xTwoBefore;
    copyNumberInt(source,&x);
    copyNumberInt(source,&xOneBefore);
    copyNumberInt(source,&xTwoBefore);
    if(getSignInt(source) == -1)
        return 0;
    if(getDigitInt(source) <= 1 && (source->n[0] <= 1)){
        copyNumberInt(source, sqroot);
        return 1;
    }
    //振動,収束するまで繰り返す
    while(1){
        //前のxを更新
        copyNumberInt(&xOneBefore,&xTwoBefore);
        copyNumberInt(&x, &xOneBefore);

        //xを更新
        struct NUMBER divTemp,temp,addtemp;
        int remain;
        if(!(divideInt(source, &xOneBefore, &divTemp, &temp)))
            return 0;
        if(!(addInt(&divTemp, &xOneBefore,&addtemp)))
            return 0;
        if(!(divIntInt(&addtemp, 2,&x,&remain)))
            return 0;
        //収束
        if(numCompInt(&x, &xOneBefore) == 0)
            break;
        //振動
        if(numCompInt(&x, &xTwoBefore) == 0){
            //小さい方を採用
            if(numCompInt(&x, &xTwoBefore) == 1)
                copyNumberInt(&xOneBefore, &x);
            break;
        }
    }
    copyNumberInt(&x, sqroot);
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
        copyNumberInt(base,ans);
        return 1;
    }else if(exponent % 2 == 0){
        struct NUMBER square;
        if(!(multipleInt(base, base, &square))){
            clearByZeroInt(ans);
            return 0;
        }
        if(!(power(&square, exponent / 2,ans))){
            clearByZeroInt(ans);
            return 0;
        }
    }else{
        struct NUMBER powerTemp;
        if(!(power(base, exponent - 1, &powerTemp))){
            clearByZeroInt(ans);
            return 0;
        }
        if(!(multipleInt(base, &powerTemp, ans))){
            clearByZeroInt(ans);
            return 0;
        }
    }
    return 1;
}
