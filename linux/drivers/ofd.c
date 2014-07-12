
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static int __init ofd_init(void)  // ctor
{
  printk(KERN_INFO "Namaskar: ofd registered");
  return 0;  
}

static void __exit ofd_exit(void)  // dtor
{
  printk(KERN_INFO "Alvida: ofd unregistered");  
}

module_init(ofd_init);
module_exit(ofd_exit);

// Info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email_at_sarika-pugs_dot_com>");
MODULE_DESCRIPTION("Our First Driver");