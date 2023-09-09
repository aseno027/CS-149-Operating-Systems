#include <stdio.h>

int main(void) {

   int userNum;
   int divNum;
   
   scanf("%d %d", &userNum, &divNum);
   userNum /= divNum;
   printf("%d ", userNum);
   userNum /= divNum;
   printf("%d ", userNum);
   userNum /= divNum;
   printf("%d\n", userNum);
   
   return 0;
}

