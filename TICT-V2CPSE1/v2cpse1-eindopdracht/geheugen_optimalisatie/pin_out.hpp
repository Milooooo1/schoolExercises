/// pin_out implementation for a ATSAM3X8E
class pin_out : public hwlib::pin_out {
private:
   Pio & port;
   uint32_t mask;
   
public:

   /// Arduino Due pin_out constructor
   /// 
   /// Constructor for a ATSAM3X8E input pin.
   ///
   /// The port_number and pin_number refer to the chip, 
   /// not to the Arduino board pin names.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( uint32_t port_number, uint32_t pin_number ): 
      port{ port_registers( port_number ) }, 
      mask{ 0x1U << pin_number }
   {
      port.PIO_OER  = mask; 
   }
   
   /// Arduino Due pin_out constructor from a Due pin name
   /// 
   /// This call creates a pin_out from an Arduino Due pin name.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( pins name ): 
      pin_out{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}     
   
   void HWLIB_INLINE write( bool v ) override {
      ( v 
         ?  port.PIO_SODR 
         :  port.PIO_CODR 
      )  = mask;
   }

   void HWLIB_INLINE flush() override {}

};