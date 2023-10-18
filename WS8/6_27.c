/**
 * Description: This C program get an input character and a string, and whose output indicates the number of times the character appears in the string. 
 * Author names: Abel Seno & Amirali Marsahifar
 * Author emails: abel.seno@sjsu.edu & amirali.marashifar@sjsu.edu
 * Last modified date: 10/18/2023
 * Creation date: 10/18/2023 
 **/

#include <stdio.h>
#include <string.h>

// Function to calculate the number of occurrences of a character in a string
int CalcNumCharacters(char* userString, char userChar) {
   int count = 0;
   
   // Loop through the string character by character
   for (int i = 0; i < strlen(userString); i++) {
      // If the current character matches the userChar, increment the count
      if (userChar == userString[i]) {
         count++;
      }
   }
   return count;
}

int main(void) {
   char userChar;
   char userString[50];
   
   // Prompt the user to enter a character and read it
   scanf("%c", &userChar);
   
   // Read a string from the user, with a maximum length of 49 characters (including null terminator)
   fgets(userString, sizeof(userString), stdin);
   
   // Call the function to calculate the number of occurrences of userChar in userString
   int result = CalcNumCharacters(userString, userChar);
   
   // Output the result with appropriate pluralization
   if (result == 1) {
       printf("%d %c\n",  result, userChar);
   } else {
      printf("%d %c's\n",  result, userChar);
   }

   return 0;
}
