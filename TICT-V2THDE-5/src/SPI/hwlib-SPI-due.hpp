#ifndef HWLIB_SPI_DUE_HPP_
#define HWLIB_SPI_DUE_HPP_

#include "../../hwlib/library/hwlib.hpp"
#include "../bmptk/targets/cortex/atmel/sam3xa/include/sam3x8e.h"

namespace due
{
    class SPI
    {
        private:
            uint8_t u8ReceivedData;

            void GPIO_setup()
            {
                /* Enable clock PA25(MISO), PA27(SPCK), PA28(SPI0_NPCS0)*/
                PMC->PMC_PCER0 |= PMC_PCER0_PID11;

                //PIOA->PIO_WPMR = PIO_WPMR_WPKEY;
                
                PIOA->PIO_PDR |= (PIO_PER_P25 | PIO_PER_P26 | 
                    PIO_PER_P27 | PIO_PER_P28 | PIO_PER_P29);
                PIOA->PIO_ABSR &= ~(PIO_PER_P25 | PIO_PER_P26 | 
                    PIO_PER_P27 | PIO_PER_P28 | PIO_PER_P29);
                PIOA->PIO_PUDR = PIO_PUDR_P25;
            }


            void SPI_setup()
            {
                /* Enable clock */
                PMC->PMC_PCER0 |= PMC_PCER0_PID24;

                SPI0->SPI_MR = SPI_MR_MSTR | SPI_MR_PCS(1);
                SPI0->SPI_CSR[1] = ((0x10 << SPI_CSR_SCBR_Pos) | SPI_CSR_NCPHA);
                SPI0->SPI_CR = SPI_CR_SPIEN;
            }


            SPI(void)
            {
                GPIO_setup();
                SPI_setup();
            }


        public:
            static SPI &instance(void)
            {
                static SPI SPIInstance;

                return SPIInstance;
            }


            bool tdr_empty(void)
            {
                return ((SPI0->SPI_SR & SPI_SR_TDRE) != 0);
            }


            void write_byte(uint8_t u8Data)
            {
                while((SPI0->SPI_SR & SPI_SR_TDRE) == 0);

                SPI0->SPI_TDR = u8Data;
            }


            void write_multiple(uint8_t *u8pData, uint8_t u8Len)
            {
                while(u8Len-- > 0)
                {
                    while((SPI0->SPI_SR & SPI_SR_TDRE) == 0);
                    
                    SPI0->SPI_TDR = *u8pData++;
                }

                while((SPI0->SPI_SR & SPI_SR_TXEMPTY) == 0);
            }    
            
            uint8_t read_byte(void)
            {
                while((SPI0->SPI_SR & SPI_SR_TXEMPTY) == 0);
                return (SPI0->SPI_RDR & 0xFF);
            }
    };
}

#endif /* HWLIB_SPI_DUE_HPP_ */