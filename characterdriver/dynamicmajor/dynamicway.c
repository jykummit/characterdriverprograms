// dynamic representation of major number and device files 

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>

static dev_t dev = 0;

static int __init gpiopin_init(void)
{
pr_info(KERN_ALERT "module insert sucessfully\n");
int major= alloc_chrdev_region(&dev,0,1,"example_driver");
printk("the major numer is %d\n",MAJOR(dev),MINOR(dev));
return 0;
}

static void __exit gpiopin_exit(void)
{
pr_info(KERN_ALERT "module remove sucessfully\n");
unregister_chrdev_region(dev,1);
}


module_init(gpiopin_init);
module_exit(gpiopin_exit);



MODULE_AUTHOR("JYOTHI");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("general purpose input and output programming");
MODULE_VERSION("0.1");

