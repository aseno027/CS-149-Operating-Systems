#include <stdio.h>
#include <string.h>

int main(void) {
   
   char userStr[51];
   
   do {
      fgets(userStr, sizeof(userStr), stdin);
      
      // Remove the newline character at the end of the input
      if (userStr[strlen(userStr) - 1] == '\n') {
            userStr[strlen(userStr) - 1] = '\0';
      }
      
      // Check user input
      if(strcmp(userStr, "done") == 0 || strcmp(userStr, "Done") == 0 || strcmp(userStr, "d") == 0){
         break; // Exit loop
      }
      
      // Reverse and print the input
      for (int i = strlen(userStr) - 1; i >= 0; i--) {
         printf("%c", userStr[i]);
      }
      printf("\n");  
      
   } while(1);
   
   return 0;
}
