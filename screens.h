#ifndef SCREEN_H
#define SCREEN_H

#include "lvgl.h"

#define MENU_ITEMS 4

extern lv_obj_t *menu_items[MENU_ITEMS];
extern int selected_index;

void create_menu_screen(void);
extern void update_menu_highlight(void);

#endif
