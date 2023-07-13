#include "menu-system.h"
#include "utility.h"

static WLabel save_button(7, 95,  170, 3, 55);

static WLabel red_input_buttons_bg(9, 80, 10, 4);
static WLabel red_down_slow(2, 82, 12, 1, 42);
static WLabel red_down_fast(2, 126, 12, 3, 42);
static WLabel red_up_slow(2, 262, 12, 1, 42);
static WLabel red_up_fast(2, 218, 12, 3, 42);
static WLabel set_red_intensity(2, 170, 10, 3);

static WLabel IR_input_buttons_bg(9, 80, 60, 4);
static WLabel IR_down_slow(2, 82, 62, 1, 42);
static WLabel IR_down_fast(2, 126, 62, 3, 42);
static WLabel IR_up_slow(2, 262, 62, 1, 42);
static WLabel IR_up_fast(2, 218, 62, 3, 42);
static WLabel set_IR_intensity(2, 170, 60, 3); 

static WLabel time_input_buttons_bg(9, 124, 110, 4);
static WLabel time_down(2, 126, 112, 3, 42);
static WLabel time_up(2, 218, 112, 3, 42);
static WLabel set_time(2, 170, 110, 3);

static bool values_changed = false;

static void change_value(uint8_t * variable, int8_t increment)
{
    values_changed = true;

    if(variable != &time_on_timer)
    {
        if(* variable >= 90 && increment == 10)
            * variable = 99;
        else if(* variable <= 10 && increment == -10)
            * variable = 0;
        else if(* variable + increment >= 0 && * variable + increment <= 99)
            * variable += increment;
    }
    else if(* variable + increment >= 0 && * variable + increment <= 30 && variable == &time_on_timer)
    {
        * variable += increment;
        time_on_timer_in_seconds = (* variable) * 60;
    }

    send_intensity(0, 0);
}

void WSetupMenu::tick()
{
    if(values_changed)
    {
        values_changed = false;
        set_red_intensity.paint_two_digits(red_intensity_val, ILI9341_RED, ILI9341_BLACK);
        set_IR_intensity.paint_two_digits(IR_intensity_val, ILI9341_WHITE, ILI9341_BLACK);
        set_time.paint_two_digits(time_on_timer, ILI9341_WHITE, ILI9341_BLACK);
    }
}

void WSetupMenu::paint()
{
    WLabel::paint(F("RED"), 15, 10, ILI9341_RED, ILI9341_BLACK, 3);
    WLabel::paint(F("IR"), 15, 60, ILI9341_WHITE, ILI9341_BLACK, 3);
    WLabel::paint(F("TIME: "), 15, 110, ILI9341_WHITE, ILI9341_BLACK, 3);

    save_button.paint(F("Save"), ILI9341_BLACK, ILI9341_GREEN);

    red_input_buttons_bg.w = 226;
    red_input_buttons_bg.paint(F(""), ILI9341_MAROON, ILI9341_MAROON);
    red_down_slow.paint(F("-"), ILI9341_RED, ILI9341_BLACK);
    red_down_fast.paint(F("-"), ILI9341_RED, ILI9341_BLACK);
    red_up_slow.paint(F("+"), ILI9341_RED, ILI9341_BLACK);
    red_up_fast.paint(F("+"), ILI9341_RED, ILI9341_BLACK);
    set_red_intensity.paint_two_digits(red_intensity_val, ILI9341_RED, ILI9341_BLACK);

    IR_input_buttons_bg.w = 226;
    IR_input_buttons_bg.paint(F(""), ILI9341_MAROON, ILI9341_MAROON);
    IR_down_slow.paint(F("-"), ILI9341_WHITE, ILI9341_BLACK);
    IR_down_fast.paint(F("-"), ILI9341_WHITE, ILI9341_BLACK);
    IR_up_slow.paint(F("+"), ILI9341_WHITE, ILI9341_BLACK);
    IR_up_fast.paint(F("+"), ILI9341_WHITE, ILI9341_BLACK);
    set_IR_intensity.paint_two_digits(red_intensity_val, ILI9341_WHITE, ILI9341_BLACK);

    time_input_buttons_bg.w = 138;
    time_input_buttons_bg.paint(F(""), ILI9341_MAROON, ILI9341_MAROON);
    time_down.paint(F("-"), ILI9341_WHITE, ILI9341_BLACK);
    time_up.paint(F("+"), ILI9341_WHITE, ILI9341_BLACK);
    set_time.paint_two_digits(time_on_timer, ILI9341_WHITE, ILI9341_BLACK);
}

void WSetupMenu::touch(uint16_t x, uint16_t y)
{
    if(save_button.hit(x, y))
    {
        save_settings();
        menu.setMenu(main_menu);
    }

    if(red_down_slow.hit(x, y))
        change_value(&red_intensity_val, -1);
    else if(red_down_fast.hit(x, y))
        change_value(&red_intensity_val, -10);
    else if(red_up_slow.hit(x, y))
        change_value(&red_intensity_val, 1);
    else if(red_up_fast.hit(x, y))
        change_value(&red_intensity_val, 10);

    if(IR_down_slow.hit(x, y))
        change_value(&IR_intensity_val, -1);
    else if(IR_down_fast.hit(x, y))
        change_value(&IR_intensity_val, -10);
    else if(IR_up_slow.hit(x, y))
        change_value(&IR_intensity_val, 1);
    else if(IR_up_fast.hit(x, y))
        change_value(&IR_intensity_val, 10);

    if(time_down.hit(x, y))
        change_value(&time_on_timer, -1);
    else if(time_up.hit(x, y))
        change_value(&time_on_timer, 1);

}