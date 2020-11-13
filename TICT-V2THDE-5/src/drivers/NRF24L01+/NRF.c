#include "NRF.h"


/* ---------------------------- ENUMERATED TYPES --------------------------- */

enum NRF_REGISTER 
{
    NRF_REGISTER_CONFIG         = 0x00U,
    NRF_REGISTER_EN_AA          = 0x01U,
    NRF_REGISTER_EN_RXADDR      = 0x02U,
    NRF_REGISTER_SETUP_AW       = 0x03U,
    NRF_REGISTER_SETUP_RETR     = 0x04U,
    NRF_REGISTER_RF_CH          = 0x05U,
    NRF_REGISTER_RF_SETUP       = 0x06U,
    NRF_REGISTER_STATUS         = 0x07U,
    NRF_REGISTER_OBSERVE_TX     = 0x08U,
    NRF_REGISTER_CD             = 0x09U,
    NRF_REGISTER_RX_ADDR_P0     = 0x0AU,
    NRF_REGISTER_RX_ADDR_P1     = 0x0BU,
    NRF_REGISTER_RX_ADDR_P2     = 0x0CU,
    NRF_REGISTER_RX_ADDR_P3     = 0x0DU,
    NRF_REGISTER_RX_ADDR_P4     = 0x0EU,
    NRF_REGISTER_RX_ADDR_P5     = 0x0FU,
    NRF_REGISTER_TX_ADDR        = 0x10U,
    NRF_REGISTER_RX_PW_P0       = 0x11U,
    NRF_REGISTER_RX_PW_P1       = 0x12U,
    NRF_REGISTER_RX_PW_P2       = 0x13U,
    NRF_REGISTER_RX_PW_P3       = 0x14U,
    NRF_REGISTER_RX_PW_P4       = 0x15U,
    NRF_REGISTER_RX_PW_P5       = 0x16U,
    NRF_REGISTER_FIFO_STATUS    = 0x17U
};


enum NRF_COMMAND
{
    NRF_COMMAND_R_REGISTER      = 0x00U,
    NRF_COMMAND_W_REGISTER      = 0x20U,
    NRF_COMMAND_R_RX_PAYLOAD    = 0x61U,
    NRF_COMMAND_W_TX_PAYLOAD    = 0xA0U,
    NRF_COMMAND_FLUSH_TX        = 0xE1U,
    NRF_COMMAND_FLUSH_RX        = 0xE2U,
    NRF_COMMAND_REUSE_TX_PL     = 0xE3U,
    NRF_COMMAND_NOP             = 0xFFU
};

/* -------------------------- ENUMERATED TYPES END ------------------------- */


/* ---------------------- STATIC FUNCTIONS PROTOTYPES ---------------------- */

static void NRF_write_register(enum NRF_REGISTER reg, uint8_t au8Data);


static uint8_t NRF_read_register(enum NRF_REGISTER reg);


static uint8_t NRF_get_status(void);


static void SPI_send_blocking(uint8_t *pData, uint8_t u8Len);


static void SPI_send_byte(uint8_t u8Byte);


static void SPI_end_transfer(void);

/* -------------------- STATIC FUNCTIONS PROTOTYPES END -------------------- */


/* ---------------------------- STATIC VARIABLES --------------------------- */

static SPIInterface *pSPI;
static uint8_t u8SPIPort;

static GPIOInterface *pGPIO;
static unsigned uCEPinPort;
static unsigned uCEPinNum;
static unsigned uCSNPinPort;
static unsigned uCSNPinNum;

static uint8_t u8RFchannel;
static uint8_t u8PayloadLen;

/* -------------------------- STATIC VARIABLES END ------------------------- */


/* ---------------------------- STATIC FUNCTIONS --------------------------- */

static void NRF_write_register(enum NRF_REGISTER aeReg, uint8_t au8Data)
{
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);

    SPI_send_byte(NRF_COMMAND_W_REGISTER | aeReg);
    SPI_send_byte(au8Data);
    SPI_end_transfer();

    pGPIO->set_pin(uCEPinPort, uCEPinNum);
}


static uint8_t NRF_read_register(enum NRF_REGISTER aeReg)
{
    SPI_send_byte(NRF_COMMAND_R_REGISTER | aeReg);
    SPI_send_byte(NRF_COMMAND_NOP);
    SPI_end_transfer();
    
    return pSPI->receive_byte(u8SPIPort);
}


static uint8_t NRF_get_status(void)
{
    SPI_send_byte(NRF_COMMAND_NOP);
    SPI_end_transfer();

    return pSPI->receive_byte(u8SPIPort);
}


static void SPI_send_blocking(uint8_t *pData, uint8_t u8Len)
{
    pGPIO->reset_pin(uCSNPinPort, uCSNPinNum);
    pSPI->send_multiple_blocking(u8SPIPort, pData, u8Len);
    pGPIO->set_pin(uCSNPinPort, uCSNPinNum);
}


static void SPI_send_byte(uint8_t u8Byte)
{
    pGPIO->reset_pin(uCSNPinPort, uCSNPinNum);
    pSPI->send_byte(u8SPIPort, u8Byte);
}


