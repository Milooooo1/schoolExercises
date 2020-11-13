#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "rtos.hpp"

#define DISP_CHAR_WIDTH             8
#define DISP_CHAR_HEIGHT            8

#define DISP_STATUS_X               (DISP_CHAR_WIDTH * 0)
#define DISP_STATUS_Y               (DISP_CHAR_WIDTH * 0)


#define DISP_PLAYER_LIFE_NUM_X      (DISP_CHAR_WIDTH * 1)
#define DISP_PLAYER_LIFE_NUM_Y      (DISP_CHAR_WIDTH * 2)

#define DISP_PLAYER_LIFE_STR_X      (DISP_CHAR_WIDTH * 4)
#define DISP_PLAYER_LIFE_STR_Y      (DISP_CHAR_WIDTH * 2)


#define DISP_TIME_NUM_X             (DISP_CHAR_WIDTH * 1)
#define DISP_TIME_NUM_Y             (DISP_CHAR_WIDTH * 4)

#define DISP_TIME_STR_X             (DISP_CHAR_WIDTH * 4)
#define DISP_TIME_STR_Y             (DISP_CHAR_WIDTH * 4)

/// @file

class Display : public rtos::task<2048>
{
    private:
        hwlib::i2c_bus &refBus;
        hwlib::glcd_oled_i2c_128x64_direct OLED;
        hwlib::font_default_8x8 font;

        rtos::flag renderStartFlag;
        rtos::flag renderEndFlag;
        rtos::channel<uint8_t, 1> renderLifesChannel;
        rtos::channel<uint32_t, 1> renderTimeChannel;

        hwlib::image_invert_t get_char(char cIndex);

        void write_string(hwlib::xy origin, const char* cpStr);

        void _render_lifes(uint8_t au8Lifes);
        void _render_time(uint32_t au32GameTime);
        void _render_start(void);
        void _render_end(void);

        uint8_t u8LifeBuffer = 0;
        uint32_t u32TimeBuffer = 0;

        void main(void) override;

    public:
        /**********************************************//**
        * @brief
        *  Initialises the display
        * @details
        *  Initialises the display, clears it and writes
        *  the basic layout of the info screen.
        *  The basic layout includes all the parts that
        *  remain the same throughout the game.
        **************************************************/
        Display(hwlib::i2c_bus &arefBus);


        /**********************************************//**
        * @brief
        *  Renders the life data
        * @details
        *  Renders the number of lifes left, it only
        *  rewrites the numerical part, the other part is
        *  written to the display by the constructor to 
        *  save CPU time.
        *  It also buffers the value, only rewriting if
        *  necessary to keep CPU time down even further.
        **************************************************/        
        void render_lifes(uint8_t au8Lifes);


        /**********************************************//**
        * @brief
        *  Renders the time data
        * @details
        *  Renders the number of minutes left, it only
        *  rewrites the numerical part, the other part is
        *  written to the display by the constructor to 
        *  save CPU time.
        *  It also buffers the value, only rewriting if
        *  necessary to keep CPU time down even further.
        **************************************************/        
        void render_time(uint32_t au32GameTime);


        /**********************************************//**
        * @brief
        *  Renders the start start, doing a countdown.
        * @details
        *  To keep game logic from starting it is a
        *  blocking operation.
        **************************************************/
        void render_start(void);


        /**********************************************//**
        * @brief
        *  Renders game end
        **************************************************/
        void render_end(void);
};

#endif /* DISPLAY_HPP_ */