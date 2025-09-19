// include header files

#ifndef CONFIG_H
#define CONFIG_H


// local constants



//local data type



// local variables



// local function prototype
typedef enum{
    mode_auto,
    mode_manual
}system_mode;


typedef struct{
    float nguong_bat_bom;//do am
    float nguong_tat_bom;
    unsigned long tuoi_toi_da;// thoi gian tuoi toi da
    unsigned long kiem_tra; // thoi gian kiem tra cam bien
    system_mode mode;
}config;

#endif