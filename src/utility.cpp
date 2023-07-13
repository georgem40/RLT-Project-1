#include "menu-system.h"
#include "EEPROM.h"

// serial port used to send light commands
#define Lights Serial1

// serial output buffer
static char buffer[32];

void save_settings()
{
    EEPROM.write(0, time_on_timer);
    EEPROM.write(1, red_intensity_val);
    EEPROM.write(2, IR_intensity_val);
}

void fetch_settings()
{
   time_on_timer = EEPROM.read(0);
   red_intensity_val = EEPROM.read(1);
   IR_intensity_val = EEPROM.read(2);

   if(time_on_timer > 30)
      time_on_timer = 0;
   if(red_intensity_val > 99)
      red_intensity_val = 0;
   if(IR_intensity_val > 99)
      IR_intensity_val = 0;
}

void init_lights_serial()
{
    Lights.begin(1200);
}

void send_intensity(uint8_t red, uint8_t IR)
{
    snprintf(buffer, sizeof(buffer), "ABC..NextLevel:%d:%d:%d:00\r\n", red, IR, 0);
    Lights.print(buffer);
}




