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
 * @file ArgPassing.c                                                                                                *
 * @ingroup Sample_2                                                                                                 *
 * @brief This file implements a sample testing programe for passing arguments                                       *
 * @author divinraj1994@gmail.com                                                                                    *
 *********************************************************************************************************************/

/*! ******************************************************************************************************************
 * @System Includes                                                                                                  *
 *********************************************************************************************************************/
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/module.h>
#include<linux/moduleparam.h>


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
 * @Variables for argument passing                                                                                                  *
 *********************************************************************************************************************/
int intValue = 0;
int arrBuffer[5] = { 0 };
char *strName = NULL;
int cbValue = 0;

/*! ******************************************************************************************************************
 * @Local Includes                                                                                                   *
 *********************************************************************************************************************/
static int __init InitDrv(void);
static void __exit RemoveDrv(void);
int  paramSet_Notify(const char *val, const struct kernel_param *kp);

/*! ******************************************************************************************************************
 * @Global Struct Defnisions                                                                                         *
 *********************************************************************************************************************/
static struct kernel_param_ops cb_param_ops = {
.set = &paramSet_Notify,
.get = &param_get_int,
}; 

/*! ******************************************************************************************************************
 * @param macros                                                                                                     *
 *********************************************************************************************************************/
module_param(intValue, int, S_IWUSR|S_IRUSR);
module_param(strName, charp, S_IWUSR|S_IRUSR|S_IXUSR|S_IWGRP|S_IRGRP|S_IXGRP);
module_param_array(arrBuffer, int, NULL, S_IWUSR|S_IRUSR|S_IXUSR|S_IWGRP|S_IRGRP|S_IXGRP);
module_param_cb(cbValue, &cb_param_ops, &cbValue, S_IWUSR|S_IRUSR);

/*! ******************************************************************************************************************
 * @Global variable declarations                                                                                     *
 *********************************************************************************************************************/
static dev_t dev = 0u;

/*! ******************************************************************************************************************
 *                                                                                                                   *
 * @brief     Handler to notify when variable value get changed                                                      *
 *                                                                                                                   *
 * @param[in] val - updated value                                                                                    *
 *            kp  - param structure                                                                                  *                            *                                                                                                                   *
 * @return    Success                                                                                                *
 *            Failed                                                                                                 *
 *                                                                                                                   *
 *********************************************************************************************************************/
int  paramSet_Notify(const char *val, const struct kernel_param *kp)
{

uint8_t Ret = E_NOT_OK;
Ret = param_set_int(val, kp);
if(E_OK == Ret)
{
printk(KERN_INFO "module_param_cb Called.!!!\n");
printk(KERN_INFO "Value updated cbValue : %d\n", cbValue);
return Ret;
}
return E_NOT_OK;
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
int index = 0;
	printk(KERN_INFO "Entering into kernel world\n");

	Ret = alloc_chrdev_region(&dev, BASE_MINORNUMBER, MINORNUMBER_RANGE,"extDrv");
	if(Ret != E_OK)
	{
		printk(KERN_INFO "Failed to allocate Major and Minor Number for : extDrv\n");
		return E_NOT_OK;
	}

	printk(KERN_INFO "Major Number Created for  extDrv : %d\n", MAJOR(dev));
	printk(KERN_INFO "Minor Number Created for  extDrv : %d\n", MINOR(dev));

	printk(KERN_INFO "Registerd intValue : %d\n", intValue);
	printk(KERN_INFO "Registerd strName  : %s\n", strName);
	printk(KERN_INFO "Initialized cbValue : %d\n", cbValue);

for(index = 0; index < sizeof(arrBuffer)/sizeof(int); index++)
{
	printk(KERN_INFO "arrBuffer[%d] = %d \n", index, arrBuffer[index]);

}	printk(KERN_INFO "Major and Minor Numbers are successfully Created.!!\n");

	return E_OK;

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
MODULE_DESCRIPTION("Sample program to passing arguments to exicutable file");
MODULE_VERSION("v.1.0");

/******************************************END OF FILE **************************************************************/

