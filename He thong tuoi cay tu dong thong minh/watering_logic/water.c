#include<stdio.h>
#include<time.h>
#include "water.h"
#include "config.h"
#include "sensor.h"
#include "button.h"
static unsigned long start_time = 0;
static unsigned long current_time(void){
    return (unsigned long) time(NULL);
} 

void watering_start_time(config *cfg){
    start_time = 0;
}

void watering_logic_auto(config *cfg,SENSOR *data)
{
    
    if(cfg.mode != mode_auto) return;

    if(cfg.mode == mode_auto && data->do_am < cfg->nguong_bat_bom){
        get_button_on();
        GET_PUMP_ON();
        led_set_state(led_watering);
        printf("Thoi gian bat dau chay la: %lu",time(NULL));
        start_time = current_time();
    }

    if(get_pump() == pump_on) {
        unsigned long running_time = current_time() - start_time; 
        if(cfg.mode == mode_auto && data->do_am >= cfg->nguong_tat_bom && running_time > cfg->tuoi_toi_da){
            printf("Thoi gian dung chay la : %lu",time(NULL));
            get_button_off();
            GET_PUMP_OFF();
            led_set_state(led_normal);
        } 
    }
}

void watering_logic_manual(config *cfg)
{
    unsigned long end_time = current_time + 60; 
    if(cfg->mode != mode_manual) return;

    if(cfg->mode == mode_manual) { 
        printf("Thoi gian bat dau chay la :%lu",time(NULL));
        get_button_on();
        GET_PUMP_ON();
        led_set_state(led_watering);
        do{
            print("Thoi gian dung chay la :%lu",time(NULL));
        }   
        while(time(NULL) < end_time);
        GET_PUMP_OFF();
        led_set_state(led_normal);
    }
}
//chuyen che do tuoi
void watering_toggle(config *cfg,SENSOR *data){
    btn = get_button();
    if(btn == button_toggle){
        toggle_button();
        if(cfg->mode == mode_manual){
        watering_logic_manual(cfg);
        }
        else{
            watering_logic_auto(cfg,data);
        }
    }    
}
