#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "queue.h"
#include "stack.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome (quit after):\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));

  while (get_user_str(in, MAX_STR_LEN)) {
    /*
     * Inside this loop body, you'll have an input string from the user in `in`.
     * You should use your stack and your queue to test whether that string is
     * a palindrome (i.e. a string that reads the same backward as forward, e.g.
     * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
     * print a message letting the user know whether or not their string is
     * is a palindrome.
     *
     * When you test whether the user's string is a palindrome, you should
     * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
     * etc.), and you should ignore the case of letters (e.g. the characters
     * 'a' and 'A' should be considered as equal).  The C functions isalpha()
     * and tolower() from ctype.h might help with this.
     */

     //create a stack and a queue
     struct queue* q1 = queue_create();
     struct stack* s1 = stack_create();

     for(int i = 0; i < strlen(in); i++) {
       //skips non-letter characters
       if(!isalpha(in[i])) continue;

       char lower2 = tolower(in[i]);

       //push that character onto both stack and queue
       queue_enqueue(q1, (void*) lower2);
       stack_push(s1, (void*) lower2);

    }

    int is_palindrome = 1;

    //pop off from both simultaneously until one (or both) is empty
    while(!queue_isempty(q1) || !stack_isempty(s1)) {
      void* val = queue_dequeue(q1);
      void* val2 = stack_pop(s1);

      char ch1 = (char) val;
      char ch2 = (char) val2;
      
      if(ch1 != ch2) {
        printf("\nNot a Palindrome\n");
        is_palindrome = 0;
        break;
      }
    }

    if (is_palindrome) {
      printf("\nPalindrome\n");
    }
    
    //free stack and queue
    queue_free(q1);
    stack_free(s1);
    break;


  }

  free(in);
  return 0;
}
