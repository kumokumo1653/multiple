#include <stdio.h>
#include <string.h>
//円周率のための文字列一致プログラム。
//1つ目を導出した円周率、2つ目を理論値の円周率
int main(int argc, char *argv[]){
   int i, flag, digit,cnt;
   cnt = 0;
   flag = 1;
   char a[15000], b[15000];
   
   scanf("%s",a);
   scanf("%s",b);
   if(strlen(a) > strlen(b)){
      printf("理論値の円周率の桁が少ないです。");
      return -1;
   }
   digit = strlen(a);
   for(i = 0; i < digit; i++){
      if(a[i] != b[i]){
         flag = 0;
         break;
      }
      cnt++;
   }
   if(flag)
      printf("完全一致。小数点以下%d桁まで\n", cnt - 2);
   else
      printf("部分一致。小数点以下%d桁まで\n", cnt - 2);
   return 0;
}