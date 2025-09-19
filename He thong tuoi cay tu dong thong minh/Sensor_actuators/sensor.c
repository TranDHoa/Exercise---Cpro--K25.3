#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sensor.h"

static PUMP pump_state = pump_off;
static LED led_state = led_normal;


void sensor_init(void) {
    srand(time(NULL));
    printf("[SENSORS] Da duoc khoi tao\n");
}

// mo phong cam bien
void sensor_read(SENSOR *data)
{
    float delta = (rand() % 21) - 10;
    data->do_am += delta;  
    if(data->do_am < 0) data->do_am = 0;
    if(data->do_am > 100) data->do_am = 100;

    data->nhiet_do += (delta/10);
    printf("Do am la: %f", data->do_am);
    printf("Nhiet do la: %f",data->nhiet_do);

}

void actuators_init(void)
{
    pump_state = pump_off;
    led_state = led_normal;

}

void GET_PUMP_ON(void)
{
    pump_state = pump_on;
    printf("May bom dang o che do: ON");
}

void GET_PUMP_OFF(void)
{
    pump_state = pump_off;
    printf("May bom dang o che do: OFF");
}

PUMP get_pump(void)
{
    return pump_state;
}

void led_set_state(LED trangthai)
{
    led_state = trangthai;
}
