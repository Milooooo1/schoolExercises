#include "display.hpp"

#define DEBUG
#include "log.hpp"

/* ------------------------------ Constructor ------------------------------ */

Display::Display(hwlib::i2c_bus &arefBus)
    :
    task("name"),
    refBus(arefBus),
    OLED(refBus),
    renderStartFlag(this),
    renderEndFlag(this),
    renderLifesChannel(this),
    renderTimeChannel(this)
    {
        OLED.clear();

        write_string(
            {DISP_STATUS_X, DISP_STATUS_Y},
            "Not running"
        );

        write_string(
            {DISP_PLAYER_LIFE_STR_X, DISP_PLAYER_LIFE_STR_Y}, 
            "Hitpoints"
        );

        write_string(
            {DISP_TIME_STR_X, DISP_TIME_STR_Y},
            "Min left"
        );


        LOG("Display initialized");
    }

/* ---------------------------- Constructor end ---------------------------- */


/* --------------------------- Private methods ----------------------------  */

hwlib::image_invert_t Display::get_char(char cIndex)
{
    return hwlib::invert(font[cIndex]);
}


void Display::write_string(hwlib::xy origin, const char* cpString)
{
    uint8_t u8Counter = 0;

    while(*cpString != 0x00)
    {
        OLED.write(
            {
                origin.x + DISP_CHAR_WIDTH * u8Counter++,
                origin.y
            },
            get_char(*cpString++)
            );
    }
}


void Display::_render_lifes(uint8_t au8Lifes)
{
    if(au8Lifes == u8LifeBuffer)
        return;

    u8LifeBuffer = au8Lifes;

    OLED.write(
        {DISP_PLAYER_LIFE_NUM_X, DISP_PLAYER_LIFE_NUM_Y},
        get_char(0x30 + au8Lifes / 10)
    );

    OLED.write(
        {DISP_PLAYER_LIFE_NUM_X + DISP_CHAR_WIDTH, DISP_PLAYER_LIFE_NUM_Y},
        get_char(0x30 + au8Lifes % 10)
    );
}


void Display::_render_time(uint32_t au32GameTime)
{
    if((au32GameTime / 60) == (u32TimeBuffer / 60))
        return;
    
    u32TimeBuffer = au32GameTime;

    uint32_t u32MinLeft = au32GameTime / 60;

    OLED.write(
        {DISP_TIME_NUM_X, DISP_TIME_NUM_Y},
        get_char(0x30 + u32MinLeft / 10)
    );

    OLED.write(
        {DISP_TIME_NUM_X + DISP_CHAR_WIDTH, DISP_TIME_NUM_Y},
        get_char(0x30 + u32MinLeft % 10)
    );

}


void Display::_render_start(void)
{
    write_string(
            {DISP_STATUS_X, DISP_STATUS_Y},
            "5  "
        );
    hwlib::wait_ms_busy(1000);
    write_string(
            {DISP_STATUS_X, DISP_STATUS_Y},
            "4"
        );
    hwlib::wait_ms_busy(1000);

    write_string(
        {DISP_STATUS_X, DISP_STATUS_Y},
        "3"
    );
    hwlib::wait_ms_busy(1000);

    write_string(
        {DISP_STATUS_X, DISP_STATUS_Y},
        "2"
    );
    hwlib::wait_ms_busy(1000);

    write_string(
        {DISP_STATUS_X, DISP_STATUS_Y},
        "1"
    );
    hwlib::wait_ms_busy(1000);
    
    write_string(
        {DISP_STATUS_X, DISP_STATUS_Y},
        " "
    );
}


void Display::_render_end(void)
{
    write_string(
            {DISP_STATUS_X, DISP_STATUS_Y},
            "Not"
        );
}


void Display::main(void)
{
    while(1)
    {
        rtos::event event = wait(   renderStartFlag + 
                                    renderEndFlag + 
                                    renderLifesChannel +
                                    renderTimeChannel
                                );

        if(event == renderStartFlag)
        {
            _render_start();
        }
        else if(event == renderEndFlag)
        {
            _render_end();
        }
        else if(event == renderLifesChannel)
        {
            _render_lifes(renderLifesChannel.read());
        }
        else
        {
            _render_time(renderTimeChannel.read());
        }
        
    }
}

/* ------------------------- Private methods end --------------------------  */


/* --------------------------- Public methods -----------------------------  */

void Display::render_lifes(uint8_t au8Lifes)
{
    renderLifesChannel.write(au8Lifes);
}


void Display::render_time(uint32_t au32GameTime)
{
    renderTimeChannel.write(au32GameTime);
}


void Display::render_start(void)
{
    renderStartFlag.set();
}


void Display::render_end(void)
{
    renderEndFlag.set();
}

/* --------------------------- Public methods -----------------------------  */

