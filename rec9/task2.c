#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * return true (1) if n is happy, false (0) otherwise
 */
bool isHappy (int n){
	int map[300];

  //initialize map to all -1's
  for(int i=0; i < 300; i++){
    map[i] = -1;
  }

  while (1) {
    //check happy
    if (n == 1) {
      return 1;
    }

    //start probing: check for empty or found value
    int hash = n % 300;
    int found = 0;
    //printf("hash = %d, n = %d, map[hash] = %d\n", hash, n, map[hash]);
    while (map[hash] >= 0) {
      if (map[hash] == n) {
        found = 1;
        break;
      }
      hash++;
    }

    //this means we have looped, not happy
    if (found) {
      return 0;
    }

    //insert into map
    map[hash] = n;

    //progress n onto the next iteration
    int sumOfSquares = 0;
    int num = n;
    while (num > 0) {
      int digit = num % 10;
      sumOfSquares += digit * digit;
      num /= 10;
    }
    n = sumOfSquares;
  }
  
	return 0;
}

// 2 -> 4 -> 16 -> 1 + 36 = 37 -> 9 + 49 -> 58 -> 25 + 64 = 89 -> 64 + 81 = 145
//-> 1 + 16 + 25 = 42 -> 16 + 4 = 20 -> 4


/*
 * Below are testing functions... DO NOT MODIFY!!!
 */

void show_result(int e, int r){
	printf("Expected: %d\nActual: %d...", e, r);
	if (r != e) 
        printf("FAIL\n\n\n");
    else 
        printf("OK\n\n\n");
}



int main()
{
	printf("\nTEST 1...19\n");
	show_result(1, isHappy(19));

	printf("\nTEST 2...2\n");
	show_result(0, isHappy(2));

	printf("\nTEST 3...7\n");
	show_result(1, isHappy(7));

	printf("\nTEST 4...176\n");
	show_result(1, isHappy(176));

	printf("\nTEST 5...36\n");
	show_result(0, isHappy(36));

	

	return 0;
}
