#ifndef TOUCH_DEBOUNCE_H
#define TOUCH_DEBOUNCE_H

#include <stdint.h>

#define MAX_INDEX 4

class TouchDebounce
{
   public:
      void begin( void );
      void hit(int16_t x, int16_t y);
      void hit(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
      void nohit( void );

      bool touched( void );
      bool long_hit( void );
      int  x( void );
      int  y( void );

   private:
      bool last_hit;
      bool did_touch;
      int last_x;
      int last_y;

      int16_t index;
      int16_t accum_x[MAX_INDEX], accum_y[MAX_INDEX];
};

#endif /* TOUCH_DEBOUNCE_H */
