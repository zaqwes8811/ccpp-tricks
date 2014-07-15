#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>

/// header
#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0   /* dynamic major by default */
#endif

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4    /* scull0 through scull3 */
#endif
/// header

MODULE_LICENSE("Dual BSD/GPL");

int scull_major =   SCULL_MAJOR;
int scull_minor =   0;
int scull_nr_devs = SCULL_NR_DEVS;

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
  
  printk(KERN_ALERT "Hello, world\n");
  return 0;
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
