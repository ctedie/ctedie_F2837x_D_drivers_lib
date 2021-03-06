/*********************************************************************************************************************
 *                                                      COMECA
 ********************************************************************************************************************/
/**
 ********************************************************************************************************************
 *  \author		tedie.cedric
 *  \date		9 mars 2018
 *  \addtogroup	DRIVERS
 *  \{
 *  \addtogroup DRV_SCI
 *  \{
 *
 *  \brief This module contains SCI API functions
 *
 *  \details
 ********************************************************************************************************************/
/**
 ********************************************************************************************************************
 *  \file		drv_sci.h
 *  
 *  \brief		The SCI driver header file
 *
 *  \details	
 *
 *********************************************************************************************************************/

#ifndef DRV_SCI_H_
#define DRV_SCI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes --------------------------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* Public Macro definition -----------------------------------------------------------------------------------------*/
/* Public Constant definition --------------------------------------------------------------------------------------*/
/* Public Type definition  -----------------------------------------------------------------------------------------*/
/**
 *********************************************************
 * \brief The receive callback type
 *
 * \details The purpose of this function is to get the
 *          char to received on SCI. \n
 *          This callback is called as long as the
 *          receive fifo is not full
 *
 * \param [in]  pData    A pointer to user defined arg
 * \param [in]  car      The read character
 *********************************************************/
typedef void (*drvSciReceiveCallback_t)(void *pData, uint16_t car);

/**
 *********************************************************
 * \brief The transmit callback type
 *
 * \details The purpose of this function is to get the
 *          char to send via SCI. \n
 *          This callback is called when there is
 *          space in the transmit fifo
 *
 * \param [in]  pData    A pointer to user defined arg
 * \param [out] car      The read character
 *********************************************************/
typedef bool (*drvSciTransmitCallback_t)(void *pData, uint16_t *car);

/** The end of transmission callback type */
typedef void (*drvSciEndOfTransmissionCallback_t)(void *pData);

/** The receive interrupt type */
typedef void (*drvSciRxIsr_t)(void);

/** The transmit interrupt type */
typedef void (*drvSciTxIsr_t)(void);

/** The specific return type enum */
typedef enum
{
    DRV_SCI_SUCCESS = 0,    /**< SERIAL_LINK_SUCCESS     */
    DRV_SCI_ERROR,          /**< SERIAL_LINK_ERROR       */
    DRV_SCI_BAD_CONFIG,     /**< SERIAL_LINK_BAD_CONFIG  */
    DRV_SCI_NOT_INIT,       /**< SERIAL_LINK_NOT_INIT    */
    DRV_SCI_TX_ERROR,       /**< SERIAL_LINK_TX_ERROR    */
    DRV_SCI_BAD_ID,         /**< SERIAL_LINK_BAD_ID      */
    DRV_SCI_NO_INPUT_CHAR,
    DRV_SCI_TX_BUSY,
    DRV_SCI_ALREADY_INIT
}drvSciReturn_t;

/** The SCI number enum */
typedef enum
{
    SCI_A = 0,
    SCI_B,
    SCI_C,
    SCI_D,

    NB_SERIAL
}drvSciNumber_t;

/** The SCI baudrate enum */
typedef enum
{
    DRV_SCI_B9600 = 9600,
    DRV_SCI_B19200 = 19200,
    DRV_SCI_B57600 = 57600,
    DRV_SCI_B115200 = 115200,
    DRV_SCI_B460800 = 460800,
    DRV_SCI_B921600 = 921600
}drvSciSpeed_t;

/** The SCI data size enum */
typedef enum
{
    DRV_SCI_BIT_1 = 1,
    DRV_SCI_BIT_2,
    DRV_SCI_BIT_3,
    DRV_SCI_BIT_4,
    DRV_SCI_BIT_5,
    DRV_SCI_BIT_6,
    DRV_SCI_BIT_7,
    DRV_SCI_BIT_8
}drvSciDataSize_t;

/** The SCI parity enum */
typedef enum
{
    DRV_SCI_PARITY_NONE,
    DRV_SCI_PARITY_ODD,
    DRV_SCI_PARITY_EVEN
}drvSciParity_t;

/** The SCI stop bit enum */
typedef enum
{
    DRV_SCI_STOP_BIT_1 = 0,
    DRV_SCI_STOP_BIT_2
}drvSciStopBit_t;

/** The SCI configuration structure */
typedef struct
{

    /** The baudrate */
    drvSciSpeed_t baudrate;

    drvSciDataSize_t dataSize;
    drvSciParity_t parity;
    drvSciStopBit_t stopBit;
    drvSciReceiveCallback_t cbReception;
    void* pReceptionData;
    drvSciTransmitCallback_t cbTransmission;
    void* pTransmitionData;
    drvSciEndOfTransmissionCallback_t cbEndOfTransmition;
    void* pEndOfTransmitionArg;
    bool initOk;
}drvSciConfig_t;

/* Public variables ------------------------------------------------------------------------------------------------*/
/* Public functions ------------------------------------------------------------------------------------------------*/

drvSciReturn_t DRV_SCI_Init(drvSciNumber_t uartNb, drvSciConfig_t *pConfig);
drvSciReturn_t DRV_SCI_BasicInit(drvSciNumber_t uartNb, uint32_t baudrate, uint16_t databits, drvSciParity_t parity, drvSciStopBit_t stopBit, drvSciRxIsr_t cbRxIsr, drvSciTxIsr_t cbTxIsr);
drvSciReturn_t DRV_SCI_WriteChar_NonBlocking(drvSciNumber_t uartNb, uint16_t car);
drvSciReturn_t DRV_SCI_ReadChar_NonBlocking(drvSciNumber_t uartNb, uint16_t* pCar);
drvSciReturn_t DRV_SCI_StartTx(drvSciNumber_t uartNb);
void DRV_SCI_EnableRx(drvSciNumber_t uartNb, bool enable);
void DRV_SCI_EnableTx(drvSciNumber_t uartNb, bool enable);
void DRV_SCI_Enable_RxINT(drvSciNumber_t uartNb, bool enable);
void DRV_SCI_Enable_TxINT(drvSciNumber_t uartNb, bool enable);
void DRV_SCI_ClearIT_Rx(drvSciNumber_t uartNb);
void DRV_SCI_ClearIT_Tx(drvSciNumber_t uartNb);

#ifdef __cplusplus
}
#endif

/** \} */
/** \} */
#endif /* DRV_SCI_H_ */

/******************************************************** EOF *******************************************************/
