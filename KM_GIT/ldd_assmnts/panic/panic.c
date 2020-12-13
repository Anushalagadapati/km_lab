#include<linux/module.h>  
#include<linux/init.h> 
#include<linux/kernel.h> 
#include<linux/sched.h>
int *ptr=NULL;

static int panic_init(void) {
        printk("panic_init");
	printk("%d\n",*ptr); //creates kernel panic
        return 0;
}

static void panic_exit(void) {
   
	printk("panic_exit");
}

module_init(panic_init);
module_exit(panic_exit);

