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
/*! *******************************************************************************************************************
 * @file MajorMinorNumber.c                                                                                          *
 * @ingroup Sample_1                                                                                                 *
 * @brief This file implements a smple testing sample module for Major and Minor Number                              *
 * @author divinraj1994@gmail.com                                                                                    *
 *********************************************************************************************************************/

/*! ********************************************************************************************************************
 * @System Includes                                                                                                   *
 *********************************************************************************************************************/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>


/*! ********************************************************************************************************************
 * @Program specific Macros                                                                                                    *
 *********************************************************************************************************************/

/*! @MINOR Number base */
#define BASE_MINORNUMBER    1u

/*! @Consecutive Number Requsted for Minor */
#define MINORNUMBER_RANGE   1u

/*! @Return Types */
#define E_OK                0u //Success
#define E_NOT_OK            1u //Fail

/*! ********************************************************************************************************************
 * @Local Includes                                                                                                   *
 *********************************************************************************************************************/
static int __init InitDrv(void);
static void __exit RemoveDrv(void);


static dev_t dev = 0u;
/*! *******************************************************************************************************************
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

	printk(KERN_INFO "Major and Minor Numbers are successfully Created.!!\n");

	return E_OK;

}

/*! ******************************************************************************************************************
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

	unregister_chrdev_region(dev, MINORNUMBER_RANGE);
	printk(KERN_INFO "Major and minor Numbers are de-registerd\n");
	printk(KERN_INFO "Leaving from kernel space\n");

}

/*! *******************************************************************************************************************
 * @Module Init and Exit Macro                                                                                        *
 **********************************************************************************************************************/
module_init(InitDrv);
module_exit(RemoveDrv);

/*! *******************************************************************************************************************
 * @Module Informations                                                                                               *
 **********************************************************************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Divin Raj");
MODULE_DESCRIPTION("extDrv for Allocating Major and Minor Number");
MODULE_VERSION("v.1.0");

/******************************************END OF FILE ****************************************************************/

