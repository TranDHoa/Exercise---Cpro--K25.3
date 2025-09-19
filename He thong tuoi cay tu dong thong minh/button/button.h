// include header files

#ifndef BUTTON_H
#define BUTTON_H


// local constants



//local data type



// local variables


// local function prototype



// global function definition
typedef enum{
    button_toggle,
    button_on,
    button_off
}BUTTON;

void button_init(void);
void get_button_on(void);
void get_button_off(void);
BUTTON get_button(void);
void toggle_button(void);

#endif