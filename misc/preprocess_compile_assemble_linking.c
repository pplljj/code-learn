#include<stdio.h>

/*

#first step: pre processing (process the macro mainly)
gcc -E test.c -o test.i
#second step: compiling (turn the *.i to the assembling file *.s)
gcc -S test.i -o test.s
#third step: assembling (turn the *.s to the binary object *.o)
gcc -c test.s -o test.o
#fourth setp: linking (get the final program)
gcc test.o -o test

*/

int main()
{
  printf("this is a test.\n");
  return 0;
}
