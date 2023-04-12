#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/version.h>

int major;
static int device_open(struct inode *inode,struct file *ifile){
	printk(KERN_INFO "module opening");
	return 0;
}
ssize_t static device_read(struct file *ifile,char __user *buff, size_t len, loff_t *off){
	printk(KERN_INFO "module reading");
	return 0;
}
ssize_t static device_write(struct file *ifile,const char __user *buff, size_t len, loff_t *off){
        printk(KERN_INFO "module writing");
        return 0;
}


static int device_release(struct inode *inode,struct file *ifile){
		printk(KERN_INFO "module closing successfully");
		return 0;
}


struct  file_operations fops={
	.owner= THIS_MODULE,
	.open=device_open,
	.write = device_write,
	.release = device_release,
};

static int __init main_start(void){
	pr_info(KERN_ALERT "module loaded successfully");
	return 0;
}

static void __exit main_end(void){
	pr_info(KERN_ALERT "module unloaded successfully");
}


module_init(main_start);
module_exit(main_end);


MODULE_AUTHOR("JYOTHI");
MODULE_DESCRIPTION("module programming ");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
