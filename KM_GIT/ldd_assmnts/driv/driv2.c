#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>
#include"head.h"
int km2_open (int x);
int km2_read (int z);
//void fun_km2(void);
struct  file_ops km2 = {
        "KM2_Driver",
        .open = km2_open,
        .read = km2_read,
};
int km2_open (int x)
{
printk("open=%d",x);
}
int km2_read (int z)
{
printk("read=%d",z);
}
static int modparam_init (void)
{
	struct  file_ops *fop1=&km2;
        printk ("This is modparam init function driv2\n");
        fop1->open(6);
        fop1->read(7);
        return 0;

}


static void modparam_exit (void)
{
        printk ("This is modparam exit function drive2\n");
}
module_init(modparam_init);
module_exit(modparam_exit);



