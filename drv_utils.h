/*********************************************************************************************************************
 *                                                      COMECA
 ********************************************************************************************************************/
/**
 *********************************************************************************************************************
 *  \author		tedie.cedric
 *  \date		12 avr. 2018
 *  \addtogroup DRIVERS
 *  \{
 *  \addtogroup	DRV_UTILS
 *  \{
 ********************************************************************************************************************/
/**
 *********************************************************************************************************************
 *  \file		drv_utils.h
 *  
 *  \brief		The drivers utility tools header file
 *
 *  \details	It contains some utils functions
 *
 ********************************************************************************************************************/
#ifndef GENERIC_DRIVERS_LIB_DRV_UTILS_H_
#define GENERIC_DRIVERS_LIB_DRV_UTILS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes --------------------------------------------------------------------------------------------------------*/
#include <stdint.h>

/* Public Macro definition -----------------------------------------------------------------------------------------*/
#define EXTRACT_INT_NUMBER(x)  (((x) & 0xFFFF0000) >> 16)

/* Public Constant definition --------------------------------------------------------------------------------------*/
/* Public Type definition  -----------------------------------------------------------------------------------------*/
/* Public variables ------------------------------------------------------------------------------------------------*/
/* Public functions ------------------------------------------------------------------------------------------------*/

#endif /* GENERIC_DRIVERS_LIB_DRV_UTILS_H_ */

#ifdef __cplusplus
}
#endif

/** \} */
/** \} */
/******************************************************** EOF *******************************************************/