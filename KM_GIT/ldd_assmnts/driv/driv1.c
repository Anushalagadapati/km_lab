#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>
#include"head.h"
int km1_open (int x);
int km1_read (int z);
//void fun_km2(void);
struct  file_ops km1 = {
        "KM1_Driver",
        .open = km1_open,
        .read = km1_read,
};
int km1_open (int x)
{
printk("open=%d",x);
}
int km1_read (int z)
{
printk("read=%d",z);
}
static int modparam_init (void)
{       struct  file_ops *fops=&km1;
        printk ("This is modparam init function driv1\n");
        fops->km1.open;
	fops->km1.read;
	//km1.read(5);
        return 0;
}

static void modparam_exit (void)
{
        printk ("This is modparam exit function driv1\n");
}
module_init(modparam_init);
module_exit(modparam_exit);

