#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "number.h"
void clearByZeroInt(struct NUMBER *num){
    int i;
    for(i = 0; i < DIGIT; i++)
        num->n[i] = 0;

    setSign(num,1);
}
void clearByZeroFloat(struct FLOAT *num){
    clearByZeroInt(&(num->n));
    setExp(num, 0);
}

void dispNumberFloat(struct FLOAT *num){
    int i;
    int exp = getExp(num);
    if(getSign(&(num->n)) < 0)
        printf("-");
    if(exp >= 0){

        for(i = getDigit(&num->n) - 1; i >= 0; i--){
            if(i == getDigit(&num->n) - 1)
                printf("%d",num->n.n[i]);
            else
                printf("%09d",num->n.n[i]);
            if(exp == 0)
                printf(".");
            exp--;
        }
        if( exp >= 0 ){
            printf(DISPRAD);
            while(exp != 0){
                printf(DISPRAD);
                exp--;
            }
            printf(".");
        }
    }else{
        printf("0");
        exp++;
        printf("."); 
        while(exp != 0){
            printf(DISPRAD);
            exp++;
        }
        for(i = getDigit(&(num->n))- 1; i >= 0; i--)
            printf("%09d",num->n.n[i]);

    }
    

}

void copyNumberInt(struct NUMBER *source, struct NUMBER *to){
    int i;
    clearByZeroInt(to);
    for (i = 0; i < DIGIT;i++){
        to->n[i] = source->n[i];
    }
    setSign(to,getSign(source));
}
void copyNumberFloat(struct FLOAT *source, struct FLOAT *to){
    clearByZeroFloat(to);
    copyNumberInt(&source->n, &to->n);
    setExp(to, getExp(source));
}

void getAbsInt(struct NUMBER *source,struct NUMBER *to){
    copyNumberInt(source,to);
    setSign(to,1);
}

void getAbsFloat(struct FLOAT *source,struct FLOAT *to){
    clearByZeroFloat(to);
    getAbsInt(&source->n, &to->n);
    setExp(to, getExp(source));
}

