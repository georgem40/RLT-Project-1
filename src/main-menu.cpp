#include "menu-system.h"
#include "utility.h"

static WLabel setup_button(6, 20, 160, 3, 55);
static WLabel start_button(8, 155, 130, 3, 85);
static WLabel red_intensity(2, 100, 20, 3);
static WLabel IR_intensity(2, 240, 20, 3);
static WLabel timer_counter(2, 153, 70, 4);

uint8_t  red_intensity_val, IR_intensity_val, time_on_timer;
uint8_t  prev_red_intensity_val, prev_IR_intensity_val, prev_time_on_timer;
uint16_t time_on_timer_in_seconds = 0;
uint16_t countdown_time_in_seconds = 0;

unsigned int countdown_prev_time = 0;

void WMainMenu::tick()
{
   send_intensity(0, 0);
}

void WMainMenu::paint()
{
   WLabel::paint(F("RED "),   40, 20, ILI9341_RED, ILI9341_BLACK, 3);
   WLabel::paint(F("IR "),   190, 20, ILI9341_WHITE, ILI9341_BLACK, 3);

   red_intensity.paint_two_digits(red_intensity_val, ILI9341_RED, ILI9341_BLACK);
   IR_intensity.paint_two_digits(IR_intensity_val, ILI9341_WHITE, ILI9341_BLACK);

   WLabel::paint(F("TIMER: "), 10, 70, ILI9341_WHITE, ILI9341_BLACK, 4);

   timer_counter.paint_two_digits(time_on_timer, ILI9341_WHITE, ILI9341_BLACK);

   WLabel::paint(F("Mins"), 210, 70, ILI9341_WHITE, ILI9341_BLACK, 4);

   setup_button.paint(F("SETUP"), ILI9341_BLACK, ILI9341_ORANGE);
   start_button.paint(F("START"), ILI9341_BLACK, ILI9341_GREEN);
}

void WMainMenu::touch(uint16_t x, uint16_t y)
{
   if(setup_button.hit(x, y))
      menu.setMenu(setup_menu);
   if(start_button.hit(x, y) && time_on_timer != 0)
   {
      countdown_prev_time = millis();
      time_on_timer_in_seconds = time_on_timer * 60;
      menu.setMenu(run_menu);
   }
}
