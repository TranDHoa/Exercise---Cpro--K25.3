// include header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "water.h"
#include "sensor.h"
#include "config.h"
#include "button.h"



// local constants

//local data type

// local variables

// local function prototype
// global function definition
int main(void)
{
    config cfg;
    cfg.nguong_bat_bom = 20;
    cfg.nguong_tat_bom = 90;
    cfg.kiem_tra = 30;
    cfg.tuoi_toi_da = 120;
    cfg.mode = mode_auto;

    SENSOR sensor;
    sensor.do_am = 80;
    sensor.nhiet_do = 25;
    
    button_init();
    sensor_init();
    actuators_init();
    watering_start_time(&cfg);

    while(1){
        sensor_read(&sensor);
        BUTTON button_state = get_button();
        if(button_state == button_toggle){
            watering_toggle(&cfg,&sensor);
        }
        if(button_state == button_on) return 0;
        else
        {
            if(cfg.mode == mode_auto){
                watering_logic_auto(&cfg,&sensor);      
            }
            else watering_logic_manual(&cfg);
        }
    }
    return 0;
}


