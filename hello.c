#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Varich Boonsanong");
MODULE_DESCRIPTION("A simple kernel that say hello and goodbye to you");

static int __init init(void) {
  printk(KERN_INFO "Hello world\n");
  return 0;
}

static void __exit cleanup(void) { printk(KERN_INFO "Goodbye!\n"); }

module_init(init);
module_exit(cleanup);
