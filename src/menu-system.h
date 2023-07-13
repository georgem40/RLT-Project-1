#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "menu.h"

class MenuSystem
{
   public:
      void setMenu(WMenuBase& menu);
      void prevMenu(void);
      // void paintChangeControls(bool back=false) const;
      bool isMainMenu() const;

      inline void begin(void)
      {
         setMenu( main_menu );
      }

      inline void tick()
      {
         current->tick();
      }

      inline void touch(uint16_t x, uint16_t y)
      {
         current->touch(x, y);
      }

   private:
      WMenuBase *current;
      WMenuBase *previous;
};

extern MenuSystem menu;
extern uint8_t red_intensity_val, IR_intensity_val, time_on_timer;
extern uint8_t prev_red_intensity_val, prev_IR_intensity_val, prev_time_on_timer;
extern uint16_t time_on_timer_in_seconds, countdown_time_in_seconds;
extern unsigned int countdown_prev_time;

#endif /* MENU_SYSTEM_H */
