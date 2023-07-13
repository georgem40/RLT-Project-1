#include <stdio.h>
#include "Adafruit_ILI9341.h"
#include "menu.h"

static bool between(uint16_t corner, uint8_t width, uint16_t value)
{
   if ((value >= corner) && (value <= (corner + width)))
      return true;
   return false;
}

bool WLabel::hit(uint16_t hx, uint16_t hy) const
{
   if (between(x, w, hx) && between(y, h, hy))
      return true;
   return false;
}


/* min size (h/w) of buttons, if text is small */
static const int minimum_button_size = 46;

static const int base_text_height = 8;
static const int base_text_width = 6;

static constexpr uint16_t string_width(uint8_t swidth, uint8_t sz)
{
   return swidth * (base_text_width * sz);
}

static constexpr uint16_t string_height(uint8_t sz)
{
   return (base_text_height * sz);
}

WLabel::WLabel(uint8_t  swidth,
      uint16_t x,
      uint16_t y,
      uint8_t  sz,
      uint8_t  min_width) 
   : x(x),
   y(y),
   sz(sz),
   w(max(min_width, string_width(swidth, sz) + 4)),
   h(max(min_width, string_height(sz) + 4))
{
}

void WLabel::paint_common(uint8_t  len,
      uint16_t fg,
      uint16_t bg) const
{
   uint16_t text_x = (x + ((w - string_width(len, sz)) / 2));
   uint16_t text_y = (y + ((h - string_height(sz)) / 2));

   tft.fillRect(x, y, w, h, bg);
   tft.setTextSize(sz);
   tft.setTextColor(fg);
   tft.setCursor(text_x, text_y);
}

void WLabel::paint_common(int      len,
      uint16_t x,
      uint16_t y,
      uint16_t fg,
      uint16_t bg,
      uint8_t  sz,
      uint8_t  w,
      uint8_t  h)
{
   if (w == 0)
      w = string_width(len, sz);
   if (h == 0) // +4 so coordinates line up with buttons correctly
      h = max(minimum_button_size, string_height(sz) + 4);

   uint16_t text_x = (x + ((w - string_width(len, sz)) / 2));
   uint16_t text_y = (y + ((h - string_height(sz)) / 2));

   tft.fillRect(x, y, w, h, bg);
   tft.setTextSize(sz);
   tft.setTextColor(fg);
   tft.setCursor(text_x, text_y);
}

void WLabel::paint(const __FlashStringHelper *str,
      uint16_t                   x,
      uint16_t                   y,
      uint16_t                   fg,
      uint16_t                   bg,
      uint8_t                    sz,
      uint8_t                    w,
      uint8_t                    h)
{
   int len = strlen_P((const char *)str);
   paint_common(len, x, y, fg, bg, sz, w, h);
   tft.print(str);
}

void WLabel::paint(const char *str,
      uint16_t    x,
      uint16_t    y,
      uint16_t    fg,
      uint16_t    bg,
      uint8_t     sz,
      uint8_t     w,
      uint8_t     h)
{
   int len = strlen(str);
   paint_common(len, x, y, fg, bg, sz, w, h);
   tft.print(str);
}

void WLabel::paint(char     ch,
      uint16_t x,
      uint16_t y,
      uint16_t fg,
      uint16_t bg,
      uint8_t  sz,
      uint8_t  w,
      uint8_t  h)
{
   paint_common(1, x, y, fg, bg, sz, w, h);
   tft.print(ch);
}

void WLabel::paint(const char *label,
      uint16_t    fg,
      uint16_t    bg) const
{
   paint_common(strlen(label), fg, bg);
   tft.print(label);
}

void WLabel::paint(const __FlashStringHelper *label,
      uint16_t                   fg,
      uint16_t                   bg) const
{
   paint_common(strlen_P((const char *)label), fg, bg);
   tft.print(label);
}

void WLabel::paint(uint8_t  m,
      uint16_t fg,
      uint16_t bg) const
{
   char buf[8];
   int z = m;
   snprintf(buf, sizeof(buf), "%d", z);
   paint(buf, fg, bg);
}

void WLabel::paint(uint16_t m,
      uint16_t fg,
      uint16_t bg) const
{
   char buf[8];
   int z = m;
   snprintf(buf, sizeof(buf), "%d", z);
   paint(buf, fg, bg);
}

void WLabel::paint_two_digits(uint8_t  m,
      uint16_t fg,
      uint16_t bg) const
{
   char buf[3];
   int z = m;
   snprintf(buf, sizeof(buf), "%2.2d", z);
   paint( buf, fg, bg);
}

void WLabel::paint_four_digits(uint16_t m,
      uint16_t fg,
      uint16_t bg) const
{
   char buf[8];
   int z = m;
   snprintf( buf, sizeof(buf), "%4.4d", z);
   paint( buf, fg, bg);
}
