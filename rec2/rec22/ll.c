#include <stdlib.h>

#include "ll.h"

// struct node
// {
// 	int val;
// 	struct node *next;
// };


struct node* add_two_num (struct node* l1, struct node* l2)
{

	//struct node* l3 = (struct node*)malloc(sizeof(struct node));
	struct node* curr1 = l1;
	struct node* curr2 = l2;
	int check = 0;
	int carry = 0;
	struct node* head3; 

   	while (curr1 != NULL || curr2 != NULL) {
	   struct node* l3 = (struct node*)malloc(sizeof(struct node));

		
		if (curr1 == l1 && curr2 = l2) { 
	       		head3 = l3;
			}
		
		l3 -> val = curr1 -> val + curr2 -> val + carry;
		//check = curr1 -> val + curr2 -> val;
		


		if (l3 -> val >= 10) {
		   l3 -> val = l3 -> val - 10;	   
		   carry = 1;
		 


		}	
		if(carry == 1) {
		   carry = 0
		     }

		
		   curr1 = curr1 -> next;
		   curr2 = curr2 -> next;


	




	return struct node* l3;
}


