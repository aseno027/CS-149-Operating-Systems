#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

typedef struct ItemToPurchase_struct {
   char itemName [100];
   int itemPrice;
   int itemQuantity;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase* itemToPurchase);
void PrintItemCost(ItemToPurchase itemToPurchase);

#endif
