#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/version.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>


static dev_t dev_number;
static struct cdev c_dev;
static struct class *c_class;

static int device_open(struct inode *inode, struct file *ifile){
	printk(KERN_INFO "module opening\n");
	return 0;
}
ssize_t static device_read(struct file *ifile, char __user *buf, size_t len,loff_t *off){
	printk(KERN_INFO "module start to reading");
	return len;
}

ssize_t static device_write(struct file *ifile, const char __user *buf, size_t len, loff_t *off){
	printk(KERN_INFO "module start to write");
	return len;
}

static int device_release(struct inode *inode, struct file *ifile){
	printk(KERN_INFO "module release");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};

static int __init file_init(void){
	pr_info(KERN_INFO "hi hello kernel");
    int	err= alloc_chrdev_region(&dev_number,0,1,"characterdriver");
	    if(err == 0){
		    printk("failed to register");
	    }
	 printk("major is %d minor is %d",MAJOR(dev_number),MINOR(dev_number));
	cdev_init(&c_dev,&fops);
	cdev_add(&c_dev,dev_number,1);
	c_class =class_create(THIS_MODULE, "class_created");
	device_create(c_class,NULL,dev_number,NULL,"device_create");
	return 0;
}

static void __exit file_exit(void){
	pr_info(KERN_INFO "bye bye kernel");
	device_destroy(c_class,dev_number);
	class_destroy(c_class);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev_number,1);
}



module_init(file_init);
module_exit(file_exit);


MODULE_AUTHOR("jyothi");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("hello kernel am using u");
MODULE_VERSION("0.1");
