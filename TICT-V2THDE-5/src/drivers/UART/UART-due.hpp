#ifndef UART_DUE_HPP_
#define UART_DUE_HPP_

#include "UART-interface.hpp"

#define register 
#include "../../bmptk/targets/cortex/atmel/sam3xa/include/sam3x8e.h"

#define DUE_MAX_CLOCK_SPEED 84000000

class UARTDue : public UARTInterface
{
    private:
        uint8_t u8Port;
        uint32_t u32Baudrate;
        STOP_BITS eStopBits;
        PARITY eParity;
        WORD_LENGTH eWordLength;

        struct Pin { uint8_t u8Port, u8Pin; };
        struct PinPair {struct Pin TX, RX; };

        const struct PinPair arrDuePinPairs[4] = 
        {
            {{0u, 11u}, {0u,10u}},
            {{0u, 13u}, {0u,12u}},
            {{0u, 20u}, {0u,21u}},
            {{1u, 4u},  {1u,5u}}
        };

        Usart *pArrDueUSARTS[4] =
        {
            USART0,
            USART1,
            USART2,
            USART3
        };

        void configure_IO_alternate_function(Pin pinToConfigure);
        void configure(void);

    public:
        UARTDue(    uint8_t u8Port, uint32_t u32Baudrate, STOP_BITS eStopBits,
                    PARITY eParity, WORD_LENGTH eWordLength);

        virtual void put_char(uint8_t u8ByteToSend) override;
        virtual uint8_t read_char(void) override;        
};

#endif /* UART_DUE_HPP_ */
