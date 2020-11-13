#ifndef UART_INTERFACE_HPP_
#define UART_INTERFACE_HPP_

#include <cstdint>

class UARTInterface
{
    public:
        enum STOP_BITS    {STOP_BITS_1, STOP_BITS_1_5, STOP_BITS_2};

        enum PARITY       {PARITY_NONE, PARITY_EVEN, PARITY_ODD};

        enum WORD_LENGTH  {WORD_LENGTH_5, WORD_LENGTH_6, WORD_LENGTH_7,
                             WORD_LENGTH_8, WORD_LENGTH_9};
                        
        virtual void put_char(uint8_t u8ByteToSend) = 0;
        virtual uint8_t read_char(void) = 0;
};

#endif /* UART_INTERFACE_HPP_ */