// include header files

#ifndef WATER_H
#define WATER_H

#include "config.h"
#include "sensor.h"

// local constants



//local data type



// local variables



// local function prototype
void watering_start_time(config *cfg)

void watering_logic_auto(config *cfg,SENSOR *data);

void watering_logic_manual(config *cfg);

void watering_toggle(config *cfg,SENSOR *data);






// global function definition

#endif