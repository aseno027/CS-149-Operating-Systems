#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers

   int numCount;

   scanf("%d", &numCount);

   for (int i = 0; i < numCount; i++) {
      scanf("%d", &userVals[i]);
   }

   for (int i = numCount - 1; i >= 0; i--) {
      printf("%d", userVals[i]);


      printf(",");

   }
   printf("\n");

   return 0;
}
