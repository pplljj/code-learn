#include<stdio.h>
#include<iostream>

// min(4, size of member type)

typedef struct {
   char a;    //offset: 0, a:o
   short b;   //offset: min(4,2)=2, so b's offset is beishu of 2, so a:o#, b:oo
   char c;    //offset: min(4,1)=1, so c's offset is beishu of 1, so c:o
   double d;  //offset: min(4,8)=4, so d's offset is beishu of 4, so c: o### d:oooo oooo
              //so total is o#oo o### oooo oooo, 16

  //add v1
  void func();//do not occupy space
  int func1(int, float); //do not occupy space

  virtual void funcv();//virtual func table, size are equal to pointer, is 8
  virtual int funcv1(int, int);//all virtual func occupy one piece of space
} sss;  //24


typedef struct {
 long a1;   //8   offset: 0
 short a2;  //offset: min(4,2)=2, 8 is beishu of 2, so just fill 6 bytes
}A; //16

typedef struct {
  short a1;
  short a2;
  short a3;
}B; //6


typedef struct {
  float a;
  double b;
  int c;
  char d;// last one's fill bytes num is decided by max(4, size1, size2, size3,...) (sizei is element i 's size)
}C; //24

class base{
  public:
   base() {}
   ~base() {}
}; // 1

class drived1: public virtual base{
}; //virtual jicheng has a hidden virtual table

int main()
{
  printf("_________Benchmark__________\n");
  printf("int    size: %ld\n",sizeof(int));
  printf("short  size: %ld\n",sizeof(short));
  printf("double size: %ld\n",sizeof(double));
  printf("float  size: %ld\n",sizeof(float));
  printf("long   size: %ld\n",sizeof(long));
  printf("void*  size: %ld\n",sizeof(void*));
  printf("____________________________\n");
  printf("struct size: %ld\n",sizeof(drived1));
  return 0;
}
