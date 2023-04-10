#include <stdlib.h>
#include <stdio.h>

#include "ll.h"

// struct node
// {
// 	int val;
// 	struct node *next;
// };


struct node* add_two_num (struct node* l1, struct node* l2)
{
	struct node* l3 = (struct node*)malloc(sizeof(struct node));
	
	struct node* curr1 = l1;
	struct node* curr2 = l2;
	struct node* head;
	int check = 0;
	int carry = 0;

	while (curr1 != NULL || curr2 != NULL) {
		if (curr1 == l1 && curr2 == l2) {
			head = l3;
		}

    int val1 = (curr1 != NULL) ? curr1->val : 0;
    int val2 = (curr2 != NULL) ? curr2->val : 0;

		l3 -> val = val1 + val2 + carry;
    
		if (l3 -> val >= 10) {
			l3 -> val = l3 -> val - 10;
			carry = 1;
		}

    if(curr1 != NULL){
      curr1 = curr1 -> next;
    }
	  if(curr2 != NULL){
      curr2 = curr2 -> next;
    }	
	
    //check if NOT done (both are not null)
    if(curr1 != NULL || curr2 != NULL) {
      struct node* l4 = (struct node*)malloc(sizeof(struct node));
		  l3 -> next = l4;
		  l3 = l3 -> next;
    }
	}

  //after the loop ends, if there's a carry left, add it in
  if(carry == 1) {
    struct node* l5 = (struct node*)malloc(sizeof(struct node));
    l5->val = 1;
    l3 -> next = l5;
  }

	return head;
}


