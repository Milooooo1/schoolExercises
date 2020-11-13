#include "due-PIO.h"

#include "../../bmptk/targets/cortex/atmel/sam3xa/include/sam3x8c.h"


/* ---------------------- STATIC FUNCTIONS PROTOTYPES ---------------------- */

static void _init_PIO_port(uint8_t au8Port);

static Pio *_get_PIO_pointer(uint8_t au8Port);

/* -------------------- STATIC FUNCTIONS PROTOTYPES END -------------------- */


/* ---------------------------- STATIC VARIABLES --------------------------- */

/* An array of bools indicating whether an IO port has been initialised. */
static uint8_t u8arrInitialised[_DUE_NUMBER_OF_PIO_CONTROLLERS] = {0,0,0,0};

/* -------------------------- STATIC VARIABLES END ------------------------- */


/* ---------------------------- STATIC FUNCTIONS --------------------------- */

static void _init_PIO_port(uint8_t au8Port)
{
    PMC->PMC_PCER0 = 0x1 << (ID_PIOA + au8Port);
    u8arrInitialised[au8Port] = 0x1;
}


static Pio *_get_PIO_pointer(uint8_t au8Port)
{
    return (Pio*)(((uint32_t)PIOA) + (au8Port * 0x200));
}

/* -------------------------- STATIC FUNCTIONS END ------------------------- */


/* --------------------------------- METHODS ------------------------------- */

static void _due_PIO_set_mode(enum GPIO_MODE eMode, unsigned auPort, unsigned auPin)
{
    if(!(u8arrInitialised[auPort]))
    {
        _init_PIO_port(auPort);
    }

    Pio *pPIOPort = _get_PIO_pointer(auPort);
    uint32_t u32PinBit = 0x1 << auPin;

    switch(eMode)
    {
        case GPIO_MODE_PUSH_PULL:
            pPIOPort->PIO_PER = u32PinBit;
            pPIOPort->PIO_OER = u32PinBit;
            pPIOPort->PIO_OWER = u32PinBit;
            break;
        
        case GPIO_MODE_ALTERNATE_MODE:
            pPIOPort->PIO_PDR = u32PinBit;
            pPIOPort->PIO_ABSR &= ~(u32PinBit);
            break;
        
        case GPIO_MODE_FLOATING:
            pPIOPort->PIO_PER = u32PinBit;
            pPIOPort->PIO_ODR = u32PinBit;
            break;

        default:
            break;
    }
}


static void _due_PIO_set_pin(unsigned auPort, unsigned auPin)
{
    _get_PIO_pointer(auPort)->PIO_SODR = 0x1 << auPin;
}


static void _due_PIO_reset_pin(unsigned auPort, unsigned auPin)
{
    _get_PIO_pointer(auPort)->PIO_CODR = 0x1 << auPin;
}


static void _due_PIO_toggle_pin(unsigned auPort, unsigned auPin)
{
    _get_PIO_pointer(auPort)->PIO_ODSR ^= 0x1 << auPin;
}

/* ------------------------------- METHODS END ----------------------------- */


GPIOInterface GPIO_INTERFACE_DUE =
{
    &_due_PIO_set_mode,
    &_due_PIO_set_pin,
    &_due_PIO_reset_pin,
    &_due_PIO_toggle_pin
};
