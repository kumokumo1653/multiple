#include <stdio.h>
#include <string.h>
//円周率のための文字列一致プログラム。
//1つ目を導出した円周率、2つ目を理論値の円周率
int main(int argc, char *argv[]){
   int i, flag, digit,cnt;
   cnt = 0;
   flag = 1;
 
   if(argc != 3){
      printf("引数:確認する円周率 理論の円周率");
      return -1;
   }
   if(strlen(argv[1]) > strlen(argv[2])){
      printf("理論値の円周率の桁が少ないです。");
      return -1;
   }
   digit = strlen(argv[1]);
   for(i = 0; i < digit; i++){
      if(argv[1][i] != argv[2][i]){
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