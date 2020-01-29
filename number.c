#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <limits.h>
#include "number.h"
void clearByZeroInt(struct NUMBER *num){
    int i;
    for(i = 0; i < DIGIT; i++)
        num->n[i] = 0;

    setSignInt(num,1);
}
void clearByZeroFloat(struct FLOAT *num){
    clearByZeroInt(&(num->n));
    setExp(num, 0);
}

void dispNumberInt(struct NUMBER *num){
    int i;
    if(getSignInt(num) > 0)
        printf("+");
    else
        printf("-");
    for(i = DIGIT - 1;i >= 0;i--)
        printf(" %09d",num->n[i]);
}
void dispNumberFloat(struct FLOAT *num){
    int i;
    int exp = getExp(num);
    if(getSignInt(&(num->n)) > 0)
        printf("+");
    else
        printf("-");
    if(exp >= 0){

        for(i = getDigitInt(&(num->n)) - 1; i >= 0; i--){
            printf(" %09d",num->n.n[i]);
            if(exp == 0)
                printf(".");
            exp--;
        }
        if( exp >= 0 ){
            printf(" ");
            printf(DISPRAD);
            while(exp != 0){
                printf(" ");
                printf(DISPRAD);
                exp--;
            }
            printf(".");
        }
    }else{
        printf(" ");
        printf(DISPRAD);
        exp++;
        printf("."); 
        while(exp != 0){
            printf(" ");
            printf(DISPRAD);
            exp++;
        }
        for(i = getDigitInt(&(num->n))- 1; i >= 0; i--)
            printf(" %09d",num->n.n[i]);

    }
    
    
}
void dispNumberFloatforCopy(struct FLOAT *num){
    int i;
    int exp = getExp(num);
    if(getSignInt(&(num->n)) < 0)
        printf("-");
    if(exp >= 0){

        for(i = getDigitInt(&(num->n)) - 1; i >= 0; i--){
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
        for(i = getDigitInt(&(num->n))- 1; i >= 0; i--)
            printf("%09d",num->n.n[i]);

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
    setExp(to, getExp(source));
}

void getAbsInt(struct NUMBER *source,struct NUMBER *to){
    copyNumberInt(source,to);
    setSignInt(to,1);
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
        if(getExp(num) == 0)
            return 1;
        else
            return 0;
    }else
        return 0;
}

//返り値
//1...正常終了
//0...オーバーフロー
int mulByRadInt(struct NUMBER *source,struct NUMBER *to){
    int i;
    clearByZeroInt(to);
    if(isZeroInt(source))
        return 1;
    if(source->n[DIGIT - 1] != 0)
        return 0;
    for(i = 0;i < DIGIT - 1;i++){
        to->n[i + 1] = source->n[i];
    }
    to->n[0] = 0;
    setSignInt(to,getSignInt(source));
    return 1;
}
//10のn乗した結果を返す
//返り値
//1...正常終了
//0...オーバーフロー
int mulByNInt(struct NUMBER *source,struct NUMBER *to,int n){
    int i;
    clearByZeroInt(to);
    if(isZeroInt(source))
        return 1;
    if(n == 0){
        copyNumberInt(source,to);
        return 1;
    }
    if(DIGIT < n || source->n[DIGIT - n] != 0)
        return 0;
    for(i = 0; i < DIGIT - n; i++)
        to->n[i + n] = source->n[i];
    setSignInt(to, getSignInt(source));
    return 1;
}

//返り値
//割り算の剰余
int divByRadInt(struct NUMBER *source,struct NUMBER *to){
    int i,temp;
    clearByZeroInt(to);
    if(isZeroInt(source))
        return 0;
    temp = source->n[0];
    for(i = 0;i < DIGIT - 1; i++){
        to->n[i] = source->n[i + 1];
    }
    to->n[DIGIT - 1] = 0;
    setSignInt(to,getSignInt(source));
    return getSignInt(source) * temp;
}
//10のn乗したぶんで割る
//0除算はエラー。桁数以上除算はエラー
//あまりはNUMBERで返す
int divByNInt(struct NUMBER *source,struct NUMBER *to, int n, struct NUMBER *div){
    int i;
    clearByZeroInt(to);
    if(div != NULL)
        clearByZeroInt(div);
    if(isZeroInt(source) || DIGIT <= n)
        return 0;
    for(i = 0; i < DIGIT; i++){
        if(i < n){
            if(div != NULL)
                div->n[i] = source->n[i];
        }
        else
            to->n[i - n] = source->n[i];
    }
    setSignInt(to, getSignInt(source));
    if(div != NULL)
        setSignInt(div, getSignInt(source));
    return 1;
}
//1...正常終了
//0...設定できなかった
//digit桁の乱数をnumに入れる。signは符号
int setRandomInt(struct NUMBER *num, int digit){
    int i;
    clearByZeroInt(num);
    if(digit > DIGIT)
        return 0;
    num->sign = rand() % 2 ? -1 : 1;
    for(i = 0; i < digit; i++)
        num->n[i] = rand() % RADIX;
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
//1...正常設定
//0...設定できなかった
int setRandomFloat(struct FLOAT *num, int digit, int ex){
    clearByZeroFloat(num);
    if(!setRandomInt(&num->n, digit))
        return 0;
    setExp(num, rand() % ex * (rand() % 2 ? 1 : -1)); 
}

//小数点以下の桁数を返す
int getDigitDecimal(struct FLOAT*num){
    int digit = getDigitInt(&num->n);
    return digit - 1 - getExp(num);
}
//仮数部の無意味なゼロを省く
//24000->24
int clearByZeroDecimal(struct FLOAT *source, struct FLOAT *to){
    int cnt = 0;
    clearByZeroFloat(to);
    if(isZeroFloat(source))
        copyNumberFloat(source, to);
    while(1){
        if(source->n.n[cnt] != 0)
            break;
        cnt++;
    }
    if(cnt != 0)
        divByNInt(&source->n, &to->n, cnt, NULL);
    else
        copyNumberFloat(source, to);
    setExp(to, getExp(source));
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
//返り値に指数部
int getExp(struct FLOAT *num){
    return num->exp;
}
void setExp(struct FLOAT *num, int exp){
    num->exp = exp;
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
int getSignInt(struct NUMBER *num){
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
int numCompFloat(struct FLOAT *a,struct FLOAT *b){
    int Aexp = getExp(a);
    int Bexp = getExp(b);
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
            mulByNInt(&temp1, &temp2, Adigit - Bdigit);
            copyNumberInt(&temp2, &temp1);
            return numCompInt(&a->n, &temp1);
        }else if(Adigit < Bdigit){
            copyNumberInt(&a->n, &temp1);
            mulByNInt(&temp1, &temp2, Bdigit - Adigit);
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
    int augendSign = getSignInt(augend);
    int addendSign = getSignInt(addend);
    int digit = getDigitInt(augend) >= getDigitInt(addend) ? getDigitInt(augend) : getDigitInt(addend);
    //ともに正
    if((augendSign == 1) && (addendSign == 1)){
        clearByZeroInt(ans);
        for(i = 0; i < DIGIT;i++){
            long long int sum = augend->n[i] + addend->n[i] + carry;
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
        if(!subInt(addend,&temp,ans, NULL)){
            clearByZeroInt(ans);
            return 0;
        }
        return 1;
    }
    //augendが正addendが負
    else if((augendSign == 1) && (addendSign == -1)){
        struct NUMBER temp;
        getAbsInt(addend,&temp);
        if(!subInt(augend, &temp, ans, NULL)){
            clearByZeroInt(ans);
            return 0;
        }
        return 1;
    }
    //ともに負
    else {
        struct NUMBER augendTemp,addendTemp;
        getAbsInt(augend,&augendTemp);
        getAbsInt(addend,&addendTemp);
        if(!addInt(&augendTemp, &addendTemp,ans,NULL)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans, -1);
        return 1;
    }
    return 0;
}
//0…エラー
//1…正常終了
int addFloat(struct  FLOAT *augend, struct FLOAT *addend, struct FLOAT *ans){
    int augendSign = getSignInt(&augend->n);
    int addendSign = getSignInt(&addend->n);
    int augendDigitDecimal = getDigitDecimal(augend);
    int addendDigitDecimal = getDigitDecimal(addend);
    int digitDiff, moveableDigit;
    int i, j, c;
    struct NUMBER temp1,temp2,temp3;
    struct FLOAT temp4,temp5;
    if(augendSign == 1 && addendSign == 1){
        clearByZeroFloat(ans);
        //桁調整をする方を決める。
        if(augendDigitDecimal > addendDigitDecimal){
            digitDiff = augendDigitDecimal - addendDigitDecimal;
            moveableDigit = DIGIT - getDigitInt(&addend->n);
            copyNumberInt(&augend->n, &temp3);
            copyNumberInt(&addend->n, &temp1);
            if(moveableDigit - digitDiff >= 0){
                mulByNInt(&temp1, &temp2, digitDiff);
                copyNumberInt(&temp2, &temp1);
            }else{
                mulByNInt(&temp1, &temp2, moveableDigit);
                copyNumberInt(&temp2, &temp1);
                divByNInt(&temp3, &temp2, digitDiff - moveableDigit,NULL);
                copyNumberInt(&temp2, &temp3);

            }

            if(addInt(&temp1, &temp3, &temp2,&c)){
                copyNumberInt(&temp2, &ans->n);
                setExp(ans, getExp(augend) >= getExp(addend) ? getExp(augend) : getExp(addend));
                if(c)
                    ans->exp++;
                return 1;
            }else{
                divByRadInt(&temp2, &ans->n);
                ans->n.n[DIGIT - 1] = 1;
                setExp(ans, getExp(augend) >= getExp(addend) ? getExp(augend) : getExp(addend));
                if(getExp(ans) >= INT_MAX)
                    return 0;
                ans->exp += 1;
                return 1;
            }
        }else if (augendDigitDecimal == addendDigitDecimal){
            if(addInt(&augend->n, &addend->n,&temp1,&c)){
                copyNumberInt(&temp1, &ans->n);
                setExp(ans, getExp(augend) >= getExp(addend) ? getExp(augend) : getExp(addend));
                if(c)
                    ans->exp++;
                return 1;
            }else{
                divByRadInt(&temp1, &ans->n);
                ans->n.n[DIGIT - 1] = 1;
                setExp(ans, getExp(augend) >= getExp(addend) ? getExp(augend) : getExp(addend));
                if(getExp(ans) == INT_MAX)
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
            setSignInt(&ans->n, -1);
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
    int minuendSign = getSignInt(minuend);
    int subtrahendSign = getSignInt(subtrahend);
    int digit = getDigitInt(minuend) >= getDigitInt(subtrahend) ? getDigitInt(minuend) : getDigitInt(subtrahend);
    if(b != NULL)
        *b = digit; 
    //ともに正のとき
    if((minuendSign == 1) && (subtrahendSign == 1)){
        //a<bのとき入れ替える
        if(numCompInt(minuend,subtrahend) == -1){
            swapInt(minuend,subtrahend);
            if(!subInt(minuend,subtrahend,ans, b)){
                clearByZeroInt(ans);
                return 0;
            }
            swapInt(minuend,subtrahend);
            setSignInt(ans,-1);
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
                printf("over flow\n");
                return 0;
            }

            //繰り下がり桁数の決定
            if(b != NULL)
                *b -= getDigitInt(ans);
            
            return 1;
        }
    }
    //minuendが正でsubtrahedが負のとき
    else if((minuendSign == 1) && (subtrahendSign == -1)){
        struct NUMBER temp;
        getAbsInt(subtrahend,&temp);
        if(!addInt(minuend,&temp,ans,NULL)){
            clearByZeroInt(ans);
            return 0;
        }
    }
    //minuendが負でsubtrahendが正のとき
    else if((minuendSign == -1) && (subtrahendSign == 1)){
        struct NUMBER temp;
        getAbsInt(minuend,&temp);
        if(!addInt(&temp,subtrahend,ans,NULL)){
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
        if(!subInt(&subtrahendTemp, &minuendTemp, ans, NULL)){
            clearByZeroInt(ans);
            return 0;
        }
    }
    return 0;
}

int subFloat(struct FLOAT *minuend ,struct FLOAT *subtrahend, struct FLOAT *ans){

    clearByZeroFloat(ans);

    //桁調整をする方を決める。
    int minuendSign = getSignInt(&minuend->n);
    int subtrahendSign = getSignInt(&subtrahend->n);
    int minuendDigitDecimal = getDigitDecimal(minuend);
    int subtrahendDigitDecimal = getDigitDecimal(subtrahend);
    int digitDiff, moveableDigit;
    int i, j, b;
    struct NUMBER temp1,temp2,temp3;
    struct FLOAT temp4,temp5;
    if(minuendSign == 1 && subtrahendSign == 1){
        if(minuendDigitDecimal > subtrahendDigitDecimal){
            digitDiff = minuendDigitDecimal - subtrahendDigitDecimal;
            moveableDigit = DIGIT - getDigitInt(&subtrahend->n);
            copyNumberInt(&minuend->n, &temp3);
            copyNumberInt(&subtrahend->n, &temp1);
            if(moveableDigit - digitDiff >= 0){
                mulByNInt(&temp1, &temp2, digitDiff);
                copyNumberInt(&temp2, &temp1);
            }else{
                mulByNInt(&temp1, &temp2, moveableDigit);
                copyNumberInt(&temp2, &temp1);
                divByNInt(&temp3, &temp2, digitDiff - moveableDigit,NULL);
                copyNumberInt(&temp2, &temp3);

            }
            if(subInt(&temp3, &temp1, &temp2, &b)){
                copyNumberInt(&temp2, &ans->n);
                setExp(ans, getExp(minuend) >= getExp(subtrahend) ? getExp(minuend) : getExp(subtrahend));
                if(b)
                    ans->exp -= b;
                return 1;

            }else{
                return 0;
            }
            
        }else if(minuendDigitDecimal == subtrahendDigitDecimal){

            if(subInt(&minuend->n, &subtrahend->n, &temp2, &b)){
                copyNumberInt(&temp2, &ans->n);
                setExp(ans, getExp(minuend) >= getExp(subtrahend) ? getExp(minuend) : getExp(subtrahend));
                if(b)
                    ans->exp -= b;
                return 1;

            }else
                return 0;
        }else { 
            copyNumberFloat(minuend, &temp4);
            copyNumberFloat(subtrahend, &temp5);
            if(subFloat(&temp5, &temp4, ans)){
                if(numCompFloat(&temp5, &temp4) == 1)
                    setSignInt(&ans->n,-1);
                else if(numCompFloat(&temp5, &temp4) == -1)
                    setSignInt(&ans->n, 1);
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
            setSignInt(&ans->n, -1);
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

int decrementInt(struct NUMBER *source, struct NUMBER *to){
    struct NUMBER one;
    setInt(&one,1, 0);
    return subInt(source,&one,to,NULL);

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
    int multiplicandDigit = getSignInt(multiplicand);
    int multiplierDigit = getSignInt(multiplier);
    //ともに正
    if(multiplicandDigit == 1 && multiplierDigit == 1){
        for (i = 0; i < getDigitInt(multiplier); i++){
            clearByZeroInt(&temp);
            clearByZeroInt(&carryTemp2);
            for (j = 0; j < getDigitInt(multiplicand); j++){
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
        if(!multipleInt(&temp,multiplier,ans,NULL)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans,-1);
        return 1;
    }else if(multiplicandDigit == 1 && multiplierDigit == -1){
        struct NUMBER temp;
        getAbsInt(multiplier,&temp);
       if(!multipleInt(multiplicand,&temp,ans, NULL)){
            clearByZeroInt(ans);
            return 0;
        }
        setSignInt(ans,-1);
        return 1;
    }else if(multiplicandDigit == -1 && multiplierDigit == -1){
        struct NUMBER temp1,temp2;
        getAbsInt(multiplicand,&temp1);
        getAbsInt(multiplier,&temp2);
        if(!multipleInt(&temp1,&temp2,ans, NULL)){
            clearByZeroInt(ans);
            return 0;
        }
        return 1;
    }
    return 0;
}

//返り値
//1...正常終了
//0...オーバーフロー
int multipleFloat(struct FLOAT *multiplicand, struct FLOAT *multiplier, struct FLOAT *ans){
    //指数部のみでオーバフローをとりあえず検知
    int multiplicandSign = getSignInt(&multiplicand->n);
    int multiplierSign = getSignInt(&multiplier->n);
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
    ////不要なゼロを消す
    clearByZeroDecimal(multiplicand, &temp1);
    copyNumberFloat(&temp1, multiplicand);
    clearByZeroDecimal(multiplier, &temp2);
    copyNumberFloat(&temp2, multiplier);
    if(multiplicandSign == 1 && multiplierSign == 1){
        if(multipleInt(&multiplicand->n, &multiplier->n, &ans->n, &carry)){
            ans->exp += multiplicand->exp + multiplier->exp;
            if(getDigitInt(&multiplicand->n) + getDigitInt(&multiplier->n) <= getDigitInt(&ans->n)){
                if(getExp(ans) == INT_MAX)
                    return 0;
                ans->exp++;
            }

            return 1;
        }else{
            ans->exp += multiplicand->exp + multiplier->exp;

            //繰り上がりがあるかどうか
            if(getDigitInt(&multiplicand->n) + getDigitInt(&multiplier->n) - DIGIT <= getDigitInt(&carry)){
                if(ans->exp == INT_MAX)
                    return 0;
                ans->exp++;
            }
            divByNInt(&ans->n, &temp, getDigitInt(&carry), NULL);
            digit = DIGIT - getDigitInt(&carry);
            for(i = 0; i < getDigitInt(&carry); i++){
                temp.n[digit + i] = carry.n[i];
            }
            copyNumberInt(&temp, &ans->n);
            return 1;
        }
    }else if(multiplicandSign == -1 && multiplierSign == 1){
        getAbsFloat(multiplicand, &temp1);
        if(multipleFloat(&temp1, multiplier, ans)){
            setSignInt(&ans->n, -1);
            return 1;
        }
        return 0;
    }else if(multiplicandSign == 1 && multiplierSign == -1){
        getAbsFloat(multiplier, &temp2);
        if(multipleFloat(multiplicand, &temp2, ans)){
            setSignInt(&ans->n, -1);
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
/*
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
                        mulByRadInt(remainder,&tempRemainder);
                        copyNumberInt(&tempRemainder,remainder);
                        //tempも10倍
                        mulByRadInt(&temp,&tempTemp);
                        copyNumberInt(&tempTemp,&temp);
                    }else{
                        divByRadInt(remainder,&tempRemainder);
                        copyNumberInt(&tempRemainder,remainder);
                        divByRadInt(&temp,&tempTemp);
                        copyNumberInt(&tempTemp,&temp);
                        break;
                    }
                }
                
                struct NUMBER ansTemp;
                subInt(&tempDividend,remainder,&ansTemp, NULL);
                copyNumberInt(&ansTemp,&tempDividend);
                addInt(quotient,&temp,&ansTemp,NULL);
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
*/
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
/*
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
    return 0;
}
*/
//正の平方根を求める。
//戻り値
//0...エラー
//1...正常終了
int numSqrt(struct FLOAT *source,struct FLOAT *sqroot){
    struct FLOAT x, xAfter, half, newDist, oldDist, temp1, temp2;
    clearByZeroFloat(sqroot);
    if(getSignInt(&source->n) == -1)
        return 0;
    if(isZeroFloat(source))
        return 1;
    //初期値
    //setFloat(&x, 5, source->exp / 2);
    copyNumberFloat(source, &x);
    clearByZeroFloat(&half);
    setInt(&half.n, 500000000, 0);
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
    struct FLOAT x, xAfter, temp1, temp2, temp3, two, one,oneNear, oldDist, newDist;
    struct NUMBER temp;
    int sourceSign = getSignInt(&source->n);
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
            setSignInt(&to->n, -1);
            return 1;
        }
        return 0;
    }
    return 0;
}
/*
int numSqrt2(struct FLOAT *source, struct FLOAT *sqroot){
    struct FLOAT x, xAfter, half, three, one, oldDist, newDist,temp1 , temp2, temp3, eps;
    clearByZeroFloat(sqroot);
    //初期値
    setFloat(&x, 66 , -(source->exp / 3 + 1));
    setFloat(&eps, 9, -DIGIT + 1);
    setFloat(&half, 5, -1);
    setFloat(&three, 3, 0);
    setFloat(&one, 1, 0);
    dispNumberFloat(&x);puts("");
    //oldDist
    if(!power(&x, 2, &temp1))
        return 0;
    if(!multipleFloat(&temp1, source, &temp2))
        return 0;
    if(!subFloat(&temp2, &one, &temp3))
        return 0;
    getAbsFloat(&temp3, &oldDist);

    //ニュートンラフソン法
    while(1){
        if(!multipleFloat(&x, &half, &temp1))
            return 0;
        puts("1");
        if(!power(&x, 3, &temp2))
            return 0;
        puts("2");
        if(!multipleFloat(&temp2, source, &temp3))
            return 0;
        puts("3");
        if(!subFloat(&three, &temp3, &temp2))
            return 0;
        puts("4");
        if(!multipleFloat(&temp1, &temp2, &xAfter))
            return 0;
        dispNumberFloat(&xAfter);puts("");
        puts("5");
        
        //newDist
        if(!power(&xAfter, 2, &temp1))
            return 0;
        puts("6");
        if(!multipleFloat(&temp1, source, &temp2))
            return 0;
        puts("7");
        if(!subFloat(&temp2, &one, &temp3))
            return 0;
        puts("8");
        getAbsFloat(&temp3, &newDist);
        
        //収束条件
        if( numCompFloat(&oldDist, &newDist) <= 0 && numCompFloat(&newDist,&eps) <= 0)
            break;
        copyNumberFloat(&xAfter, &x);
        copyNumberFloat(&newDist, &oldDist);
        
    }
    if(!multipleFloat(&x, source, sqroot))
        return 0;
    return 1;
}
*/
