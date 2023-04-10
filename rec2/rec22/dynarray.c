/* CS261 - Reciation 2*/
/* Description: create a array of integers and struct student by giving the size of array, 
                and sort them using sort() and function pointers
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

struct student{
	int id;
	int score;
};

//helper function to compare students by their scores
int compare_student (void* x, void* y){
	struct student *s1 = x;
	struct student *s2 = y;
	return s1->score > s2->score ? 1 : 0;
}

//helper function to compare two ints
int compare_int (void* x, void* y){
	int* a = x, *b = y;
	return *a > *b ? 1 : 0;
}

/* sort the arr array by using a function pointer to 
 * compare its elements
 * Param: 
 *		void** arr                 - array of generic type 
 *      int n                      - array size
 *      int(*cmp)(void* a, void* b)- function pointer to compare two elements in the array 
 */
//void sort(void** arr, int n, int(*cmp)(void* a, void* b))
void sort(int* arr, int n){
    /*Sort n integers in arr, ascending order*/
	/*
	 * FIXED ME:
	 */
	 
}


/* free the memeory allocated by arr
 * Param: 
 *      void** arr                 - array of generic type 
 *      int n                      - array size
 */
void free_arr (void** arr, int n){
	/* free the memory allocated by arr*/
	/*
	 * FIXED ME:
	 */
}

int main(){
    srand(time(NULL));

    /*Declare an integer n and assign 10 to it.*/

    /***Step 1: sort an integer array ***/
    
    /*Allocate memory for n integers using malloc.*/
    
    /*Generate random ints (0-100, inclusive) for the n integers, using rand().*/

    /*Print the contents of the array of n students.*/
    printf("\nBefore sorting....\n");
    
    /*call sort() function to sort*/

    /*Print the contents of the array of n students.*/
    printf("\nAfter sorting....\n");
    



    /***Step 2: After modifying sort() by using function pointer, modify your sort() function call above ****/




    /***Step 3: sort an array of students ***/

    /*Allocate memory for n students using malloc.*/
    
    /*Generate random IDs and scores for the n students, using rand().*/
    /*note: 
     *    1. no two students should have the same ids 
     *    2. score and id range: 0-100, inclusive
     */
    

    /*Print the contents of the array of n students.*/
    printf("\nBefore sorting....\n");

    /*call sort() function to sort*/
    
    /*Print the contents of the array of n students.*/
    printf("\nAfter sorting....\n");
    

    

    /***Step 4: free the memory allocated in Step 1-3 by calling free_arr() ***/
    

    return 0;
}
