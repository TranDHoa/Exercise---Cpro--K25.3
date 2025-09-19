// include header files

#ifndef SENSOR_H
#define SENSOR_H


// local constants



//local data type



// local variables
typedef enum{
    pump_off,
    pump_on
}PUMP;

typedef enum{
    led_normal,
    led_watering,
    led_low_moisture_alert,
    led_error
}LED;

typedef struct{
    float do_am;
    float nhiet_do;
}SENSOR;



// local function prototype
void sensor_init(void);//Khoi tao sensor

void sensor_read(SENSOR *data);//Doc gia tri sensor

void actuators_init(void);

//Dieu khien bom
void GET_PUMP_ON(void);
void GET_PUMP_OFF(void);
PUMP get_pump(void);

//Dieu khien led
void led_set_state(LED trangthai);

#endif