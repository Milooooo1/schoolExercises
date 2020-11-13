#include "UART-due.hpp"


/* ------------------------------- Interface ------------------------------- */

void UARTDue::put_char(uint8_t u8ByteToSend)
{
    while((pArrDueUSARTS[u8Port]->US_CSR & US_CSR_TXRDY) == 0);

    pArrDueUSARTS[u8Port]->US_THR |= u8ByteToSend;
}


uint8_t UARTDue::read_char(void)
{
    while((pArrDueUSARTS[u8Port]->US_CSR & US_CSR_RXRDY) == 0);
    
    return (pArrDueUSARTS[u8Port]->US_RHR & (0xFF));
}

/* ---------------------------------- END ---------------------------------- */


/* ------------------------------- Constructor ----------------------------- */

UARTDue::UARTDue(
    uint8_t u8Port,
    uint32_t u32Baudrate, 
    STOP_BITS eStopBits,
    PARITY eParity, 
    WORD_LENGTH eWordLength)
    :
    u8Port(u8Port),
    u32Baudrate(u32Baudrate),
    eStopBits(eStopBits),
    eParity(eParity),
    eWordLength(eWordLength)
{
    configure();
}

/* ---------------------------------- END ---------------------------------- */


/* ---------------------------- private functions -------------------------- */

void UARTDue::configure_IO_alternate_function(Pin pinToConfigure)
{
    PMC->PMC_PCER0 = (0x1 << (ID_PIOA + pinToConfigure.u8Port));

    /* TODO: replace with define */
    Pio *pPIO = (Pio*)(0x400E0C00 + (0x200 << pinToConfigure.u8Port));

    pPIO->PIO_PDR |= (0x1 << pinToConfigure.u8Pin);
    pPIO->PIO_ABSR &= ~(0x1 << pinToConfigure.u8Pin);
}


void UARTDue::configure()
{
    configure_IO_alternate_function(arrDuePinPairs[u8Port].TX);
    configure_IO_alternate_function(arrDuePinPairs[u8Port].RX);


    /* Enable clock to USART, first disable it to reset registers */
    PMC->PMC_PCDR0 = (0x1 << (ID_USART0 + u8Port));
    PMC->PMC_PCER0 = (0x1 << (ID_USART0 + u8Port));

    /* Configure stop bits */
    pArrDueUSARTS[u8Port]->US_MR = (eStopBits << (US_MR_NBSTOP_Pos));

    /* Configure parity */
    uint32_t u32ParityBit;
    switch(eParity)
    {
        case PARITY_NONE:
            u32ParityBit = US_MR_PAR_NO;
            break;

        case PARITY_EVEN:
            u32ParityBit = US_MR_PAR_EVEN;
            break;

        case PARITY_ODD:
            u32ParityBit = US_MR_PAR_ODD;
            break;

        default:
            u32ParityBit = 0x0;
            break;
    }

    pArrDueUSARTS[u8Port]->US_MR |= u32ParityBit;

    /* Configure word length */
    pArrDueUSARTS[u8Port]->US_MR |= ( (eWordLength & 0x3) << (US_MR_CHRL_Pos));
    pArrDueUSARTS[u8Port]->US_MR |= ((eWordLength & 0x4) != 0)
                                    ? (US_MR_MODE9) 
                                    : (0);

    /* Calculate Baudrate div */
    pArrDueUSARTS[u8Port]->US_BRGR = (DUE_MAX_CLOCK_SPEED / (u32Baudrate << 4));

    pArrDueUSARTS[u8Port]->US_CR |= US_CR_TXEN | US_CR_RXEN;
}

/* ---------------------------------- END ---------------------------------- */
