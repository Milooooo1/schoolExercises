#include "hwlib-SPI-due.hpp"
#include "SPI-due.hpp"

extern "C"
{

    /* Singleton doesn't need to be opened */
    void _DUE_SPI_open(uint8_t a, uint32_t b)
    {

    }

    /* It doesn't need to be closed either */
    void _DUE_SPI_close(uint8_t a)
    {

    }

    void _DUE_SPI_send_byte(uint8_t au8Port, uint8_t au8Data)
    {
        due::SPI::instance().write_byte(au8Data);
    }


    void _DUE_SPI_send_multiple(uint8_t au8Port, uint8_t *au8pData, unsigned auLen)
    {
        due::SPI::instance().write_multiple(au8pData, auLen);
    }

    uint8_t _DUE_SPI_read(uint8_t a)
    {
        return due::SPI::instance().read_byte();
    }

}

SPIInterface SPI_INTERFACE_DUE =
{
    &_DUE_SPI_open,
    &_DUE_SPI_close,
    &_DUE_SPI_send_byte,
    &_DUE_SPI_send_multiple,
    &_DUE_SPI_read
};