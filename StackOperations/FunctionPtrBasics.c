#include <stdio.h>

typedef int (*Operation)(int a , int b ) ; 

typedef  struct _str {

       int  result ; 
       Operation  opt; // funtion pointer 

 } obj;
 
int Add ( int a , int b ){
     
      return a+b ;
}

int Multi ( int a , int b ){

       return a*b ;
}

int main (){

      obj str_obj;

      str_obj.opt = Add;//the function pointer variable point to Add function 

      str_obj. result = str_obj.opt(5,3);

      printf ("%d\n", str_obj.result );

      str_obj.opt= Multi;//the function pointer variable point to Multi function 

      str_obj. result = str_obj.opt(5,3);

      printf ("%d\n", str_obj.result );

      return 0 ;

}
