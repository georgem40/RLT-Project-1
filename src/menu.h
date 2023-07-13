#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include "Adafruit_ILI9341.h"

extern Adafruit_ILI9341 tft; 

// default font is 6x8 scaled by textsize

#define rgb(r, g, b) \
   ((0x1f & r) << (5+6) | \
    (0x3f & g) << (5) | \
    (0x1f & b) << (0))

#define DARK_COLOR rgb(0x5, 0x5, 0x5)

class WLabel {
   public:
      uint16_t x:9;
      uint16_t y:9;

      uint16_t sz:4;

      uint8_t w;
      uint8_t h;

      static const uint8_t min_width = 46;

      WLabel(uint8_t  swidth,
            uint16_t x,
            uint16_t y,
            uint8_t  sz = 2,
            uint8_t  min = min_width); 

      void paint(const char *label,
            uint16_t    fg,
            uint16_t    bg) const;

      void paint(const __FlashStringHelper *label,
            uint16_t                   fg,
            uint16_t                   bg) const;

      void paint(uint8_t  m,
            uint16_t fg,
            uint16_t bg) const;

      void paint(uint16_t m,
            uint16_t fg,
            uint16_t bg) const;

      void paint_two_digits(uint8_t m,
            uint16_t fg,
            uint16_t bg) const;

      void paint_four_digits(uint16_t m,
            uint16_t fg,
            uint16_t bg) const;

      bool hit(uint16_t hx, uint16_t hy) const;

      static void paint(const __FlashStringHelper *str,
            uint16_t                   x,
            uint16_t                   y,
            uint16_t                   fg,
            uint16_t                   bg,
            uint8_t                    sz = 2,
            uint8_t                    w = 0,
            uint8_t                    h = 0);

      static void paint(const char *str,
            uint16_t    x,
            uint16_t    y,
            uint16_t    fg,
            uint16_t    bg,
            uint8_t     sz = 2,
            uint8_t     w = 0,
            uint8_t     h = 0);

      static void paint(char     str,
            uint16_t x,
            uint16_t y,
            uint16_t fg,
            uint16_t bg,
            uint8_t sz = 2,
            uint8_t w = 0,
            uint8_t h = 0);

   protected:
      static void paint_common(int      len,
            uint16_t x,
            uint16_t y,
            uint16_t fg,
            uint16_t bg,
            uint8_t  sz,
            uint8_t  w,
            uint8_t  h);

      void paint_common(uint8_t  len,
            uint16_t fg,
            uint16_t bg) const;
};

class WMenuBase {
   public:
      /* paint full window to display */
      virtual void paint() = 0;

      /* ticks every second */
      virtual void tick() { };

      /* handle touchscreen press */
      virtual void touch(uint16_t x, uint16_t y) = 0;
};

class WMainMenu : public WMenuBase {
      virtual void paint();
      virtual void tick();
      virtual void touch(uint16_t x, uint16_t y);
};

extern WMainMenu main_menu;

class WSetupMenu : public WMenuBase {     
      virtual void paint();
      virtual void tick();
      virtual void touch(uint16_t x, uint16_t y);
};

extern WSetupMenu setup_menu;

class WRunMenu : public WMenuBase {
      virtual void paint();
      virtual void tick();
      virtual void touch(uint16_t x, uint16_t y);
};

extern WRunMenu run_menu;


#endif /* MENU_H */
