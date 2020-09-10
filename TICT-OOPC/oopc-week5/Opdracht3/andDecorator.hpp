#include "hwlib.hpp"

class and_pin_ins : public hwlib::pin_in {
    private:
    hwlib::target::pin_in & slave1;
    hwlib::target::pin_in & slave2;

    public:
    and_pin_ins(hwlib::target::pin_in & slave1, hwlib::target::pin_in & slave2){
        slave1 ( slave1 ),
        slave2 ( slave2 )
    }

    bool read() override {
        if( slave1.read() && slave2.read() ){
            return true;
        } else {
            return false;
        }
    }

    void refresh() override {
        slave1.refresh();
        slave2.refresh();
    }
}