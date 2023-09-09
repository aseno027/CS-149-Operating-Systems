#include <stdio.h>

int main(void) {

   int x;
   int y;
   int z;
   int smallest;
   
   scanf("%d %d %d", &x, &y, &z);
   
   if(x <= y && x <= z){
      smallest = x;
   }else if(y <= x && y <= z){
      smallest = y;
   }else{
      smallest = z;
   }
   
   printf("%d\n", smallest);
   
   return 0;
}

