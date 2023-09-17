#include <stdio.h>
#include <string.h>

int main(void) {
   char searchCharacter;
   int numWords;
   scanf("%d" , &numWords);
   
   char userWords[20][10];
   for (int i = 0; i < numWords; ++i){
      scanf("%s", userWords[i]);
   }
   scanf(" %c", &searchCharacter);
   for (int i = 0; i < numWords; ++i){
      if (strchr(userWords[i], searchCharacter) != NULL){
         printf("%s,", userWords[i]);
      }
   }
   printf("\n");
   

   return 0;
}

