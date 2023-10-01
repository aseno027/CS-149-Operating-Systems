#include <stdio.h>
#include <stdbool.h>

bool IsArrayMult10(int inputVals[], int numVals) {
   for(int i = 1; i <= numVals; i++) {
      if(inputVals[i] % 10 != 0) {
         return false;
      }
   }
   return true;
}

bool IsArrayNoMult10(int inputVals[], int numVals) {
   for(int i = 1; i <= numVals; i++) {
      if(inputVals[i] % 10 == 0) {
         return false;
      }
   }
   return true;
}

int main(void) {

   int inputVals[20];
   scanf("%d", &inputVals[0]);
   
   for(int i = 1; i <= inputVals[0]; i++) {
      scanf("%d", &inputVals[i]);
   }
   
   if (IsArrayMult10(inputVals, inputVals[0])) {
      printf("all multiples of 10");
   } else if (IsArrayNoMult10(inputVals, inputVals[0])) {
      printf("no multiples of 10");
   } else {
      printf("mixed values");
   }
   printf("\n");
   
   return 0;
}
