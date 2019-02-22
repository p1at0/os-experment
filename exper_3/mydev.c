#include"linux/kernel.h"
#include"linux/init.h"
#include"linux/uaccess.h"
#include"linux/module.h"
#include"linux/fs.h"
#include"linux/kdev_t.h"
#include"linux/types.h"
int device_open(struct inode *inode, struct file *file);
int device_release(struct inode *inode, struct file *file);
ssize_t device_read(struct file *file, char __user *user, size_t t, loff_t *f);
ssize_t device_write(struct file *file, const char __user *user, size_t t, loff_t *f);

const char* dev_name = "myDevice";
int device_major_id;
char message[1024];
struct file_operations pStruct =
{ 
	open:device_open, 
	release:device_release, 
	read:device_read, 
	write:device_write, 
};

// init 
int my_init_module(void)
{
	int id = register_chrdev(0, dev_name, &pStruct);
  if(id < 0){
    printk("register_chrdev error!\n");
    return -1;
  }else{
    device_major_id = id;
    printk("register_chrdev success!\n");
    printk("dev id is %d\n", id);
    return 0;
  }
}


// cleanup
void my_cleanup_module(void)
{
	unregister_chrdev(device_major_id, dev_name);
	printk("unregister successful.\n");
}

//open
int device_open(struct inode *inode, struct file *file){
  printk("open device ok!\n");
  try_module_get(THIS_MODULE);
  return 0;
}


// release
int device_release(struct inode *inode, struct file *file){
  printk("release device ok!\n");
  module_put(THIS_MODULE);
  return 0;
}

// read
ssize_t device_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
	if(copy_to_user(user,message,sizeof(message)))
	{
		return -2;
	}
  printk("read message ok!\n");
	return sizeof(message);
}
 
// write
ssize_t device_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
	if(copy_from_user(message,user,sizeof(message)))
	{
		return -3;
	}
  printk("write message ok!\n");
	return sizeof(message);
}

MODULE_LICENSE("GPL");
module_init(my_init_module);
module_exit(my_cleanup_module);
