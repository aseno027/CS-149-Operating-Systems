#include <stdio.h>

int main(void)
{

   const int MAX_ELEMENTS = 20;
   int userValues[MAX_ELEMENTS]; 
   int numCount, lowerBound, upperBound;

   scanf("%d", &numCount);

   for (int i = 0; i < numCount; i++)
   {
      scanf("%d", &userValues[i]);
   }

   scanf("%d %d", &lowerBound, &upperBound);

   for (int i = 0; i < numCount; i++)
   {
      if (userValues[i] >= lowerBound && userValues[i] <= upperBound)
      {
         printf("%d", userValues[i]);
            printf(",");
      }
   }

   printf("\n");
   return 0;
}
