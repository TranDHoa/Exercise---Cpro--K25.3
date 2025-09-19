#include<stdio.h>
#include "button.h"
#include "config.h"
#include "sensor.h"


static system_mode mode_state = mode_auto;
static BUTTON button_state = button_off;

void button_init(void){
    button_state = button_off;
}
void get_button_on(void){
    button_state = button_on;
    printf("Cong tac dang bat");
}
void get_button_off(void){
    button_state = button_off;
    printf("Cong tac dang tat");
}

BUTTON get_button(void)
{
    return button_state;
}

void toggle_button(void)
{
    if(mode_state == mode_auto){
        GET_PUMP_OFF();
        mode_state = mode_manual;
    }
    else{
        mode_state = mode_auto;
    }
}
