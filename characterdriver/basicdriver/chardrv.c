#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>

static int hello_init(void){
	printk(KERN_INFO "hello world");
	return 0;
}

static void hello_exit(void){
	printk(KERN_INFO "hi kernel");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("jyothi");
MODULE_DESCRIPTION("character driver programming");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
