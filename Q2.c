/* CS261- Recitation 1 - Q.2
 * Solution description: call the function foo using "reference" to see the values before and after the function
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = 2 *  *a;
    /*Set b to half its original value*/
	*b = *b/2;
    /*Assign a+b to c*/
	c = *a + *b;
    /*Return c*/
	return c;
    return 0;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 7, 8, 9 respectively*/
 	int x = 7;
     	int y = 8;
	int z = 9;	
    /*Print the values of x, y and z*/
	printf("%d\n" , x);
	printf("%d\n" , y);
	printf("%d\n" , z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
	

	printf("%d\n", foo(&x,&y,z));
    /*Print the value returned by foo*/
	printf("%d\n", x);
	printf("%d\n", y);
	printf("%d\n", z);
    /*Print the values of x, y and z again*/
	
    /*Is the return value different than the value of z?  Why? */
    return 0;
}
    
    
