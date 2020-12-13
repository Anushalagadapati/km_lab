#include<linux/module.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/kernel.h>
ssize_t my_read (struct file *, char __user *, size_t, loff_t *);
ssize_t my_write (struct file *, const char __user *, size_t, loff_t *);
int my_release (struct inode *, struct file *);
int my_open (struct inode *, struct file *);
struct file_operations fops ={
//.owner=my_owner,
.open=my_open,
.read=my_read,
.write=my_write,
.release=my_release
};
ssize_t my_read (struct file *f, char __user *u, size_t s, loff_t *l)
{
printk("read\n");
return 0;
}
ssize_t my_write (struct file *f, const char __user *u, size_t s, loff_t *l)
{
printk("write\n");
return s;
}
int my_open (struct inode *i, struct file *f)
{
printk("open\n");
return 0;
}
int my_release (struct inode *i, struct file *f)
{
printk("release\n");
return 0;
}
static int dev_init(void)
{
printk("dev_init\n");
register_chrdev(60,"mychar",&fops);
return 0;
}

static void dev_exit(void)
{
printk("dev_exit\n");
unregister_chrdev(60,"mychar");
}

module_init(dev_init);
module_exit(dev_exit);
