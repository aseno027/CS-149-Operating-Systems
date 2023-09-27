#include <stdio.h>
#include <string.h>
#include <ctype.h>

void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]){
   if (userString[strlen(userString) - 1] == '\n') {
      userString[strlen(userString)-1] = '\0';
   }
   int i;
   int j = 0;
   for(i = 0; i < strlen(userString); ++i){
      if(isalpha(userString[i])){
         userStringAlphaOnly[j] = userString[i];
         ++j;
      }
   }
   userStringAlphaOnly[j] = '\0';
   printf("%s\n", userStringAlphaOnly);
}

int main(void) {
   char userString[50];
   char userStringAlphaOnly[50];
   
   fgets(userString, 50, stdin);

   RemoveNonAlpha(userString, userStringAlphaOnly);

   return 0;
}
