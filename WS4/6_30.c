#include <stdio.h>

int MaxNumber(int num1, int num2, int num3, int num4){
   int max = num1;
   if(max < num2){
      max = num2;
   }
   if(max < num3){
      max = num3;
   }
   if(max < num4){
      max = num4;
   }
   return max;
}

int MinNumber(int num1, int num2, int num3, int num4){
   int min = num1;
   if(min > num2){
      min = num2;
   }
   if(min > num3){
      min = num3;
   }
   if(min > num4){
      min = num4;
   }
   return min;
}


int main(void) {
   int num1;
   int num2;
   int num3;
   int num4;
   int max;
   int min;
   scanf("%d%d%d%d", &num1, &num2, &num3, &num4);
   max = MaxNumber(num1, num2, num3, num4);
   min = MinNumber(num1, num2, num3, num4);
   printf("Maximum is %d\n", max);
   printf("Minimum is %d\n", min);
   return 0;
}

