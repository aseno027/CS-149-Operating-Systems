#include <stdio.h>

int main(void) {
   int userNum;
   
   printf("Enter integer:\n");
   scanf("%d", &userNum);
   
   printf("You entered: %d\n", userNum);
   int userNumSquared = userNum * userNum;
   printf("%d squared is %d\n", userNum, userNumSquared);
   int userNumCubed = userNumSquared * userNum;
   printf("And %d cubed is %d!!\n", userNum, userNumCubed);
   
   int userNum2;
   printf("Enter another integer:\n");
   scanf("%d", &userNum2);
   printf("%d + %d is %d\n", userNum, userNum2, userNum + userNum2);
   printf("%d * %d is %d\n", userNum, userNum2, userNum * userNum2);
   
   return 0;
}
