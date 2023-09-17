#include <stdio.h>

int main(void)
{
   const int MAX_ELEMENTS = 20;
   int userValues[MAX_ELEMENTS];
   int numCount;

   scanf("%d", &numCount);

   for (int i = 0; i < numCount; i++)
   {
      scanf("%d", &userValues[i]);
   }

   int smallest = userValues[0];
   int secondSmallest = userValues[1];

   for (int i = 1; i < numCount; i++)
   {
      if (userValues[i] < smallest)
      {
         secondSmallest = smallest;
         smallest = userValues[i];
      }
      else if (userValues[i] < secondSmallest)
      {
         secondSmallest = userValues[i];
      }
   }

   printf("%d and %d\n", smallest, secondSmallest);

   return 0;
}
