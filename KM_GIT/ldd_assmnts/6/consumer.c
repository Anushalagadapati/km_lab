//************** CONSUMER ************
#include<stdio.h>
#include "struct.h"
stu percentage(stu s1)
 {
   printf("**** WELCOME TO CONSUMER ****\n");
    int i;
    float total;
    for(i=0;i<6;i++)
     {
       total+=s1.marks[i];
     }
   s1.per=total/6;
   //return s1;
   printf("student name : %s\npercentage  : %f\n", s1.name,s1.per);
 }
