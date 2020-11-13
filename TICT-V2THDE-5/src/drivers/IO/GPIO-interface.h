#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


enum GPIO_MODE 
{   
    GPIO_MODE_PUSH_PULL, 
    GPIO_MODE_ALTERNATE_MODE, 
    GPIO_MODE_FLOATING
};


typedef struct
{
    /**************************************************//**
    * @brief
    *  Configures a specific pin.
    * @details
    *  This function configures a specific pin.
    *  The function is also responsible for enabeling the
    *  clock to the IO port and configuring the port.
    * @param[in] aeMode Mode to put pin into, 
    *             see enum GPIO_MODE.
    * @param[in] auPort Port of pin.
    * @param[in] auPin Pin number.
    ******************************************************/
    void (*set_mode)(enum GPIO_MODE aeMode, unsigned auport, unsigned auPin);
    

    /**************************************************//**
    * @brief
    *  Sets pin high.
    * @param[in] auPort Port of pin.
    * @param[in] auPin Pin number.
    ******************************************************/
    void (*set_pin)(unsigned auPort, unsigned auPin);


    /**************************************************//**
    * @brief
    *  Sets pin low.
    * @param[in] auPort Port of pin.
    * @param[in] auPin Pin number.
    ******************************************************/
    void (*reset_pin)(unsigned auPort, unsigned auPin);


    /**************************************************//**
    * @brief
    *  Toggles pin.
    * @param[in] auPort Port of pin.
    * @param[in] auPin Pin number.
    ******************************************************/
    void (*toggle_pin)(unsigned auPort, unsigned auPin);
} GPIOInterface;


#endif /* GPIO_INTERFACE_H_ */