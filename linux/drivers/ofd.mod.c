#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa6942b40, "module_layout" },
	{ 0xdfce4b05, "cdev_del" },
	{ 0x4d463351, "device_destroy" },
	{ 0xc48f0e0a, "cdev_add" },
	{ 0x5ce8b525, "cdev_init" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xbd7ada6c, "class_destroy" },
	{ 0x1ed7701c, "device_create" },
	{ 0xf1d424ee, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x50eedeb8, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

