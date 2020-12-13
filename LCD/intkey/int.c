#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<asm/atomic.h>
#include<linux/wait.h>
#include<linux/sched.h>
#include<linux/interrupt.h>
static atomic_t data =ATOMIC_INIT(0);
DECLARE_WAIT_QUEUE_HEAD(wq);
int id,rv;
char buff;

int my_open(struct inode *, struct file *);
ssize_t my_read (struct file *, char __user *, size_t, loff_t *);
ssize_t my_write (struct file *, const char __user *, size_t, loff_t *);
int my_close(struct inode *, struct file *);

struct file_operations fiop={
	.open=my_open,
	.read=my_read,
	.write=my_write,
	.release=my_close,
};
irqreturn_t handler(int irq,void *id)
{
        //char buff;
	buff=inb(0X60);

	printk("inside the handler buff = %x\n",buff);
	if(buff<0xffffff80)
	{

		atomic_set(&data,1);
		wake_up_interruptible(&wq);
		return IRQ_HANDLED;
	}
}
int my_open (struct inode *i, struct file *f)
{
	printk("open\n");
	return 0;
}
int my_close (struct inode *i, struct file *f)
{
	printk("close\n");
	return 0;
}
ssize_t my_read (struct file *f, char __user *u, size_t s, loff_t *l)
{
	printk("read\n");
	if(atomic_read(&data)==0)
	{
		printk("data is not available\n");
	}
	rv=request_irq(1,handler,IRQF_SHARED,"km",&id);
	wait_event_interruptible(wq,(atomic_read(&data)==1));
	return 0;
}

ssize_t my_write (struct file *f, const char __user *u, size_t s, loff_t *l)
{
	printk("write\n");
	//atomic_set(&data,1);
	//wake_up_interruptible(&wq);
	return s;
}
static int init_keypad(void)
{
	printk("init_keypad\n");
	register_chrdev(60,"keypad",&fiop);
	return 0;
}
static void exit_keypad(void)
{
	unregister_chrdev(60,"keypad");
	free_irq(1,&id);
	printk("exit_keypad\n");
}

module_init(init_keypad);
module_exit(exit_keypad);
