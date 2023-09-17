#include <stdio.h>

double LapsToMiles(double userLaps){
   return (userLaps * 0.25);
}

int main(void) {

   double yourValue;
   scanf("%lf", &yourValue);
   yourValue = LapsToMiles(yourValue);
   printf("%0.2lf\n", yourValue);

   return 0;
}

