#include <stdio.h>
#include <string.h>

int main(void) {

   char userStr[50];
   
   fgets(userStr, 50, stdin);
   
   if (userStr[strlen(userStr) - 1] == '\n') {
      userStr[strlen(userStr)-1] = '\0';
   }
   int i;
   int count = 0;
   for(i = 0; i < strlen(userStr); ++i){
      if(userStr[i] != ' ' && userStr[i] != '.' && userStr[i] != '!' && userStr[i] != ','){
        count++;
      }
   }
   printf("%d\n", count);
   
   return 0;
}
