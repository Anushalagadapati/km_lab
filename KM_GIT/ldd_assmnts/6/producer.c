//**************** PRODUCER ***************
#include<stdio.h>
#include "struct.h"
stu percentage(stu );
main()
{
  
   printf("**** WELCOME TO PRODUCER ****\n");
   stu s1={"KPSR"};
   printf("Enter 6 subjects marks \n");
   int i;
    for(i=0;i<6;i++)
     {
        scanf("%f",&s1.marks[i]);
     }
   s1=percentage(s1);
}
