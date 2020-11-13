#include "ReceiveIRMessageControl.hpp"

#define DEBUG
#include "log.hpp"

/* -------------------------------- CONSTRUCTOR ---------------------------- */

ReceiveIRMessageControl::ReceiveIRMessageControl(
    RunGameControl& refRunGameControl,
    hwlib::pin_in& refReceiver
    ) :
    task("Receive IR message control"),
    tim0(this, "timer 0"),
    refRunGameControl(refRunGameControl),
    refReceiver(refReceiver),
    eCurrState(RECV_STATE_IDLE),
    bLastState(0),
    u16LastMSG(0),
    uNumReceived(0)
    {}

/* ------------------------------ CONSTRUCTOR END -------------------------- */


/* ------------------------------ PRIVATE METHODS -------------------------- */

uint16_t ReceiveIRMessageControl::extract_data_from_FIFO(void)
{
    uint16_t u16Data = 0;

    for(int i = 15; i >= 0; i--)
    {
        /* bit consists of two pieces of timedata, high and low */
        timeData bit[2] = {*timeFIFO.read(), *timeFIFO.read()};

        /* high first then low */
        if(bit[0].u16Period > bit[1].u16Period)
        {
            u16Data |= 0x1 << i;
        }
    }

    LOG("RECEIVED_DATA: ");
    LOG(u16Data);

    return u16Data;
}


uint8_t ReceiveIRMessageControl::compute_checksum(uint16_t au16Data)
{
    return (uint8_t)(((au16Data >> 1) & 0x1F)^((au16Data >> 6) & 0x1F));
}


uint8_t ReceiveIRMessageControl::extract_checksum(uint16_t au16Data)
{
    return (uint8_t)(au16Data >> 11);
}

/* ---------------------------- PRIVATE METHODS END ------------------------ */


/* ------------------------------ STATE HANDLERS --------------------------- */

ReceiveIRMessageControl::RECV_STATE ReceiveIRMessageControl::idle_handler(void)
{
    timeFIFO.purge();
    
    tim0.set(200);
    wait(tim0);

    RECV_STATE eStateToReturn;
    
    bLastState = !(refReceiver.read());
    if(bLastState == true)
    {
        uNumReceived = 0;
        uNumCycles = 1;
     
        eStateToReturn = RECV_STATE_RECEIVE;    
    }
    else
    {
        eStateToReturn = RECV_STATE_IDLE;    
    }
    
    return eStateToReturn;
}


ReceiveIRMessageControl::RECV_STATE ReceiveIRMessageControl::receive_handler(void)
{
    tim0.set(200);

    RECV_STATE eStateToReturn;

    if(uNumReceived == 31)
    {
        /* LSB is start bit write zero data */
        timeFIFO.push_back({0, 1});

        eStateToReturn = RECV_STATE_IDLE;
        
        uint16_t u16RawData = extract_data_from_FIFO();
        u8CheckSum = compute_checksum(u16RawData);
        if(u8CheckSum == extract_checksum(u16RawData))
        {
            if(u16LastMSG != u16RawData)
            {
                u16LastMSG = u16RawData;
                refRunGameControl.hit({(uint8_t)((u16RawData & (0x1F << 1)) >> 1), (uint8_t)((u16RawData & (0x1F << 6)) >> 6)});
                /* We won't receive any data for the next 3ms
                according to protocol. */
                hwlib::wait_ms(50);
                u16LastMSG = 0x0000;
            }
            else
            {
                LOG("FAULTY MESSAGE RECEIVED, duplicate");
            }
        }
        else
        {
            LOG("FAULTY MESSAGE RECEIVED, checksum error.");
        }
    }
    else if(uNumCycles == 20)
    {
        eStateToReturn = RECV_STATE_IDLE;
        bLastState = 0;
    
        LOG("FAULTY MESSAGE RECEIVED, timed out");
    }
    else
    {
        eStateToReturn = RECV_STATE_RECEIVE;
        wait(tim0);

        bool bState = !(refReceiver.read());
        if(bState != bLastState)
        {
            timeFIFO.push_back({bLastState, (uint16_t)uNumCycles});
            bLastState = bState;

            uNumCycles = 0;
            uNumReceived++;
        }
        else
        {
            uNumCycles++;
        }
    }
    
    return eStateToReturn;
}
/* TODO: it might be benificial to reduce the complexity of this function
            that also requires the documentation to be reworked. */

/* ---------------------------- STATE HANDLERS END ------------------------- */


/* ------------------------------ STATE_MACHINE ---------------------------- */

void ReceiveIRMessageControl::main(void)
{
    LOG("RECEIVER STARTED");

    RECV_STATE eNextState;

    while(1)
    {
        switch(eCurrState)
        {
            case RECV_STATE_IDLE:
                eNextState = idle_handler();
                break;
            
            case RECV_STATE_RECEIVE:
                eNextState = receive_handler();
                break;

            default:
                break;
        }

        eCurrState = eNextState;
    }
}

/* ---------------------------- STATE_MACHINE END -------------------------- */

