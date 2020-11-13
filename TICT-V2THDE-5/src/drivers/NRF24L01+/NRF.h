#ifndef NRF_H_
#define NRF_H_

#ifdef __cplusplus 
extern "C" {
#endif

#include "../SPI/SPI-interface.h"
#include "../IO/GPIO-interface.h"

/// @file

/* ---------------------------- ENUMERATED TYPES --------------------------- */

enum NRF_STATUS
{
    NRF_STATUS_OK,
    NRF_STATUS_DATA_NOT_READY
};

/* -------------------------- ENUMERATED TYPES END ------------------------- */


/* -------------------------------- INTERFACE ------------------------------ */

/******************************************************//**
* @brief
*  Setup function for the NRF module.
* @details
*  Sets up registers that are used in both transmitting
*  and receiving mode, a call to either 
*  NRF_enter_transit_mode or NRF_enter_receive_mode
*  is needed before using module.
* @param[in] apSPIProvider an implemented SPI
*             as defined in SPI-interface.h
* @param[in] au8SPIPort SPIport/SPIperipheral
*             directly passed to SPI interface
*             needed even if not used by interface.
* @param[in] apGPIOProvider an implemented GPIO interface
*             as defined in GPIO-interface.h.
* @param[in] auCEPinPort port of CE pin.
* @param[in] auCEPinNum pin number of CE pin.
* @param[in] auCSNPinPort port of CSN pin.
* @param[in] auCSNPinNum pin number of CSN pin.
* @param[in] au8Channel RF channel to be used by NRF.
* @param[in] au8PayloadLength Logic of NRF heavily
*             depens on the length of the payload
*             can be changed later on by the 
*             NRF_set_payload_length function.
**********************************************************/
void NRF_setup( SPIInterface *apSPIProvider, 
                uint8_t au8SPIPort, 
                GPIOInterface *apGPIOProvider,
                unsigned auCEPinPort,
                unsigned auCEPinNum,
                unsigned auCSNPinPort,
                unsigned auCSNPinNum,
                uint8_t au8Channel,
                uint8_t au8PayloadLenght
                );


/******************************************************//**
* @brief
*  Reads data from the RX FIFO.
* @details
*  Reads data from the RX FIFO. The function places
*  the data read in the buffer passed to the function.
*  The function is not blocking, it indicates whether 
*  it has succeeded in the return value.
* @param[out] apBuffer buffer to place the data in.
* @retval NRF_STATUS indicates whether the function
*          succeeded in reading the data from the FIFO.
**********************************************************/
enum NRF_STATUS NRF_read_data(uint8_t *apBuffer);


/******************************************************//**
* @brief
*  Sends out data
* @details
*  Sends out the data, it is an blocking operation it 
*  returns as soon as transmitting failed or as soon as
*  it reception is comfirmed by the recipient.
* @param[in] au8pData pointer to the data 
*             that is to be sent.
**********************************************************/
void NRF_write_data(uint8_t *au8pData);


/******************************************************//**
* @brief
*  Enters transmission mode.
* @details
*  Sets up all registers that need to be configured
*  before module is ready to transmit data.
**********************************************************/
void NRF_enter_transmit_mode(void);


/******************************************************//**
* @brief
*  Enters receive mode.
* @details
*  Sets up all registered that need to be configured
*  before module is ready to receive data.
**********************************************************/
void NRF_enter_receive_mode(void);


/******************************************************//**
* @brief
*  Updates payload length.
* @details
*  Updates payload length, payload length needs to be 
*  updated if one want to receive a different type of data. 
**********************************************************/
void NRF_set_payload_length(uint8_t u8Length);


/* ------------------------------ INTERFACE END ---------------------------- */

#ifdef __cplusplus 
}
#endif

#endif /* NRF_H_ */