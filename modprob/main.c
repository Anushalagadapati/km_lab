#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
int x=10,y=20;
module_param(x,int,0);
module_param(y,int,0);
static int add_init(void)
{
printk("add_init %d,%d",x,y);
}
static void add_exit(void)
{
printk("add_exit");
}
module_init(add_init);
module_exit(add_exit);

