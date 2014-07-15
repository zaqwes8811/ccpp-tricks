
// dmesg | tail -7

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first;  // gl var for the first dev number

// Step 5

static struct cdev c_dev;
static struct class *cl;

/// IO
static int my_open(
    struct inode *i, 
    struct file *f)
{
  printk(KERN_INFO "Driver: open()\n");
  return 0;
}

static int my_close(
    struct inode *i, 
    struct file *f)
{
  printk(KERN_INFO "Driver: close()\n");
  return 0;
}
  
static ssize_t my_read(
    struct file *f, 
    char __user *buf, 
    size_t len, 
    loff_t *off)
{
  printk(KERN_INFO "Driver: read()\n");
  return 0;
}
static ssize_t my_write(
    struct file *f, 
    const char __user *buf,
    size_t len, 
    loff_t *off)
{
  printk(KERN_INFO "Driver: write()\n");
  return len;
}

static struct file_operations pugs_fops =
{
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  .write = my_write
};
/// IO

static int __init ofd_init(void)  // ctor
{
  printk(KERN_INFO "Namaskar: ofd registered");
  //return -1;
  
  // Step 4
  if (alloc_chrdev_region(&first, 0, 1, "Shweta3") < 0)
  {
    return -1;    
  }
 
  if ((cl = class_create(THIS_MODULE, "chardvr")) == NULL)
  {
    unregister_chrdev_region(first, 1);
    return -1;
  }
  
  if (device_create(cl, NULL, first, NULL, "mynull") == NULL)
  {
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }
  
  // init
  cdev_init(&c_dev, &pugs_fops);
  
  if (cdev_add(&c_dev, first, 1) == -1)
  {
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    return -1;
  }
  
  
  // TODO: Where? 
  // int register_chrdev_region(dev_t first, unsigned int cnt, char *name);
  //
  // http://stackoverflow.com/questions/9835850/allocating-device-numbers
  //
  //printk(KERN_INFO "<Maj, Min>: <%d, %d>\n", MAJOR(first), MINOR(first));
  return 0;  
  
  // show in 
  // cat /proc/devices, but not in /dev/*
  //
  // need map
  // ls -l /dev | grep "250,"
  // mknod /dev/ofcd0 c 250 0
  // mknod /dev/ofcd1 c 250 1
  // chmod a+w /dev/ofcd*
  // ls -l /dev/ofcd*
  //
  // automap?
}

static void __exit ofd_exit(void)  // dtor
{
  // leak if no unregistered?
  //unregister_chrdev_region(first, 3);  // почему 3?
  cdev_del(&c_dev);
  device_destroy(cl, first);
  class_destroy(cl);
  
  unregister_chrdev_region(first, 1);
  printk(KERN_INFO "Alvida: ofd unregistered");  
}

module_init(ofd_init);
module_exit(ofd_exit);

// Info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email_at_sarika-pugs_dot_com>");
MODULE_DESCRIPTION("Our First Driver");