#include <stdio.h>

int main(void) {
   int num;
   int sum = 0;
   int count = 0;
   int max = -1; 

   while (1) {
      scanf("%d", &num);

        if (num < 0) {
            break;  
        }

        if (num > max) {
            max = num;
        }

        sum += num;
        count++;
    }

    if (count > 0) {
        double average = (double)sum / count;
        printf("%d %.2lf\n", max, average);
    }

    return 0;
}