static void SPI_end_transfer(void)
{
    pSPI->receive_byte(u8SPIPort);
    pGPIO->set_pin(uCSNPinPort, uCSNPinNum);
}

/* -------------------------- STATIC FUNCTIONS END ------------------------- */


/* -------------------------------- INTERFACE ------------------------------ */

void NRF_setup( SPIInterface *apSPIProvider, 
                uint8_t au8SPIPort, 
                GPIOInterface *apGPIOProvider,
                unsigned auCEPinPort,
                unsigned auCEPinNum,
                unsigned auCSNPinPort,
                unsigned auCSNPinNum,
                uint8_t au8RFChannel,
                uint8_t au8PayloadLength
                )
{
    pSPI = apSPIProvider;
    u8SPIPort = au8SPIPort;
    
    u8RFchannel = au8RFChannel;
    u8PayloadLen = au8PayloadLength;

    pGPIO = apGPIOProvider;
    uCEPinPort = auCEPinPort;
    uCEPinNum = auCEPinNum;
    uCSNPinPort = auCSNPinPort;
    uCSNPinNum = auCSNPinNum;

    pGPIO->set_mode(GPIO_MODE_PUSH_PULL, uCEPinPort, uCEPinNum);
    pGPIO->set_mode(GPIO_MODE_PUSH_PULL, uCSNPinPort, uCSNPinNum);
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);
    pGPIO->set_pin(uCSNPinPort, uCSNPinNum);

    SPI_send_byte(NRF_COMMAND_FLUSH_TX);
    SPI_end_transfer();

    SPI_send_byte(NRF_COMMAND_FLUSH_RX);
    SPI_end_transfer();

    /* set RF channel */
    NRF_write_register(NRF_REGISTER_RF_CH, u8RFchannel);
}


void NRF_sleep(void)
{
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);
}


void NRF_write_data(uint8_t *au8pData)
{
    /* Check whether last transmission has failed,
    if so discard data and start again. */
    if((NRF_get_status() & 0x10) != 0x00)
    {
        NRF_write_register(NRF_REGISTER_STATUS, 0x10);
        SPI_send_byte(NRF_COMMAND_FLUSH_TX);
        SPI_end_transfer();
    }

    pGPIO->set_pin(uCEPinPort, uCEPinNum);
    
    /* Burn cycles to achieve a minimun high CE high time of 10us */
    for(volatile uint32_t i = 0xFF0; i > 0; i--);

    SPI_send_byte(NRF_COMMAND_W_TX_PAYLOAD);
    SPI_send_blocking(au8pData, u8PayloadLen);

    pGPIO->reset_pin(uCEPinPort, uCEPinNum);
    pGPIO->set_pin(uCEPinPort, uCEPinNum);

    /* Wait until ACK is received */
    while((NRF_get_status() & 0x30) == 0);
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);
}


enum NRF_STATUS NRF_read_data(uint8_t *apData)
{
    //uint8_t status = NRF_get_status();

    if(((NRF_get_status() & 0x40) == 0))
    {
        return NRF_STATUS_DATA_NOT_READY;
    }

    SPI_send_byte(NRF_COMMAND_R_RX_PAYLOAD);

    for(uint8_t i = u8PayloadLen; i > 0; i--)
    {
        SPI_send_byte(NRF_COMMAND_NOP);
        *apData++ = pSPI->receive_byte(u8SPIPort); 
    }
    SPI_end_transfer();

    SPI_send_byte(NRF_COMMAND_FLUSH_RX);
    SPI_end_transfer();

    NRF_write_register(NRF_REGISTER_STATUS, 0xFF);

    return NRF_STATUS_OK;
}


void NRF_set_payload_length(uint8_t au8Length)
{
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);

    u8PayloadLen = au8Length;
    NRF_write_register(NRF_REGISTER_RX_PW_P0, u8PayloadLen);
}


void NRF_enter_transmit_mode(void)
{
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);

    SPI_send_byte(NRF_COMMAND_FLUSH_RX);
    SPI_end_transfer();

    /* Clear config, clear status */
    NRF_write_register(NRF_REGISTER_CONFIG, 0x08);
    NRF_write_register(NRF_REGISTER_STATUS, 0xFF);

    NRF_write_register(NRF_REGISTER_CONFIG, 0x0A);
}


void NRF_enter_receive_mode(void)
{
    pGPIO->reset_pin(uCEPinPort, uCEPinNum);

    SPI_send_byte(NRF_COMMAND_FLUSH_TX);
    SPI_end_transfer();

    /* Clear config, clear status */
    NRF_write_register(NRF_REGISTER_CONFIG, 0x08);
    NRF_write_register(NRF_REGISTER_STATUS, 0xFF);

    /* Set up receiving channel */
    NRF_write_register(NRF_REGISTER_RX_PW_P0, u8PayloadLen);

    NRF_write_register(NRF_REGISTER_CONFIG, 0x09);

    for(volatile uint32_t i = 0xFF0; i > 0; i--);

    NRF_write_register(NRF_REGISTER_CONFIG, 0x0B);
    pGPIO->set_pin(uCEPinPort, uCEPinNum);
}

/* ------------------------------ INTERFACE END ---------------------------- */

