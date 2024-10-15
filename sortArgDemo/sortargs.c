#include "bst.h"
  
int main(int argc, char **argv)	/* prints arguments in order */
{
  //  printf("Please enter your string\n");
  // int c;
  // printf("> ");
  //while((c = getchar()) != '\n'){
  //  putchar(c);
  // }
  // printf("\n");
  printf("the program name is <%s>\n", *(argv+0));
  for (char **p = &argv[1]; *p; p++)
    bstInsert(&bstRoot, *p);
  bstPrint(bstRoot);
  bstClear(&bstRoot);
}
