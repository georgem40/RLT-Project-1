#include "menu-system.h"

WMainMenu   main_menu;
WSetupMenu  setup_menu;
WRunMenu    run_menu;

void MenuSystem::setMenu(WMenuBase& menu)
{
   previous = current;
   current  = &menu;
   tft.setTextSize(2);
   tft.fillScreen(ILI9341_BLACK);
   current->paint();
}

void MenuSystem::prevMenu(void)
{
   WMenuBase *menu;
   menu     = previous;
   previous = current;
   current  = menu;
   tft.setTextSize(2);
   tft.fillScreen(ILI9341_BLACK);
   current->paint();
}
