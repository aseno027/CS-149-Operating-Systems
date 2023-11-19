#include <stdio.h>
#include <string.h>

typedef struct ContactNode_struct {
   char contactName[50];
   char contactPhoneNumber[50];
   struct ContactNode_struct* nextNodePtr;
} ContactNode;


/* Define the functions here. */
void InitializeContactNode(ContactNode* thisNode, char name[], char phoneNumber[]) {
   strcpy(thisNode->contactName, name);
   strcpy(thisNode->contactPhoneNumber, phoneNumber);
   thisNode->nextNodePtr = NULL;
}

char* GetName(ContactNode* thisNode) {
   return thisNode->contactName;
}

char* GetPhoneNumber(ContactNode* thisNode) {
   return thisNode->contactPhoneNumber;
}

void InsertAfter(ContactNode* thisNode, ContactNode* newNode) {
   ContactNode* temp = thisNode->nextNodePtr;
   thisNode->nextNodePtr = newNode;
   newNode->nextNodePtr = temp;
}
ContactNode* GetNext(ContactNode* thisNode) {
   return thisNode->nextNodePtr;
}
void PrintContactNode(ContactNode* thisNode) {
   printf("Name: %s\n", thisNode->contactName);
   printf("Phone number: %s\n", thisNode->contactPhoneNumber);
}





int main(void) {
   ContactNode contact1, contact2, contact3;
   char name[50];
   char phoneNumber[50];

   fgets(name, 50, stdin);
   strtok(name, "\n"); // Remove newline character
   fgets(phoneNumber, 50, stdin);
   strtok(phoneNumber, "\n");
   InitializeContactNode(&contact1, name, phoneNumber);

   fgets(name, 50, stdin);
   strtok(name, "\n");
   fgets(phoneNumber, 50, stdin);
   strtok(phoneNumber, "\n");
   InitializeContactNode(&contact2, name, phoneNumber);

   fgets(name, 50, stdin);
   strtok(name, "\n");
   fgets(phoneNumber, 50, stdin);
   strtok(phoneNumber, "\n");
   InitializeContactNode(&contact3, name, phoneNumber);

   InsertAfter(&contact1, &contact2);
   InsertAfter(&contact2, &contact3);

   
   ContactNode* current = &contact1;
   int personCounter = 1;
   while (current != NULL) {
      printf("Person %d: %s, %s\n", personCounter++, GetName(current), GetPhoneNumber(current));
      current = GetNext(current);
   }

   printf("\nCONTACT LIST\n");
   current = &contact1;
   while (current != NULL) {
      PrintContactNode(current);
      printf("\n");
      current = GetNext(current);
   }

   return 0;
}