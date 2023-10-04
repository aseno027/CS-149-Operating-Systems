#include <stdio.h>
#include <stdbool.h>

bool IsArrayMult10(int inputVals[], int numVals) {
   for(int i = 0; i < numVals; i++) {
      if(inputVals[i] % 10 != 0) {
         return false;
      }
   }
   return true;
}

bool IsArrayNoMult10(int inputVals[], int numVals) {
   for(int i = 0; i < numVals; i++) {
      if(inputVals[i] % 10 == 0) {
         return false;
      }
   }
   return true;
}

int main(void) {

   int numVals;
   scanf("%d", &numVals);

   int inputVals[20];
   for (int i = 0; i < numVals; i++) {
      scanf("%d", &inputVals[i]);
   }

   if (IsArrayMult10(inputVals, numVals)) {
      printf("all multiples of 10\n");
   } else if (IsArrayNoMult10(inputVals, numVals)) {
      printf("no multiples of 10\n");
   } else {
      printf("mixed values\n");
   }
   
   return 0;
}

