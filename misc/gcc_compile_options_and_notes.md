#gcc g++ have lots of common parameters, we use gcc as example

#gcc process parameters:
-E   #only pre processing
-S   #only pre processing, compiling
-c   #only pre processing, compiling, assembling
-o   #output files: *.i(pre processing), *.s(compiling) , *.o(assembling), executable file(linking)
#if no (-E -S -c), then pre processing, compiling, assembling, linking are all done 

#gcc warning parameters:
-w      #do not display warning
-W      #dispaly the warning that the compiler think important
-Wall   #dispaly all warnings
#if using no above parameter, gcc prefers to act liking with -W
#there is no '-wall' parameter!!!
#advice: always use -W and -Wall together

#gcc macro parameters:
-DK43SD   #add a macro K43SD for code
-D K43SD  #same as above one

#gcc default include dir:
/usr/include
/usr/local/include

#gcc default library dir:
/lib
/usr/lib
/usr/local/lib

#gcc include parameters:
-I /home/penglijiang/user/cc/paramtest   #find include files in /home/penglijiang/user/cc/paramtest and default locations
-I/home/penglijiang/user/cc/paramtest    #same as above
-I.                                      #find include files in the pwd of the *.c
-I .                                     #same as above
-Iinc                                    #find include files in the inc folder of the *.c's dir
-I inc                                   #same as above

#gcc library parameters:
-Lpath              #find library in path
-L path             #same as above
-lzoo               #add the libzoo.so, zoo represents a lib name

#gcc build *.so
#zoo.h are bellow
#***********************#
#include<stdio.h>

void bird();
void pig();
void cat();
void dog();
#***********************#
#zoo.c are bellow
#***********************#
#include"zoo.h"

void bird()
{
  printf("bird bird bird bird bird\n");
}

void pig()
{
  printf("pig pig pig pig pig\n");
}

void cat()
{
  printf("cat cat cat cat cat\n");
}

void dog()
{
  printf("dog dog dog dog dog\n");
}

#**********************#
-fPIC     #Position Independent Code
-shared   #build shared object
#build libzoo.so
gcc -shared -fPIC zoo.c -o libzoo.so -I .
#build executable file test.c
#test.c
#*********************************#
#include<stdio.h>
#include"zoo.h"
#define K43SD

int main()
{
#ifdef K43SD
  bird();
  pig();
#else
  cat();
  dog();
#endif
  return 0;
}

#*********************************#
gcc -Wall -o test test.c -I . -L . -lzoo
#because the libzoo.so is not added to the default lib dir
#so before run ./test
export LD_LIBRARY_PATH=.

#gcc build *.a
#first generate *.o
gcc -c -Wall -o zoo.o zoo.c -I .
#the use ar to build *.a
ar -rcs libzoo.a zoo.o
#compile test.c
gcc -Wall -o test test.c -I . -L . -l:libzoo.a
#or
gcc -Wall -static -o test test.c -I . -L . -lzoo
#then run ./test


#if the .a files are nested one by one, there should be a order
#for eg.

*******************mymath.h******************
#include<stdio.h>

int iji_add(int a, int b);

int iji_sub(int a, int b);

int iji_mul(int a, int b);

int iji_div(int a, int b);

*******************mymath.c*****************
#include "mymath.h"

int iji_add(int a, int b) {
  return a+b;
}

int iji_sub(int a, int b) {
  return a-b;
}

int iji_mul(int a, int b) {
  return a*b;
}

int iji_div(int a, int b) {
  return a / ( b==0 ? 1 : b);
}
*****************************************
gcc -c -o mymath.o -Wall mymath.c -I .
ar -rcs libmymath.a mymath.o
****************************************

*****************complex.h**************
#include"mymath.h"

int iji_oula(int a, int b, int c, int d);

int iji_laibuliz(int a, int b, int c, int d);

*****************complex.c***************
#include "complex.h"

int iji_oula(int a, int b, int c, int d) {
    return iji_add(a,b) + iji_mul(c,d) + iji_div(b, c);
}


int iji_laibuliz(int a, int b, int c, int d) {
    return iji_sub(iji_div(a,c), iji_add(b,d));
}
*******************************************
gcc -Wall -c -o complex.o complex.c -I. -L. -lmymath
ar -rcs libcomplex.a complex.o
*********************************************

*****************main.c**********************
#include "complex.h"

int main() {
  printf("result is %d\n", iji_oula(1,2,3,4));
  return 0;
}
*********************************************
gcc -Wall -o main main.c -I. -L. -lcomplex -lmymath #get right answer, noted that mymath is put at last order


gcc -Wall -o main main.c -I. -L. -lmymath -lcomplex #wrong, message are followed
./libcomplex.a(complex.o): In function `iji_oula':
complex.c:(.text+0x20): undefined reference to `iji_add'
complex.c:(.text+0x31): undefined reference to `iji_mul'
complex.c:(.text+0x42): undefined reference to `iji_div'
./libcomplex.a(complex.o): In function `iji_laibuliz':
complex.c:(.text+0x6f): undefined reference to `iji_add'
complex.c:(.text+0x80): undefined reference to `iji_div'
complex.c:(.text+0x89): undefined reference to `iji_sub'
collect2: error: ld returned 1 exit status

gcc -Wall -I. -L. -lmymath -lcomplex -o main main.c #wrong, message are followed
/tmp/ccg1ekXg.o: In function `main':
main.c:(.text+0x19): undefined reference to `iji_oula'
collect2: error: ld returned 1 exit status

gcc -Wall -I. -L. -lcomplex -lmymath -o main main.c #wrong, message are followed
/tmp/cc2K7qV8.o: In function `main':
main.c:(.text+0x19): undefined reference to `iji_oula'
collect2: error: ld returned 1 exit status

#we can get a simple conclusion: the exe we should put the most basic .a file in the last
#we can thought like this: main.c first need function in libcomplex.a, then libcomplex.a need the function in libmymath.a

~
