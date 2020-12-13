#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
static int add_init(void)
{
printk("add_init");
}
static void add_exit(void)
{
printk("add_exit");
}
module_init(add_init);
module_exit(add_exit);
