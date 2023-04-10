/* CS261- Recitation 1 - Q. 1*
 * Grant Lance
 * Solution description: check the properties, like value and address, of pointer
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
    printf("%d\n" ,*iptr); 
     /*Print the address pointed to by iptr*/
    printf("%p\n", iptr );
     /*Print the address of iptr itself*/
    printf("%p\n", &iptr);
}

int main(){
    
    /*declare an integer x and initialize it with 0*/
    int x = 0;
    /*print the address of x*/
    printf("%p\n", x); 
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("%d\n", x);

    return 0;
}
