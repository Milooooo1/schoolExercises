#include "hwlib.hpp"

constexpr double radians_from_degrees(int degrees){
    return 2 * 3.14 * (degrees / 360.0);
}

constexpr double pow(double g, int n){
    double result = 1;
    while( n > 0){
        result *= g;
        --n;
    }
    return result;
}

constexpr double fac(int n){
    double result = 1;
    while(n > 0){
        result *= n;
        --n;
    }
    return result;
}

constexpr double sin(double a){
    return 
        a
        - pow(a, 3) / fac(3)
        + pow(a, 5) / fac(5)
        - pow(a, 7) / fac(7)
        + pow(a, 9) / fac(9)
        - pow(a, 11) / fac(11)
        + pow(a, 13) / fac(13);
}

constexpr double cos(double a){
    return 
        1
        - pow(a, 2) / fac(2)
        + pow(a, 4) / fac(4)
        - pow(a, 6) / fac(6)
        + pow(a, 8) / fac(8)
        - pow(a, 10) / fac(10)
        + pow(a, 12) / fac(12);
}

constexpr int calculate_y_from_sin(int degree){
    return (16 * sin(radians_from_degrees(degree - 90)));           //
}

constexpr int calculate_x_from_cos(int degree){
    return (16 * cos(radians_from_degrees(degree - 90)));
}

int main(void){
    auto scl        = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda        = hwlib::target::pin_oc( hwlib::target::pins::sda );                                                                                                                                                              
    auto i2c_bus    = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );                                                                                                                                                                  
    auto w          = hwlib::glcd_oled( i2c_bus, 0x3c ); 

    
    constexpr int sinTable[60] = {
        calculate_y_from_sin(0),
        calculate_y_from_sin(6),
        calculate_y_from_sin(12),
        calculate_y_from_sin(18),
        calculate_y_from_sin(24),
        calculate_y_from_sin(30),
        calculate_y_from_sin(36),
        calculate_y_from_sin(42),
        calculate_y_from_sin(48),
        calculate_y_from_sin(54),
        calculate_y_from_sin(60),
        calculate_y_from_sin(66),
        calculate_y_from_sin(72),
        calculate_y_from_sin(78),
        calculate_y_from_sin(84),
        calculate_y_from_sin(90),
        calculate_y_from_sin(96),
        calculate_y_from_sin(102),
        calculate_y_from_sin(108),
        calculate_y_from_sin(114),
        calculate_y_from_sin(120),
        calculate_y_from_sin(126),
        calculate_y_from_sin(132),
        calculate_y_from_sin(138),
        calculate_y_from_sin(144),
        calculate_y_from_sin(150),
        calculate_y_from_sin(156),
        calculate_y_from_sin(162),
        calculate_y_from_sin(168),
        calculate_y_from_sin(174),
        calculate_y_from_sin(180),
        calculate_y_from_sin(186),
        calculate_y_from_sin(192),
        calculate_y_from_sin(198),
        calculate_y_from_sin(204),
        calculate_y_from_sin(210),
        calculate_y_from_sin(216),
        calculate_y_from_sin(222),
        calculate_y_from_sin(228),
        calculate_y_from_sin(234),
        calculate_y_from_sin(240),
        calculate_y_from_sin(246),
        calculate_y_from_sin(252),
        calculate_y_from_sin(258),
        calculate_y_from_sin(264),
        calculate_y_from_sin(270),
        calculate_y_from_sin(276),
        calculate_y_from_sin(282),
        calculate_y_from_sin(288),
        calculate_y_from_sin(294),
        calculate_y_from_sin(300),
        calculate_y_from_sin(306),
        calculate_y_from_sin(312),
        calculate_y_from_sin(318),
        calculate_y_from_sin(324),
        calculate_y_from_sin(330),
        calculate_y_from_sin(336),
        calculate_y_from_sin(342),
        calculate_y_from_sin(348),
        calculate_y_from_sin(354)
    };
    constexpr int cosTable[60] = {
        calculate_x_from_cos(0),
        calculate_x_from_cos(6),
        calculate_x_from_cos(12),
        calculate_x_from_cos(18),
        calculate_x_from_cos(24),
        calculate_x_from_cos(30),
        calculate_x_from_cos(36),
        calculate_x_from_cos(42),
        calculate_x_from_cos(48),
        calculate_x_from_cos(54),
        calculate_x_from_cos(60),
        calculate_x_from_cos(66),
        calculate_x_from_cos(72),
        calculate_x_from_cos(78),
        calculate_x_from_cos(84),
        calculate_x_from_cos(90),
        calculate_x_from_cos(96),
        calculate_x_from_cos(102),
        calculate_x_from_cos(108),
        calculate_x_from_cos(114),
        calculate_x_from_cos(120),
        calculate_x_from_cos(126),
        calculate_x_from_cos(132),
        calculate_x_from_cos(138),
        calculate_x_from_cos(144),
        calculate_x_from_cos(150),
        calculate_x_from_cos(156),
        calculate_x_from_cos(162),
        calculate_x_from_cos(168),
        calculate_x_from_cos(174),
        calculate_x_from_cos(180),
        calculate_x_from_cos(186),
        calculate_x_from_cos(192),
        calculate_x_from_cos(198),
        calculate_x_from_cos(204),
        calculate_x_from_cos(210),
        calculate_x_from_cos(216),
        calculate_x_from_cos(222),
        calculate_x_from_cos(228),
        calculate_x_from_cos(234),
        calculate_x_from_cos(240),
        calculate_x_from_cos(246),
        calculate_x_from_cos(252),
        calculate_x_from_cos(258),
        calculate_x_from_cos(264),
        calculate_x_from_cos(270),
        calculate_x_from_cos(276),
        calculate_x_from_cos(282),
        calculate_x_from_cos(288),
        calculate_x_from_cos(294),
        calculate_x_from_cos(300),
        calculate_x_from_cos(306),
        calculate_x_from_cos(312),
        calculate_x_from_cos(318),
        calculate_x_from_cos(324),
        calculate_x_from_cos(330),
        calculate_x_from_cos(336),
        calculate_x_from_cos(342),
        calculate_x_from_cos(348),
        calculate_x_from_cos(354)
    };

    hwlib::xy middlePoint = {64, 31};
    const int radius = 31;
    int position = 0;
    int positionMinutes = 0;
    int positionHours = 0;
    int time = 0 / 10000000;
    int count = hwlib::now_us();

    for(;;){    
        
        hwlib::wait_ms(850);
        w.clear();

        hwlib::circle(middlePoint, radius, hwlib::white).draw(w);
        hwlib::circle(middlePoint, 2, hwlib::white).draw(w);
        hwlib::line(middlePoint, (middlePoint + hwlib::xy(cosTable[position], sinTable[position])*2)).draw(w);
        hwlib::line(middlePoint, (middlePoint + hwlib::xy(cosTable[positionMinutes], sinTable[positionMinutes])*2)).draw(w);
        hwlib::line(middlePoint, middlePoint + hwlib::xy(cosTable[positionHours], sinTable[positionHours])).draw(w);
            
        w.flush();
            
        position = time;
        time += (count - (count - 1.0));
        if(time == 59){
            positionMinutes++;
            time = 0;
        } else if(positionMinutes == 59){
            positionMinutes = 0;
            positionHours++;
        } else if(positionHours == 59){
            positionHours = 0;
        }
        
    } // end of main loop

} // end of main