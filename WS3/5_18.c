#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   int value;
   int count = 0;

   while (count < NUM_ELEMENTS) {
      scanf("%d", &value);
      if (value < 0) {
          break;
      }
      userValues[count] = value;
      count++;
   }

   if (count == NUM_ELEMENTS) {
       printf("Too many numbers\n");
   } else {
      int middleIndex = count / 2;
      printf("Middle item: %d\n", userValues[middleIndex]);
   }
   return 0;
}
