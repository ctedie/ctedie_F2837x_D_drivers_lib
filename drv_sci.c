/****************************************************** COMECA *******************************************************
 *  \author		tedie.cedric
 *  \date		9 mars 2018
 *  \addtogroup	DRIVERS
 *  \{
 ********************************************************************************************************************/
/****************************************************** COMECA *******************************************************
 *  \file		drv_sci.c
 *  
 *  \brief		The SCI driver source file
 *
 *  \details	
 *
 ********************************************************************************************************************/

/* Includes --------------------------------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "DSP2834x_Device.h"

#include "drv_sci.h"

/* Macro definition ------------------------------------------------------------------------------------------------*/
/* Constant definition ---------------------------------------------------------------------------------------------*/
/* Type definition  ------------------------------------------------------------------------------------------------*/

/** The SCI Handle structure */
typedef struct
{
    volatile struct SCI_REGS *sci;

    drvSciReceiveCallback_t cbReception;
    void* pReceptionData;
    drvSciTransmitCallback_t cbTransmission;
    void* pTransmitionData;
    drvSciEndOfTransmitionCallback_t cbEndOfTransmition;
    void* pEndOfTransmitionArg;


    bool initOk;

}UARTHandle_t;

/* Public variables ------------------------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------------------------*/

UARTHandle_t m_UARTList[NB_SERIAL] =
{
     {
          .sci = &SciaRegs,
          .initOk = false
     },
     {
          .sci = &ScibRegs,
          .initOk = false
     },
     {
          .sci = &ScicRegs,
          .initOk = false
     }
};

/* Private functions prototypes ------------------------------------------------------------------------------------*/
static bool setBaudRate(volatile struct SCI_REGS *pSci, drvSciSpeed_t speed);

/* Private functions -----------------------------------------------------------------------------------------------*/

/***********************************************************
 * \brief
 *
 * \param
 *
 * \return
 **********************************************************/
static bool setBaudRate(volatile struct SCI_REGS *pSci, drvSciSpeed_t speed)
{
    uint16_t brr_Value;

    //TODO Get CPU clock instead of 300000000
    brr_Value = 300000000 / ((uint32_t)speed * 8 * (SysCtrlRegs.LOSPCP.bit.LSPCLK * 2));
    pSci->SCIHBAUD = (brr_Value >> 8) & 0xFF;
    pSci->SCILBAUD = (brr_Value & 0xFF);

    return true;
}

/* Public functions ------------------------------------------------------------------------------------------------*/

/**********************************************************
 * \brief The driver initialization function
 * \warning GPIO pins must be configured before
 *
 * \param [in]  uartNb
 * \param [in]  pConfig
 *
 * \return
 *********************************************************/
drvSciReturn_t DRV_SCI_Init(drvSciNumber_t uartNb, drvSciConfig_t *pConfig)
{
    drvSciReturn_t ret = DRV_SCI_SUCCESS;
    UARTHandle_t* pHandle = &m_UARTList[uartNb];
    if(pConfig == NULL)
    {
        //Error
        return DRV_SCI_BAD_CONFIG;
    }

    pHandle->sci->SCICCR.all = 0;
    pHandle->sci->SCICTL1.bit.SWRESET = 0;  //Set in reset state

    pHandle->cbReception = pConfig->cbReception;
    pHandle->pReceptionData = pConfig->pReceptionData;
    pHandle->cbTransmission = pConfig->cbTransmission;
    pHandle->pTransmitionData = pConfig->pTransmitionData;
    pHandle->cbEndOfTransmition = pConfig->cbEndOfTransmition;
    pHandle->pEndOfTransmitionArg = pConfig->pEndOfTransmitionArg;

    /* Data size config */
    pHandle->sci->SCICCR.bit.SCICHAR = pConfig->dataSize;

    /* Parity Config */
    if (pConfig->parity != DRV_SCI_PARITY_NONE)
    {
        pHandle->sci->SCICCR.bit.PARITYENA = 1;
        pHandle->sci->SCICCR.bit.PARITY = pConfig->parity - 1;
    }

    /* Stop bit config */
    pHandle->sci->SCICCR.bit.STOPBITS = pConfig->stopBit;

    /* Baud Rate config */
    setBaudRate(pHandle->sci, pConfig->baudrate);

    pHandle->sci->SCICTL1.bit.RXENA = 1;
//    pHandle->sci->SCICTL2.bit.RXBKINTENA;
    pHandle->sci->SCICTL1.bit.TXENA = 1;

    pHandle->sci->SCICTL1.bit.SWRESET = 1; //Release from reset state
    pHandle->initOk = true;
    return ret;
}

/***********************************************************
 * \brief
 *
 * \param
 *
 * \return
 **********************************************************/
drvSciReturn_t DRV_SCI_WriteChar(drvSciNumber_t uartNb, uint16_t car)
{
    m_UARTList[uartNb].sci->SCITXBUF = car;

    return DRV_SCI_SUCCESS;
}

/***********************************************************
 * \brief
 *
 * \param
 *
 * \return
 **********************************************************/
drvSciReturn_t DRV_SCI_ReadChar(drvSciNumber_t uartNb, uint16_t* pCar)
{
    *pCar = m_UARTList[uartNb].sci->SCIRXBUF.bit.RXDT;
    return DRV_SCI_SUCCESS;
}

/** \} */
/******************************************************** EOF *******************************************************/