#include <Arduino.h>
#include "Adafruit_ILI9341.h"
#include "Adafruit_FT6206.h"
#include "menu-system.h"
#include "touch-debounce.h"
#include "utility.h"

// how frequent each menu should update itself (ms)
#define MENU_UPDATE_FREQUENCY 30
unsigned long prev_time;

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

// Debouncing for the touch screen controller
TouchDebounce debouncer;

// The menu controller
MenuSystem menu;

void setup(void)
{
   Serial.begin(115200);
   tft.begin();
   debouncer.begin();
   init_lights_serial();

   // get saved intensity and time settings
   fetch_settings();

   if (!ctp.begin(40))
   {
      Serial.println(F("ERR: unable to start touchscreen."));
   } 

   // origin = left,top landscape (USB left upper)
   tft.setRotation(3); 
   menu.begin();  // sets the main menu as the screen menu

   prev_time = millis();
}

void loop()
{
   // update the current menu
   if(millis() - prev_time >= MENU_UPDATE_FREQUENCY)
   {
      prev_time = millis();
      menu.tick();
   }

  // check for LCD touches
   if (ctp.touched())
   {
      TS_Point p1 = ctp.getPoint();
      delay( 10 );
      TS_Point p2 = ctp.getPoint();

      int16_t x1 = p1.x;
      int16_t y1 = p1.y;
      int16_t x2 = p2.x;
      int16_t y2 = p2.y;
      int16_t temp;

      // map to the display configuration
      temp = map(y1, 0, 320, 320, 0);
      y1   = map(x1, 0, 240, 0, 240);
      x1   = temp;

      temp = map(y2, 0, 320, 320, 0);
      y2   = map(x2, 0, 240, 0, 240);
      x2   = temp;

#ifdef ROTATE_DISPLAY
      // map back to the Adafruit FT6206 display configuration
      x1 = map(x1, 0, 320, 320, 0);
      y1 = map(y1, 0, 240, 240, 0);

      x2 = map(x2, 0, 320, 320, 0);
      y2 = map(y2, 0, 240, 240, 0);
#endif

      debouncer.hit(x1, y1, x2, y2);
   } else {
      debouncer.nohit();
   }

   if (debouncer.touched()) {
      menu.touch(debouncer.x(), debouncer.y());
   }
}