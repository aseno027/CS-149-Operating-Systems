#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

void MakeItemBlank(ItemToPurchase* itemToPurchase) {
   strcpy((*itemToPurchase).itemName, "none");
   (*itemToPurchase).itemPrice = 0;
   (*itemToPurchase).itemQuantity = 0;
}
void PrintItemCost(ItemToPurchase itemToPurchase) {
   int cost = itemToPurchase.itemPrice * itemToPurchase.itemQuantity;
   printf("%s %d @ $%d = $%d\n", itemToPurchase.itemName, itemToPurchase.itemQuantity, itemToPurchase.itemPrice, cost);
}
