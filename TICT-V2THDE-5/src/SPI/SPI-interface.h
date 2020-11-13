#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include <stdint.h>

typedef struct
{
    void (*open)(uint8_t u8Port, uint32_t u32Frequency);
    void (*close)(uint8_t u8Port);

    void (*send_byte)(uint8_t u8Port, uint8_t u8Data);
    void (*send_multiple_blocking)(uint8_t u8Port, uint8_t *u8Data, unsigned uLen);

    uint8_t (*receive_byte)(uint8_t u8Port);
} SPIInterface;

#endif /* SPI_INTERFACE_H_ */
