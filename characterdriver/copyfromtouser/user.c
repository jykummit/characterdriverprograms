#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/slab.h>

int major;
//#define device_name "copy-from-to-user"
unsigned char *usr;

int device_open(struct inode *inode , struct file *ifile){
	pr_info(KERN_ALERT "module opening");
	return 0;
}

ssize_t device_read(struct file *ifile, char __user *buff, size_t len, loff_t *off){
	pr_info(KERN_ALERT "module start to reading");
	if(copy_to_user(buff,usr,len))
	{
		printk("copying user failes\n");
	}
	else{
	printk("copying to user is success using %s\n",buff);
	}

	kfree(usr);
	return 0;
}

ssize_t device_write(struct file *ifile,const char __user *buff, size_t len, loff_t *off){
	pr_info(KERN_ALERT "module start to write");
	
	usr=kzalloc(len,GFP_KERNEL);

	if(usr==NULL){
		printk("memory allocation failed");
	}
	else{
		printk("memory allocation success");
		if(copy_from_user(usr,buff,len)){
				printk("copying from user failed\n");
				return -1;
			}
			else{
				printk("copying from user success with %s\n",buff);
			}
		}
	return len;
}

int device_release(struct inode *inode , struct file *ifile){
	pr_info(KERN_ALERT "module closing");
	return 0;
}




struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.read = device_read,
	.write = device_write,
	.release = device_release
};


static int __init user_init(void){
	printk(KERN_INFO "module inserted successfully\n");
	major= register_chrdev(0,example_device,&fops);
	if(major <0){
		printk("registration failed %d\n",major);
	}
	printk("major number is %d\n",major);
	return 0;
}

static void __exit user_exit(void){
	printk(KERN_INFO "module removed successfully\n");
	unregister_chrdev(major,example_device);
}


module_init(user_init);
module_exit(user_exit);


MODULE_AUTHOR("JYOTHI");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("COPY FROM USER AND COPY TO USER PRACTICING");
MODULE_VERSION("0.1");



