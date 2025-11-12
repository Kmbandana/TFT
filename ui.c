#include "ui.h"
#include "screens.h"

void ui_init(void) {
    // Initialize the LVGL library
    lv_init();

    // Create and load the menu screen
    create_menu_screen();
}