//返り値
//1... num == 0
//0... num != 0
//各桁が0であるのに符号変数が負のとき0ではないと返す
int isZeroInt(struct NUMBER *num){
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
//1... num == 0
//0... num != 0
//各桁が0であるのに指数部が0でないのとき0ではないと返す
int isZeroFloat(struct FLOAT *num){
    if(isZeroInt(&num->n)){
        if(getExp(num) == 0)
            return 1;
        else
            return 0;
    }else
        return 0;
}

//RADIXのn乗した結果を返す
//返り値
//1...正常終了
//0...オーバーフロー
int mulByN(struct NUMBER *source,struct NUMBER *to,int n){
    int i;
    clearByZeroInt(to);
    if(isZeroInt(source))
        return 1;
    if(n == 0){
        copyNumberInt(source,to);
        return 1;
    }
    if(n <= 0 ||DIGIT < n || source->n[DIGIT - n] != 0)
        return 0;
    for(i = 0; i < DIGIT - n; i++)
        to->n[i + n] = source->n[i];
    setSign(to, getSign(source));
    return 1;
}

//RADIXのn乗したぶんで割る
//0除算はエラー。桁数以上除算はエラー
//あまりはNUMBERで返す
int divByN(struct NUMBER *source,struct NUMBER *to, int n, struct NUMBER *div){
    int i;
    clearByZeroInt(to);
    if(div != NULL)
        clearByZeroInt(div);
    if(n <= 0 || DIGIT <= n)
        return 0;
    for(i = 0; i < DIGIT; i++){
        if(i < n){
            if(div != NULL)
                div->n[i] = source->n[i];
        }
        else
            to->n[i - n] = source->n[i];
    }
    setSign(to, getSign(source));
    if(div != NULL)
        setSign(div, getSign(source));
    return 1;
}
//返り値
//setをindexに格納
//1...正常終了
//0...設定できなかった
int setInt(struct NUMBER *num, int set ,int index){
    if(set >= 0 && set < RADIX)
        num->n[index] = set;
    else
        return 0;
    return 1;
}

//小数点以下の桁数を返す
int getDigitDecimal(struct FLOAT*num){
    int digit = getDigit(&num->n);
    return digit - 1 - getExp(num);
}
//返り値 桁数
int getDigit(struct NUMBER *num){
    int i;
    for(i = DIGIT - 1; i >= 0;i--){
        if(num->n[i] != 0)
            return i + 1;
    }
    if(isZeroInt(num))
        return 1;
    return 0;
}
//返り値に指数部
int getExp(struct FLOAT *num){
    return num->exp;
}
void setExp(struct FLOAT *num, int exp){
    num->exp = exp;
}

//1...正に-1...負に
int setSign(struct NUMBER *num,int s){
    if(s == 1){
        num->sign = 1;
        return 1;
    }else if(s == -1){
        num->sign = -1;
        return 1;
    }
    return 0;
}
//正なら1負なら-1を返す。
int getSign(struct NUMBER *num){
    if(num->sign == 1)
        return 1;
    else if(num->sign == -1)
        return -1;
    return 0;
}
//1...a>b
//0...a=b
//-1...a<b
int numCompInt(struct NUMBER *a,struct NUMBER *b){
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
//1...a>b
//0...a=b
//-1...a<b
int numCompFloat(struct FLOAT *a,struct FLOAT *b){
    int Aexp = getExp(a);
    int Bexp = getExp(b);
    int Adigit = getDigit(&a->n);
    int Bdigit = getDigit(&b->n);
    struct NUMBER temp1,temp2;
    if(Aexp > Bexp)
        return 1;
    else if(Aexp < Bexp)
        return -1;
    else{
        if(Adigit > Bdigit){
            copyNumberInt(&b->n, &temp1);
            mulByN(&temp1, &temp2, Adigit - Bdigit);
            copyNumberInt(&temp2, &temp1);
            return numCompInt(&a->n, &temp1);
        }else if(Adigit < Bdigit){
            copyNumberInt(&a->n, &temp1);
            mulByN(&temp1, &temp2, Bdigit - Adigit);
            copyNumberInt(&temp2, &temp1);
            return numCompInt(&temp1, &b->n);
        }else
            return numCompInt(&a->n, &b->n);
    }
    
}
//c...キャリーを検知。多倍長浮動小数点数型で使用。それ以外の仕様ではヌルポを渡す
int addInt(struct  NUMBER *augend, struct NUMBER *addend, struct NUMBER *ans, int *c){
    int carry = 0;
    int i;
    int augendSign = getSign(augend);
    int addendSign = getSign(addend);
    int digit = getDigit(augend) >= getDigit(addend) ? getDigit(augend) : getDigit(addend);
    //ともに正
    if((augendSign == 1) && (addendSign == 1)){
        clearByZeroInt(ans);
        for(i = 0; i < DIGIT;i++){
            int sum = augend->n[i] + addend->n[i] + carry;
            ans->n[i] = sum % RADIX;
            carry = sum / RADIX;
            if(c != NULL && i == digit - 1){
                if(carry)
                    *c = 1;
                else
                    *c = 0;
            }
        }
        if(carry > 0){
            if(i == DIGIT){
                if(c != NULL)
                    *c = 1;
                return 0;
            }else{
                if(c != NULL){
                    if(carry)
                        *c = 1;
                    else
                        *c = 0;
                }
                ans->n[digit] = 1;
            }
        }
        return 1;
    }
    //augendが負addendが正
    else if((augendSign == -1) && (addendSign == 1)){
        struct NUMBER temp;
        getAbsInt(augend,&temp);
        if(!subInt(addend,&temp,ans, NULL))
            return 0;
        return 1;
    }
    //augendが正addendが負
    else if((augendSign == 1) && (addendSign == -1)){
        struct NUMBER temp;
        getAbsInt(addend,&temp);
        if(!subInt(augend, &temp, ans, NULL))
            return 0;
        return 1;
    }
    //ともに負
    else {
        struct NUMBER augendTemp,addendTemp;
        getAbsInt(augend,&augendTemp);
        getAbsInt(addend,&addendTemp);
        if(!addInt(&augendTemp, &addendTemp,ans,NULL))
            return 0;
        setSign(ans, -1);
        return 1;
    }
    return 0;
}
//0…エラー
//1…正常終了
int addFloat(struct  FLOAT *augend, struct FLOAT *addend, struct FLOAT *ans){
    int augendSign = getSign(&augend->n);
    int addendSign = getSign(&addend->n);
    int augendDigitDecimal = getDigitDecimal(augend);
    int addendDigitDecimal = getDigitDecimal(addend);
    int digitDiff, moveableDigit;
    int c;
    struct NUMBER temp1,temp2,temp3;
    struct FLOAT temp4,temp5;
    if(augendSign == 1 && addendSign == 1){
        clearByZeroFloat(ans);
        //桁調整をする方を決める。
        copyNumberInt(&augend->n, &temp3);
        copyNumberInt(&addend->n, &temp1);
        if(augendDigitDecimal > addendDigitDecimal){
            digitDiff = augendDigitDecimal - addendDigitDecimal;
            moveableDigit = DIGIT - getDigit(&addend->n);
            if(moveableDigit - digitDiff >= 0){
                mulByN(&temp1, &temp2, digitDiff);
                copyNumberInt(&temp2, &temp1);
            }else{
                mulByN(&temp1, &temp2, moveableDigit);
                copyNumberInt(&temp2, &temp1);
                divByN(&temp3, &temp2, digitDiff - moveableDigit,NULL);
                copyNumberInt(&temp2, &temp3);

            }
        }
        if (augendDigitDecimal >= addendDigitDecimal){
            if(addInt(&temp1, &temp3, &temp2,&c)){
                copyNumberInt(&temp2, &ans->n);
                setExp(ans, getExp(augend) >= getExp(addend) ? getExp(augend) : getExp(addend));
                if(c)
                    ans->exp++;
                return 1;
            }else{
                divByN(&temp2, &ans->n, 1, NULL);
                ans->n.n[DIGIT - 1] = 1;
                setExp(ans, getExp(augend) >= getExp(addend) ? getExp(augend) : getExp(addend));
                if(getExp(ans) >= INT_MAX)
                    return 0;
                ans->exp += 1;
                return 1;
            }
        }else{
            copyNumberFloat(augend, &temp4);
            copyNumberFloat(addend, &temp5);
            if(addFloat(&temp5, &temp4, ans))
                return 1;
            
            return 0;
        }
    }else if(augendSign == -1 && addendSign == 1){
        getAbsFloat(augend, &temp4);
        if(subFloat(addend, &temp4, ans))
            return 1;
        return 0;
    }else if(augendSign == 1 && addendSign == -1){
        getAbsFloat(addend, &temp4);
        if(subFloat(augend, &temp4, ans))
            return 1;
        return 0;
    }else if(augendSign == -1 && addendSign == -1){
        getAbsFloat(augend, &temp4);
        getAbsFloat(addend, &temp5);
        if(addFloat(&temp4, &temp5, ans)){
            setSign(&ans->n, -1);
            return 1;
        }
        return 0;
    }
    return 0;
}


//ans = minuend - subtrahend
//0...エラー
//1...正常終了
//b…繰り下がりの桁数を返す
int subInt(struct NUMBER *minuend,struct NUMBER *subtrahend, struct NUMBER *ans, int *b){
    int i;
    int borrrow = 0;
    int minuendSign = getSign(minuend);
    int subtrahendSign = getSign(subtrahend);
    struct NUMBER temp1, temp2;
    int digit = getDigit(minuend) >= getDigit(subtrahend) ? getDigit(minuend) : getDigit(subtrahend);
    if(b != NULL)
        *b = digit; 
    //ともに正のとき
    if((minuendSign == 1) && (subtrahendSign == 1)){
        //a<bのとき入れ替える
        if(numCompInt(minuend,subtrahend) == -1){
            copyNumberInt(minuend, &temp1);
            copyNumberInt(subtrahend, &temp2);
            if(!subInt(&temp2,&temp1,ans, b))
                return 0;

            //swapInt(minuend,subtrahend);
            setSign(ans,-1);
            return 1;
        }else{
            clearByZeroInt(ans);
            for(i = 0;i < digit; i++){
                //繰り下がり考慮
                int minuendDigit = minuend->n[i] - borrrow;
                int subtrahendDigit = subtrahend->n[i];
                if(minuendDigit >= subtrahendDigit){
                    ans->n[i] = minuendDigit - subtrahendDigit;
                    borrrow = 0;
                }else{
                    ans->n[i] = RADIX + minuendDigit - subtrahendDigit;
                    borrrow = 1;
                }
            }
            if(borrrow != 0){
                return 0;
            }

            //繰り下がり桁数の決定
            if(b != NULL)
                *b -= getDigit(ans);
            
            return 1;
        }
    }
    //minuendが正でsubtrahedが負のとき
    else if((minuendSign == 1) && (subtrahendSign == -1)){
        struct NUMBER temp;
        getAbsInt(subtrahend,&temp);
        if(!addInt(minuend,&temp,ans,NULL))
            return 0;
    }
    //minuendが負でsubtrahendが正のとき
    else if((minuendSign == -1) && (subtrahendSign == 1)){
        struct NUMBER temp;
        getAbsInt(minuend,&temp);
        if(!addInt(&temp,subtrahend,ans,NULL))
            return 0;
        setSign(ans,-1);
    }
    //ともに負
    else{
        struct NUMBER minuendTemp,subtrahendTemp;
        getAbsInt(minuend,&minuendTemp);
        getAbsInt(subtrahend,&subtrahendTemp);
        if(!subInt(&subtrahendTemp, &minuendTemp, ans, NULL))
            return 0;
    }
    return 0;
}

int subFloat(struct FLOAT *minuend ,struct FLOAT *subtrahend, struct FLOAT *ans){

    clearByZeroFloat(ans);

    //桁調整をする方を決める。
    int minuendSign = getSign(&minuend->n);
    int subtrahendSign = getSign(&subtrahend->n);
    int minuendDigitDecimal = getDigitDecimal(minuend);
    int subtrahendDigitDecimal = getDigitDecimal(subtrahend);
    int digitDiff, moveableDigit;
    int b;
    struct NUMBER temp1,temp2,temp3;
    struct FLOAT temp4,temp5;
    if(minuendSign == 1 && subtrahendSign == 1){
        copyNumberInt(&minuend->n, &temp3);
        copyNumberInt(&subtrahend->n, &temp1);
        if(minuendDigitDecimal > subtrahendDigitDecimal){
            digitDiff = minuendDigitDecimal - subtrahendDigitDecimal;
            moveableDigit = DIGIT - getDigit(&subtrahend->n);
            if(moveableDigit - digitDiff >= 0){
                mulByN(&temp1, &temp2, digitDiff);
                copyNumberInt(&temp2, &temp1);
            }else{
                mulByN(&temp1, &temp2, moveableDigit);
                copyNumberInt(&temp2, &temp1);
                divByN(&temp3, &temp2, digitDiff - moveableDigit,NULL);
                copyNumberInt(&temp2, &temp3);
            }
        }
        if(minuendDigitDecimal >= subtrahendDigitDecimal){
        
            if(subInt(&temp3, &temp1, &temp2, &b)){
                copyNumberInt(&temp2, &ans->n);
                setExp(ans, getExp(minuend) >= getExp(subtrahend) ? getExp(minuend) : getExp(subtrahend));
                if(b)
                    ans->exp -= b;
                return 1;

            }else{
                return 0;
            }
        }else { 
            copyNumberFloat(minuend, &temp4);
            copyNumberFloat(subtrahend, &temp5);
            if(subFloat(&temp5, &temp4, ans)){
                if(numCompFloat(&temp5, &temp4) == 1)
                    setSign(&ans->n,-1);
                else if(numCompFloat(&temp5, &temp4) == -1)
                    setSign(&ans->n, 1);
                return 1;
            }
            return 0;

        }
    }else if(minuendSign == 1 && subtrahendSign == -1){
        getAbsFloat(subtrahend, &temp4);
        if(addFloat(minuend, &temp4, ans))
            return 1;
        return 0;
    }else if(minuendSign == -1 && subtrahendSign == 1){
        getAbsFloat(minuend, &temp4);
        if(addFloat(&temp4, subtrahend, ans)){
            setSign(&ans->n, -1);
            return 1;
        }
        return 0;
    }else if(minuendSign == -1 && subtrahendSign == -1){
        getAbsFloat(minuend, &temp4);
        getAbsFloat(subtrahend, &temp5);
        if(subFloat(&temp5, &temp4, ans))
            return 1;
        return 0;
    }
    return 0;
}
//1足す
//返り値
//0…オーバーフロー
//1…正常終了
int incrementInt(struct NUMBER *source, struct NUMBER *to){
    struct NUMBER one;
    clearByZeroInt(&one);
    setInt(&one, 1, 0);
    return addInt(source,&one,to,NULL);
}

//返り値
//1...正常終了
//0...オーバーフロー
//オーバーフロー時の繰り上がり分をcに返す
int multipleInt(struct NUMBER *multiplicand, struct NUMBER *multiplier, struct NUMBER *ans, struct NUMBER *c){
    struct NUMBER temp, productTemp,carryTemp1,carryTemp2,carryTemp3;
    int carry = 0;//繰り上がり
    clearByZeroInt(ans);
    if(c != NULL){
        clearByZeroInt(c);
    }
    clearByZeroInt(&carryTemp1);
    clearByZeroInt(&carryTemp2);
    clearByZeroInt(&carryTemp3);
    int i, j;
    int multiplicandDigit = getSign(multiplicand);
    int multiplierDigit = getSign(multiplier);
    //ともに正
    if(multiplicandDigit == 1 && multiplierDigit == 1){
        for (i = 0; i < getDigit(multiplier); i++){
            clearByZeroInt(&temp);
            clearByZeroInt(&carryTemp2);
            for (j = 0; j < getDigit(multiplicand); j++){
                long long int product = (long long int)multiplicand->n[j] * (long long int)multiplier->n[i] + (long long int)carry;
                if ((j + i) < DIGIT){
                    temp.n[j + i] = (int)(product % RADIX);
                }else if((product % RADIX) != 0){
                    carryTemp2.n[(j + i) - DIGIT] = (int)(product % RADIX);
                }
                carry = (int)(product / RADIX);
            }
            if(carry != 0){
                if((j + i) < DIGIT)
                    temp.n[j + i] = carry;
                else
                    carryTemp2.n[(j + i) - DIGIT] = carry;
                carry = 0;
            }
            //ansにtempを加える
            if(!addInt(ans, &temp, &productTemp,NULL)){
                incrementInt(&carryTemp2,&carryTemp3);
                copyNumberInt(&carryTemp3,&carryTemp2);
            }
            copyNumberInt(&productTemp, ans);

            //繰り上がりの計算
            addInt(&carryTemp1, &carryTemp2, &carryTemp3,NULL);
            copyNumberInt(&carryTemp3, &carryTemp1);
        }
        if(c != NULL)
            copyNumberInt(&carryTemp1, c);
        if(!isZeroInt(&carryTemp1))
            return 0;
        return 1;
    }//負×正
    else if(multiplicandDigit == -1 && multiplierDigit == 1){
        struct NUMBER temp;
        getAbsInt(multiplicand,&temp);
        if(!multipleInt(&temp,multiplier,ans,NULL))
            return 0;
        setSign(ans,-1);
        return 1;
    }else if(multiplicandDigit == 1 && multiplierDigit == -1){
        struct NUMBER temp;
        getAbsInt(multiplier,&temp);
       if(!multipleInt(multiplicand,&temp,ans, NULL))
            return 0;
        setSign(ans,-1);
        return 1;
    }else if(multiplicandDigit == -1 && multiplierDigit == -1){
        struct NUMBER temp1,temp2;
        getAbsInt(multiplicand,&temp1);
        getAbsInt(multiplier,&temp2);
        if(!multipleInt(&temp1,&temp2,ans, NULL))
            return 0;
        return 1;
    }
    return 0;
}

//返り値
//1...正常終了
//0...オーバーフロー
int multipleFloat(struct FLOAT *multiplicand, struct FLOAT *multiplier, struct FLOAT *ans){
    //指数部のみでオーバフローをとりあえず検知
    int multiplicandSign = getSign(&multiplicand->n);
    int multiplierSign = getSign(&multiplier->n);
    int i;
    clearByZeroFloat(ans);
    struct NUMBER carry, temp;
    struct FLOAT temp1, temp2;
    int digit;
    clearByZeroInt(&carry);
    if((multiplicand->exp >= 0 && multiplier->exp >= 0) || (multiplicand->exp <= 0 && multiplier->exp <= 0)){
        if(multiplicand->exp >= 0){
            if(multiplier->exp > INT_MAX - multiplicand->exp)
                return 0;
        }else {
            if(multiplier->exp < INT_MIN - multiplicand->exp)
                return 0;
        }
    }
    if(multiplicandSign == 1 && multiplierSign == 1){
        if(multipleInt(&multiplicand->n, &multiplier->n, &ans->n, &carry)){
            ans->exp += multiplicand->exp + multiplier->exp;
            if(getDigit(&multiplicand->n) + getDigit(&multiplier->n) <= getDigit(&ans->n)){
                if(getExp(ans) == INT_MAX)
                    return 0;
                ans->exp++;
            }

            return 1;
        }else{
            ans->exp += multiplicand->exp + multiplier->exp;

            //繰り上がりがあるかどうか
            if(getDigit(&multiplicand->n) + getDigit(&multiplier->n) - DIGIT <= getDigit(&carry)){
                if(ans->exp == INT_MAX)
                    return 0;
                ans->exp++;
            }
            divByN(&ans->n, &temp, getDigit(&carry), NULL);
            digit = DIGIT - getDigit(&carry);
            for(i = 0; i < getDigit(&carry); i++){
                temp.n[digit + i] = carry.n[i];
            }
            copyNumberInt(&temp, &ans->n);
            return 1;
        }
    }else if(multiplicandSign == -1 && multiplierSign == 1){
        getAbsFloat(multiplicand, &temp1);
        if(multipleFloat(&temp1, multiplier, ans)){
            setSign(&ans->n, -1);
            return 1;
        }
        return 0;
    }else if(multiplicandSign == 1 && multiplierSign == -1){
        getAbsFloat(multiplier, &temp2);
        if(multipleFloat(multiplicand, &temp2, ans)){
            setSign(&ans->n, -1);
            return 1;
        }
        return 0;
    }else if(multiplicandSign == -1 && multiplierSign == -1){
        getAbsFloat(multiplicand, &temp1);
        getAbsFloat(multiplier, &temp2);
        if(multipleFloat(&temp1, &temp2, ans))
            return 1;
        return 0;
    }
    return 0;
}
//1...正常終了
//0...エラー
//逆数によって実装
int divideFloat(struct FLOAT *dividend, struct FLOAT *divisor, struct FLOAT *ans){
    struct FLOAT reciprocalNum;
    if(!reciprocal(divisor, &reciprocalNum))
        return 0;
    multipleFloat(dividend, &reciprocalNum, ans);
    return 1;
}
//正の平方根を求める。
//戻り値
//0...エラー
//1...正常終了
int numSqrt(struct FLOAT *source,struct FLOAT *sqroot){
    struct FLOAT x, xAfter, half, newDist, oldDist, temp1, temp2;
    clearByZeroFloat(sqroot);
    if(getSign(&source->n) == -1)
        return 0;
    if(isZeroFloat(source))
        return 1;
    //初期値
    //setFloat(&x, 5, source->exp / 2);
    copyNumberFloat(source, &x);
    clearByZeroFloat(&half);
    setInt(&half.n, 5 * (RADIX / 10), 0);
    setExp(&half, -1);
    //oldDist
    if(!power(&x, 2, &temp1))
        return 0;
    if(!subFloat(&temp1, source, &temp2))
        return 0;
    getAbsFloat(&temp2, &oldDist);
    while(1){
        if(!divideFloat(source, &x, &temp1))
            return 0;
        if(!addFloat(&x, &temp1, &temp2))
            return 0;
        if(!multipleFloat(&half, &temp2, &xAfter))
            return 0;
        //newDist
        if(!power(&xAfter, 2, &temp1))
            return 0;
        if(!subFloat(&temp1, source, &temp2))
            return 0;
        getAbsFloat(&temp2, &newDist);
        //収束条件
        if(numCompFloat(&oldDist, &newDist) <= 0)
            break;
        copyNumberFloat(&xAfter, &x);
        copyNumberFloat(&newDist, &oldDist);
    }
    copyNumberFloat(&x, sqroot);
    return 1;
}

//baseのexponent乗を返す。(exponent>=0)ゼロのゼロ乗は1とする
//オーバーフローしたら0を入れる。
//0…エラー、オーバーフロー
//1…正常終了
int power(struct FLOAT *base, int exponent,struct FLOAT *ans){
    struct FLOAT square, powerTemp;
    if(exponent < 0)
        return 0;
    else if(exponent == 0){
        clearByZeroFloat(ans);
        setInt(&ans->n, 1, 0);
        setExp(ans, 1);
        return 1;
    }else if(exponent == 1){
        copyNumberFloat(base,ans);
        return 1;
    }else if(exponent % 2 == 0){
        if(!(multipleFloat(base, base, &square)))
            return 0;
        if(!(power(&square, exponent / 2,ans)))
            return 0;
    }else{
        if(!(power(base, exponent - 1, &powerTemp)))
            return 0;
        if(!(multipleFloat(base, &powerTemp, ans)))
            return 0;
    }
    return 1;
}

//sourceの逆数を返す
//1...正常終了
//0...エラー
int reciprocal(struct FLOAT *source, struct FLOAT *to){
    //ニュートンラフソンをつかう
    struct FLOAT x, xAfter, temp1, temp3, two, one,oneNear, oldDist, newDist;
    int sourceSign = getSign(&source->n);
    int sourceExp = getExp(source);
    clearByZeroFloat(to);
    if(isZeroFloat(source))
        return 0;
    if(sourceSign == 1){
        //初期値x = 0.2 * 10 ^(-N)
        clearByZeroFloat(&x);
        clearByZeroFloat(&one);
        clearByZeroFloat(&two);
        setInt(&x.n, 2, 0);
        setExp(&x, -(sourceExp + 1));
        setInt(&one.n, 1, 0);
        setInt(&two.n, 2, 0); 
        if(!multipleFloat(&x, source, &oneNear))
            return -1;
        //oldDist = abs(1-x * source)
        if(!(multipleFloat(&x, source, &temp1)))
            return 0;
        if(!subFloat(&one, &temp1, &temp3))
            return 0;
        getAbsFloat(&temp3, &oldDist);
        //ニュートンラフソン

        while(1){
            if(!subFloat(&two, &oneNear, &temp3))
                return 0;
            if(!multipleFloat(&temp3, &x, &xAfter))
                return 0;

            //終了条件
            //newDesit=abs(1-x*source)
            if(!(multipleFloat(&xAfter, source, &oneNear)))
                return 0;
            if(!subFloat(&one, &oneNear, &temp3))
                return 0;
            getAbsFloat(&temp3, &newDist);
            //差が小さくなっていたら続行
            if(numCompFloat(&oldDist, &newDist) <= 0)
                break;
            copyNumberFloat(&xAfter, &x);
            copyNumberFloat(&newDist, &oldDist);
        }
        copyNumberFloat(&x, to);
        //divByRadInt(&to->n, &temp);
        //copyNumberInt(&temp, &to->n);
        return 1;
    }else if(sourceSign == -1){
        getAbsFloat(source, &temp1);
        if(reciprocal(&temp1, to)){
            setSign(&to->n, -1);
            return 1;
        }
        return 0;
    }
    return 0;
}
