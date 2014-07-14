
// dmesg | tail -7

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static dev_t first;  // gl var for the first dev number

static int __init ofd_init(void)  // ctor
{
  printk(KERN_INFO "Namaskar: ofd registered");
  
  // Step 4
  if (alloc_chrdev_region(&first, 0, 3, "Shweta3") < 0)
  {
    return -1;    
  }
  
  // TODO: Where? 
  // int register_chrdev_region(dev_t first, unsigned int cnt, char *name);
  //
  // http://stackoverflow.com/questions/9835850/allocating-device-numbers
  //
  printk(KERN_INFO "<Maj, Min>: <%d, %d>\n", MAJOR(first), MINOR(first));
  return 0;  
  
  // show in 
  // cat /proc/devices, but not in /dev/*
}

static void __exit ofd_exit(void)  // dtor
{
  // leak if no unregistered?
  unregister_chrdev_region(first, 3);  // почему 3?
  
  printk(KERN_INFO "Alvida: ofd unregistered");  
}

module_init(ofd_init);
module_exit(ofd_exit);

// Info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email_at_sarika-pugs_dot_com>");
MODULE_DESCRIPTION("Our First Driver");