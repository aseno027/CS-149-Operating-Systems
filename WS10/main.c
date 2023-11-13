#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {
   // Create two objects of the ItemToPurchase struct
   ItemToPurchase item1, item2;

   // Prompt user for the first item
   printf("Item 1\n");
   printf("Enter the item name:\n");
    
   // Use fgets to get the entire line, including spaces
   fgets(item1.itemName, sizeof(item1.itemName), stdin);
   item1.itemName[strcspn(item1.itemName, "\n")] = '\0'; // Remove the trailing newline

   // Set the values for the first item
   printf("Enter the item price:\n");
   scanf("%d", &item1.itemPrice);

   printf("Enter the item quantity:\n");
   scanf("%d", &item1.itemQuantity);

   // Clear the input buffer
   char c = getchar();
   while(c != '\n' && c != EOF) {
      c = getchar();
   }

   // Prompt user for the second item
   printf("\nItem 2\n");
   printf("Enter the item name:\n");

   // Use fgets again for the second item
   fgets(item2.itemName, sizeof(item2.itemName), stdin);
   item2.itemName[strcspn(item2.itemName, "\n")] = '\0'; // Remove the trailing newline

   // Set the values for the second item
   printf("Enter the item price:\n");
   scanf("%d", &item2.itemPrice);

   printf("Enter the item quantity:\n");
   scanf("%d", &item2.itemQuantity);

   // Output the total cost
   printf("\nTOTAL COST\n");
   PrintItemCost(item1);
   PrintItemCost(item2);

   // Calculate and print the total cost
   int totalCost = (item1.itemPrice * item1.itemQuantity) + (item2.itemPrice * item2.itemQuantity);
   printf("\nTotal: $%d\n", totalCost);

   return 0;
}
