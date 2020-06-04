/*********************************************************************************************************************
 *                                   C O P Y R I G H T                                                               *
 *********************************************************************************************************************
 *                             GNU GENERAL PUBLIC LICENSE                                                            *
 *                              Version 3, 29 June 2007                                                              *
 *                                                                                                                   *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>                                              *
 * Everyone is permitted to copy and distribute verbatim copies                                                      *
 * of this license document, but changing it is not allowed.                                                         *
 *********************************************************************************************************************/
/*! ******************************************************************************************************************
 * @file FileOps.c                                                                                                   *
 * @ingroup Sample_4                                                                                                 *
 * @brief This file implements a sample testing programe for file operations                                         *
 * @author divinraj1994@gmail.com                                                                                    *
 *********************************************************************************************************************/

/*! ******************************************************************************************************************
 * @System Includes                                                                                                  *
 *********************************************************************************************************************/
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>

/*! ******************************************************************************************************************
 * @Program specific Macros                                                                                          *
 *********************************************************************************************************************/

/*! @MINOR Number base */
#define BASE_MINORNUMBER    1u

/*! @Consecutive Number Requsted for Minor */
#define MINORNUMBER_RANGE   1u

/*! @Return Types */
#define E_OK                0u //Success
#define E_NOT_OK            1u //Fail

#define maxsize             100u

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
/*! ******************************************************************************************************************
 * @Variables for argument passing                                                                                   *
 *********************************************************************************************************************/
static struct class *extClass;
static struct cdev extCdev;

/*! ******************************************************************************************************************
 * @Local Includes                                                                                                   *
 *********************************************************************************************************************/
static int __init InitDrv(void);
static void __exit RemoveDrv(void);
static ssize_t ExtDeviceRead(struct file *File, char __user *Buf, size_t Len, loff_t *Off);
static ssize_t ExtDeviceWrite(struct file *File, const char __user *Buf, size_t Len, loff_t *Off);
static int ExtDeviceOpen(struct inode *Inode, struct file *File);
static int ExtDeviceRelease(struct inode *Inode, struct file *File); 
static long ExtDeviceIoctl(struct file *File, unsigned int cmd, unsigned long arg);


/*! ******************************************************************************************************************
 * @Global Struct Defnisions                                                                                         *
 *********************************************************************************************************************/
static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.read = ExtDeviceRead,
	.write = ExtDeviceWrite,
	.open = ExtDeviceOpen,
	.unlocked_ioctl = ExtDeviceIoctl,
	.release = ExtDeviceRelease,
};

/*! ******************************************************************************************************************
 * @param macros                                                                                                     *
 *********************************************************************************************************************/

/*! ******************************************************************************************************************
 * @Global variable declarations                                                                                     *
 *********************************************************************************************************************/
static dev_t dev = 0u;
uint8_t *KernBuff;
int32_t value = 0;
/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     ExtDeviceRead - Reading Divice                                                                         *
 *                                                                                                                   *
 * @param[in] File -                                                                                                 *
 *            Buf -                                                                                                  *
 * 	      Buf -                                                                                                  *
 *            Len -                                                                                                  *
 *            Off -                                                                                                  *
 *@return     Success                                                                                                 *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
static ssize_t ExtDeviceRead(struct file *File, char __user *Buf, size_t Len, loff_t *Off)
{


	printk(KERN_INFO "Data read : Done!\n");
	return 0;
}

/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     ExtDeviceRead - Reading Divice                                                                         *
 *                                                                                                                   *
 * @param[in] File -                                                                                                 *
 *            Buf -                                                                                                  *
 * 	      Buf -                                                                                                  *
 *            Len -                                                                                                  *
 *            Off -                                                                                                  *
 *@return     Success                                                                                                 *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
static ssize_t ExtDeviceWrite(struct file *File, const char __user *Buf, size_t Len, loff_t *Off)
{
	printk(KERN_INFO "Data writtern : Done\n");
	return maxsize;
}

/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     Module to Init Kernel Module                                                                           *
 *                                                                                                                   *
 * @param[in] Inode -                                                                                                *
 *            File                                                                                                   *
 *                                                                                                                   *
 * @return    Success                                                                                                *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
