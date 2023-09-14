#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int numCount, threshold;

   scanf("%d", &numCount);

   for (int i = 0; i < numCount; i++) {
        scanf("%d", &userValues[i]);
   }

   scanf("%d", &threshold);
   for (int i = 0; i < numCount; i++) {
        if (userValues[i] <= threshold) {
            printf("%d", userValues[i]);
            printf(",");
            
        }
   }
   printf("\n");
   return 0;
}
