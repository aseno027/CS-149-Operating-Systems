#include <stdio.h>
#include <math.h>

int main(void) {
   double x;
   double y;
   double z;

   scanf("%lf %lf %lf", &x, &y, &z);
   
   double output1 = pow(x, z);
   double output2 = pow(x, pow(y, 2));
   double output3 = fabs(y);
   double output4 = sqrt(pow(x * y, z));
   
   printf("%0.2lf %0.2lf %0.2lf %0.2lf\n", output1, output2, output3, output4);

   return 0;
}