static int ExtDeviceOpen(struct inode *Inode, struct file *File)
{

	printk(KERN_INFO "Device File Opened..!!\n");
	return 0;
}

/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     Module to Init Kernel Module                                                                           *
 *                                                                                                                   *
 * @param[in] Inode -                                                                                                *
 *            File  -                                                                                                *
 *                                                                                                                   *
 * @return    Success                                                                                                *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
static int ExtDeviceRelease(struct inode *Inode, struct file *File)
{
	printk(KERN_INFO "Device File Closed..!!\n");
	return 0;
}


/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     ExtDeviceIocttl - writing and reading data                                                             *
 *                                                                                                                   *
 * @param[in] File -                                                                                                 *
 *            cmd -                                                                                                  *
 *            arg -                                                                                                  *
 *@return     Success                                                                                                *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
static long ExtDeviceIoctl(struct file *File, unsigned int cmd, unsigned long arg)
{

		switch(cmd) {
			case WR_VALUE:
				copy_from_user(&value ,(int32_t*)arg, sizeof(value));
				printk(KERN_INFO "Value = %d\n", value);
				break;
			case RD_VALUE:
				copy_to_user((int32_t*)arg, &value, sizeof(value));
				break;
		}


	return 0;
}

/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     Module to Init Kernel Module                                                                           *
 *                                                                                                                   *
 * @param[in] none                                                                                                   *
 *                                                                                                                   *
 * @return    Success                                                                                                *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
static int __init InitDrv(void)
{
	uint8_t Ret = E_NOT_OK;

	printk(KERN_INFO "Entering into kernel world\n");

	Ret = alloc_chrdev_region(&dev, BASE_MINORNUMBER, MINORNUMBER_RANGE,"extDrv");
	if(Ret != E_OK)
	{
		printk(KERN_INFO "Failed to allocate Major and Minor Number for : extDrv\n");
		return E_NOT_OK;
	}

	printk(KERN_INFO "Major Number Created for  extDrv : %d\n", MAJOR(dev));
	printk(KERN_INFO "Minor Number Created for  extDrv : %d\n", MINOR(dev));


	cdev_init(&extCdev,&fops);

	if((cdev_add(&extCdev,dev,1)) < 0)
	{
		printk(KERN_INFO "Char device failed registered..!!\n");
		goto class_error; 
	}
	else
	{
		printk(KERN_INFO "Char device successfully registered..!!\n");

	}


	if((extClass = class_create(THIS_MODULE,"extClass")) == NULL )
	{
		printk(KERN_INFO "Failed to create a class\n");
		goto class_error;
	}
	else
	{

		printk(KERN_INFO "Device Class created..!\n");
	}

	if(device_create(extClass,NULL,dev,NULL,"extDev")== NULL)
	{
		printk(KERN_INFO "Unable to create a device\n");
		goto dev_error;
	}
	else
	{

		printk(KERN_INFO "Device Created..!\n");
	}

	return E_OK;

dev_error:
	class_destroy(extClass);

class_error:
	unregister_chrdev_region(dev,MINORNUMBER_RANGE);

	return E_NOT_OK;

}

/*! *****************************************************************************************************************
 *                                                                                                                  *
 * @brief     Function to remove Remove Driver from Kernel                                                          *
 *                                                                                                                  *
 * @param[in] none                                                                                                  *
 *                                                                                                                  *
 * @return    none                                                                                                  *
 *                                                                                                                  *
 *******************************************************************************************************************/
static void __exit RemoveDrv(void)
{
	device_destroy(extClass,dev);
	class_destroy(extClass);
	cdev_del(&extCdev);
	unregister_chrdev_region(dev, MINORNUMBER_RANGE);
	printk(KERN_INFO "Major and minor Numbers are de-registerd\n");
	printk(KERN_INFO "Leaving from kernel space\n");

}

/*! *****************************************************************************************************************
 * @Module Init and Exit Macro                                                                                      *
 ********************************************************************************************************************/
module_init(InitDrv);
module_exit(RemoveDrv);

/*! *****************************************************************************************************************
 * @Module Informations                                                                                             *
 ********************************************************************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Divin Raj");
MODULE_DESCRIPTION("extDrv for Allocating Major and Minor Number");
MODULE_VERSION("v.1.0");

/******************************************END OF FILE **************************************************************/

