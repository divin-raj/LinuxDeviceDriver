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
 * @file DeviceFile.c                                                                                                *
 * @ingroup Sample_3                                                                                                 *
 * @brief This file implements a sample testing programe for creating Device file automaticly                        *
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

/*! ******************************************************************************************************************
 * @Variables for argument passing                                                                                   *
 *********************************************************************************************************************/
static struct class *extClass;

/*! ******************************************************************************************************************
 * @Local Includes                                                                                                   *
 *********************************************************************************************************************/
static int __init InitDrv(void);
static void __exit RemoveDrv(void);

/*! ******************************************************************************************************************
 * @Global Struct Defnisions                                                                                         *
 *********************************************************************************************************************/

/*! ******************************************************************************************************************
 * @param macros                                                                                                     *
 *********************************************************************************************************************/

/*! ******************************************************************************************************************
 * @Global variable declarations                                                                                     *
 *********************************************************************************************************************/
static dev_t dev = 0u;

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

	if((extClass = class_create(THIS_MODULE,"extClass")) == NULL )
	{
		printk(KERN_INFO "Failed to create a class\n");
		goto class_error;
	}

	if(device_create(extClass,NULL,dev,NULL,"extDev")== NULL)
	{
		printk(KERN_INFO "Unable to create a device\n");
		goto dev_error;
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

