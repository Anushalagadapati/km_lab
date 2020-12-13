/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *  www.kernelmasters.org                                                                       *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

/* Necessary includes for drivers */
#include <linux/init.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/ioport.h>
//#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <asm/io.h> /* inb, outb */
#include <linux/interrupt.h>
#include <linux/irqflags.h>

#define HW_LEN 80
#define IRQ_7 1
#define TEST_DEV "myIntDev"

MODULE_AUTHOR ("Kernel Masters");
MODULE_DESCRIPTION ("JOC: Android for Embedded Systems, KPHB, Hyderabad");
MODULE_LICENSE("Dual BSD/GPL");
/* Function declaration of keyboard.c */
int keyboard_open(struct inode *inode, struct file *filp);
int keyboard_release(struct inode *inode, struct file *filp);
ssize_t keyboard_read(struct file *filp, char *buf,
		size_t count, loff_t *f_pos);
ssize_t keyboard_write(struct file *filp, char *buf,
		size_t count, loff_t *f_pos);
void keyboard_exit(void);
int keyboard_init(void);

void do_mytasklet (unsigned long);
DECLARE_TASKLET (my_tasklet, do_mytasklet, 0);
static int isrCnt=0;

/* Structure that declares the common */
/* file access fcuntions */
struct file_operations keyboard_fops = {
	.read= keyboard_read,
	.write= keyboard_write,
	.open= keyboard_open,
	.release= keyboard_release
};


/* Driver global variables */
/* Major number */
int keyboard_major = 61;
/* Control variable for memory */
/* reservation of the parallel port*/
//int port;

char keyboard_buffer;
int id;

module_init(keyboard_init);
module_exit(keyboard_exit);

void do_mytasklet (unsigned long unused)
{
	printk ("This message from tasklet\n");
}

static irqreturn_t myIntHandler (int irq, void *dev_id) //, struct pt_regs *regs)
{
	local_irq_disable();
	keyboard_buffer = inb(0x60);
	printk("Handler: %c",keyboard_buffer);
	tasklet_schedule(&my_tasklet);
	isrCnt++;
	local_irq_enable();
	return IRQ_HANDLED;
}

int keyboard_init(void) {
	int result;
	/* Registering device */
	result = register_chrdev(keyboard_major, "keyboard",
			&keyboard_fops);
	if (result < 0) {
		printk(
				"<1>keyboard: cannot obtain major number %d\n",
				keyboard_major);
		return result;
	}

	//keyboard modified init module
	/* Registering port 
	   port = check_region(0x378, 3);
	   if (port) {
	   printk("<1>keyboard: cannot reserve 0x378\n");
	   result = port;
	   goto fail;
	   }
	   request_region(0x378, 3, "keyboard");*/

	//outb(0x10,0x37A);
	printk("<1>Inserting keyboard module\n");
	return 0;
}

void keyboard_exit(void) {
	/* Make major number free! */
	unregister_chrdev(keyboard_major, "keyboard");
	//  outb(0x00,0x37A);

	//keyboard modified exit module>
	/* Make port free! */
	/*  if (!port) {
	    release_region(0x378,1);
	    }*/
	free_irq(IRQ_7,&id);
	printk("<1>Removing keyboard module\n");
}


int keyboard_open(struct inode *inode, struct file *filp) {
	/* Success */
	printk("open\n");
	return 0;
}

int keyboard_release(struct inode *inode, struct file *filp) {
	/* Success */
	printk("close\n");
	return 0;
}

ssize_t keyboard_read(struct file *filp, char *buf,
		size_t count, loff_t *f_pos) {
	/* Buffer to read the device */

	//keyboard inport
	/* Reading port */	
	int rv, i;
	rv = request_irq(IRQ_7, myIntHandler,IRQF_SHARED ,TEST_DEV,&id);
	if (rv )
	{

		printk ("<1>can't get interrupt %d\n",IRQ_7);

	}
	
	for(i = 0 ; i < 10; i++);

	/* We transfer data to user space */
	copy_to_user(buf,&keyboard_buffer,1);
	/* We change the reading position as best suits */
	if (*f_pos == 0) {
		*f_pos+=1;
		return 1;
	} else {
		return 0;
	}
}


ssize_t keyboard_write( struct file *filp, char *buf,
		size_t count, loff_t *f_pos) {
	/*  char *tmp;
	// Buffer writing to the device 
	char keyboard_buffer;
	tmp=buf+count-1;
	copy_from_user(&keyboard_buffer,tmp,1);
	//keyboard outport
	// Writing to the port 
	outb(keyboard_buffer,0x378);*/
	printk("Write function\n");
	return 1;
}

