#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>

#include <linux/cdev.h>

#include <linux/slab.h>

/// header
#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0   /* dynamic major by default */
#endif

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4    /* scull0 through scull3 */
#endif

struct scull_qset {
  void **data;
  struct scull_qset* next;
};

struct scull_dev {
  struct scull_qset *data;
  int quantum;
  int qset;
  unsigned long size;
  unsigned int access_key;
  struct semaphore sem;
  struct cdev cdev;  
};
/// header

MODULE_LICENSE("Dual BSD/GPL");

int scull_major =   SCULL_MAJOR;
int scull_minor =   0;
int scull_nr_devs = SCULL_NR_DEVS;

struct scull_dev* scull_devices;  // alloc

static struct file_operations scull_fops = {
  .owner = THIS_MODULE  
};

static int scull_init_module(void)
{
  int result, i;
  dev_t dev = 0;
  
  /// Get <M, M>
  if (scull_major) {
    // static alloc.?
    dev = MKDEV(scull_major, scull_minor);
    result = register_chrdev_region(dev, scull_nr_devs, "scull");
  } else {
    result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
				 "scull");
    scull_major = MAJOR(dev);
  }
  
  /// Don't connect with name!!
  
  ///
  if (result < 0) {
    printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
    return result;
  }
  
  // alloc для нескольких устройств
  scull_devices = kmalloc(
      scull_nr_devs * sizeof(struct scull_dev),
      GFP_KERNEL);
  
  printk(KERN_ALERT "Hello, world\n");
  return 0;
  
fail:
  return -1;
}


static void scull_cleanup_module(void)
{
  dev_t devno = MKDEV(scull_major, scull_minor);
  
  
  /* */
  unregister_chrdev_region(devno, scull_nr_devs);
  printk(KERN_ALERT "Goodbye, cruel world\n");
}
 
module_init(scull_init_module);
module_exit(scull_cleanup_module);
